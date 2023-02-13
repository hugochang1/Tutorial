#include <stdio.h>
#include <string.h>
#include <stdlib.h> //atoi

typedef struct {
    #define HAS_PRN 0x1
    #define HAS_EVELATION 0x2
    #define HAS_AZI 0x4
    #define HAS_SNR 0x8
    unsigned char state;
    unsigned short prn;
    unsigned char elevation;
    unsigned short azi;
    unsigned char snr;
} satellite;

#define MAX_SATELITTE 256
typedef struct {
    char state; //0: ready to use, 1: under parsing
    int ongoing_sat;

    unsigned char num;
    satellite sat[MAX_SATELITTE];
} satellites;

typedef struct {
    #define HAS_LAT_LNG 0x1
    #define HAS_UTC 0x2
    #define HAS_ALT 0x3
    unsigned char state;
    double latitude;
    double longitude;
    unsigned int utc;
    float altitude;
} location;

typedef struct {
    location loc;
    satellites s;
} gps_info;

void dump_satellites(satellites* s) {
    printf("state=%u num=%u ongoing_sat=%u\n", s->state, s->num, s->ongoing_sat);
    for (int i = 0; i < s->num; i++) {
        satellite* sat = &s->sat[i];
        printf("  i=%02d state=%0x prn=%02d ele=%02d azi=%03d snr=%02d\n",
            i, sat->state, sat->prn, sat->elevation, sat->azi, sat->snr);
    }
}

void dump_location(location* loc) {
    printf("state=0x%x\n", loc->state);
    printf("  utc=%d latitude=%lf longitude=%lf altitude=%f\n",
        loc->utc, loc->latitude, loc->longitude, loc->altitude);
}

char* strtoken(char* str, char delim) {
    static char* out = NULL;
    static char* p = NULL;
    if (str) {
        p = str;
    } else{
        if (p == NULL) return NULL;
        p++;
    }
    out = p;
    p = strchr(p, delim);
    if (p) {
        *p = '\0';
    }
    return out;
}


void parseGPGSV(char* nmea, satellites* s) {
    char* p = NULL;
    int sent_num = 0;
    int curr_num = 0;
    int count = 0;
    //      0 1 2  3  4  5   6  7  8  9  10 11 12 13  14 15 16 17  18 19
    // $GPGSV,2,1,08,02,74,042,45,04,18,190,36,07,67,279,42,12,29,323,36*77
    p = strchr(nmea, '*');
    if (p) {
        *p = '\0';
    }
    p = strtoken(nmea, ',');
    while (p) {
        if (count == 0) {
            //do nothing
        } else if (count == 1) {
            sent_num = atoi(p);
        } else if (count == 2) {
            curr_num = atoi(p);
            if (curr_num == 1) {
                memset(s, 0, sizeof(*s));
                s->state = 1;
            }
            if (curr_num == sent_num) {
                s->state = 0;
            }
        } else if (count == 3) {
            s->num = atoi(p);
        } else {
            satellite *sat = &s->sat[s->ongoing_sat];
            if (count % 4 == 0 && strlen(p) > 0) {
                sat->state |= HAS_PRN;
                sat->prn = atoi(p);
            } else if (count % 4 == 1 && strlen(p) > 0) {
                sat->state |= HAS_EVELATION;
                sat->elevation = atoi(p);
            } else if (count % 4 == 2 && strlen(p) > 0) {
                sat->state |= HAS_AZI;
                sat->azi = atoi(p);
            } else if (count % 4 == 3 && strlen(p) > 0) {
                sat->state |= HAS_SNR;
                sat->snr = atoi(p);
            }
            if (count % 4 == 3) {
                s->ongoing_sat++;
            }
        }
        p = strtoken(NULL, ',');
        count++;
    }
}

void parseGPGGA(char* nmea, location* loc) {
    //      0      1         2 3          4 5 6  7   8     9 10   11 12 13 14
    // $GPGGA,210230,3855.4487,N,09446.0071,W,1,07,1.1,370.5,M,-29.5,M,,*7A
    char* p = NULL;
    int count = 0;

    p = strchr(nmea, '*');
    if (p) *p = '\0';
    p = strtoken(nmea, ',');
    memset(loc, 0, sizeof(*loc));
    while (p) {
        if (count == 0) {
            //do nothing
        } else if (count == 1 && strlen(p) > 0) {
            // utc
            loc->state |= HAS_UTC;
            loc->utc = atoi(p);
        } else if (count == 2 && strlen(p) > 0) {
            //lat
            double fraction = 0;
            loc->state |= HAS_LAT_LNG;
            loc->latitude = atof(p);
            loc->latitude /= 100;
            fraction = loc->latitude - (int)loc->latitude;
            loc->latitude -= fraction;
            loc->latitude += fraction /60 * 100;
        } else if (count == 3 && strlen(p) > 0) {
            //lat NS
            loc->state |= HAS_LAT_LNG;
            if (*p == 'S') {
                loc->latitude = -loc->latitude;
            }
        } else if (count == 4 && strlen(p) > 0) {
            //lng
            double fraction = 0;
            loc->state |= HAS_LAT_LNG;
            loc->longitude = atof(p);
            loc->longitude /= 100;
            fraction = loc->longitude - (int)loc->longitude;
            loc->longitude -= fraction;
            loc->longitude += fraction / 60 * 100;
        } else if (count == 5 && strlen(p) > 0) {
            //lng WE
            loc->state |= HAS_LAT_LNG;
            if (*p == 'W') {
                loc->longitude = -loc->longitude;
            }
        } else if (count == 9 && strlen(p) > 0) {
            //alt
            loc->state |= HAS_ALT;
            loc->altitude = atof(p);
        }
        p = strtoken(NULL, ',');
        count++;
    }
}

void nmeaParser(const char** nmea, int n, gps_info* info) {
    char buff[512] = {0};
    for (int i = 0; i < n; i++) {
        if (strstr(nmea[i], "$GPGSV")) {
            strcpy(buff, nmea[i]);
            parseGPGSV(buff, &info->s);
        }
        if (strstr(nmea[i], "$GPGGA")) {
            strcpy(buff, nmea[i]);
            parseGPGGA(buff, &info->loc);
        }
    }
}

int main() {
    const char *nmea[] = {
        "$GPGSV,2,1,08,02,74,042,45,04,18,190,36,07,67,279,42,12,29,323,36*77",
        "$GPGSV,2,2,08,15,30,050,47,19,09,158,,26,12,281,40,27,38,173,41*7B",
        "$GPGGA,210230,3855.4487,N,09446.0071,W,1,07,1.1,370.5,M,-29.5,M,,*7A",
    };
    const char *nmea2[] = {
        "$GPGSV,3,1,10,18,,,,09,,,,22,,,,15,,,*70",
        "$GPGSV,3,2,10,21,32,199,23,14,25,272,24,05,,,,26,14,070,20*7E",
        "$GPGSV,3,3,10,29,07,074,,30,07,163,28*7D",
        "$GPGGA,210230,3855.4487,N,09446.0071,W,1,07,1.1,370.5,M,-29.5,M,,*7A",
    };
    gps_info info;

    memset(&info, 0, sizeof(info));

    nmeaParser(nmea, 3, &info);
    dump_satellites(&info.s);

    nmeaParser(nmea2, 4, &info);
    dump_satellites(&info.s);
    dump_location(&info.loc);

    return 0;
}
