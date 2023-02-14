#include <iostream>
#include <vector>
#include <string>


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

class Satellite {
public:
    #define HAS_PRN 0x1
    #define HAS_ELE 0x2
    #define HAS_AZI 0x4
    #define HAS_SNR 0x8
    int state;
    int prn;
    int ele;
    int azi;
    int snr;
};

#define MAX_SAT_NUM 8
class Satellites {
public:
    int num;
    Satellite s[MAX_SAT_NUM];

    int state;
    int ongoing_sat;

    Satellites() {
        reset();
    }

    void reset() {
        num = 0;
        memset(&s, 0, sizeof(s));
        state = 0;
        ongoing_sat = 0;
    }

    void dump() {
        printf("num=%d state=%d ongoing_sat=%d\n",
            num, state, ongoing_sat);
        for (int i = 0; i < num; i++) {
            printf("  i=%02d state=%x prn=%02d ele=%02d azi=%03d snr=%02d\n",
                i, s[i].state, s[i].prn, s[i].ele, s[i].azi, s[i].snr);
        }
    }
};

class Location {
public:
    #define HAS_LOC 0x1
    #define HAS_UTC 0x2
    #define HAS_ALT 0x4
    int state;
    double lat;
    double lng;
    int utc;
    float alt;
    Location() {
        reset();
    }

    void reset() {
        state = 0;
        lat = 0;
        lng = 0;
        utc = 0;
        alt = 0;
    }

    void dump() {
        printf("state=%x lat=%lf lng=%lf utc=%d alt=%f\n",
            state, lat, lng, utc, alt);
    }
};

class GpsInfo {
public:
    Location loc;
    Satellites s;

    void reset() {
        loc.reset();
        s.reset();
    }

    void dump() {
        loc.dump();
        s.dump();
    }
};



char* strtoken(char* str, char delim) {
    static char* p = NULL;
    static char* out = NULL;
    if (str) {
        p = str;
    } else {
        if (p == NULL) return NULL;
        p++;
    }
    out = p;
    p = strchr(p, delim);
    if (p) *p = '\0';
    return out;
}

void parseGPGSV(char* nmea, Satellites* s) {
    int count = 0;
    int sent_num = 0;
    int curr_sent = 0;
    char* p = NULL;
    //     0 1 2  3  4  5   6  7  8  9  10 11 12 13  14 15 16 17  18 19
    //$GPGSV,2,1,08,02,74,042,45,04,18,190,36,07,67,279,42,12,29,323,36*77
    p = strchr(nmea, '*');
    if (p) *p = '\0';
    p = strtoken(nmea, ',');
    while (p) {
        if (count == 0) {
            
        } else if (count == 1) {
            sent_num = atoi(p);
        } else if (count == 2) {
            curr_sent = atoi(p);
            if (curr_sent == 1) {
                s->reset();
                s->state = 1;
            }
            if (curr_sent == sent_num) {
                s->state = 0;
            }
        } else if (count == 3) {
            s->num = atoi(p);
            if (s->num > MAX_SAT_NUM) {
                s->num = MAX_SAT_NUM;
            }
        } else {
            Satellite* sat;
            if (s->ongoing_sat == MAX_SAT_NUM) {
                return;
            }
            sat = &s->s[s->ongoing_sat];
            if (count % 4 == 0 && strlen(p) > 0) {
                sat->state |= HAS_PRN;
                sat->prn = atoi(p);
            } else if (count % 4 == 1 && strlen(p) > 0) {
                sat->state |= HAS_ELE;
                sat->ele = atoi(p);
            } else if (count % 4 == 2 && strlen(p) > 0) {
                sat->state |= HAS_AZI;
                sat->azi = atoi(p);
            } else if (count % 4 == 3 && strlen(p) > 0 ) {
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

void parseGPGGA(char* nmea, Location* loc) {
    //     0      1         2 3          4 5 6  7   8     9 10   11 12 13
    //$GPGGA,210230,3855.4487,S,09446.0071,W,1,07,1.1,370.5,M,-29.5,M,,*7A
    int count = 0;
    char* p = NULL;
    p = strchr(nmea, '*');
    if (p) *p = '\0';
    p = strtoken(nmea, ',');
    while (p) {
        if (count == 0) {

        } else if (count == 1 && strlen(p) > 0) {
            loc->state |= HAS_UTC;
            loc->utc = atoi(p);
        } else if (count == 2 && strlen(p) > 0) {
            double fraction = 0;
            loc->state |= HAS_LOC;
            loc->lat = atof(p);
            loc->lat /= 100;
            fraction = loc->lat - (int)loc->lat;
            loc->lat += fraction/60*100 - fraction;
        } else if (count == 3 && strlen(p) > 0) {
            if (*p == 'S') {
                loc->lat = -loc->lat;
            }
        } else if (count == 4 && strlen(p) > 0) {
            double fraction = 0;
            loc->lng = atof(p);
            loc->lng /= 100;
            fraction = loc->lng - (int)loc->lng;
            loc->lng += fraction/60*100 - fraction;
        } else if (count == 5 && strlen(p) > 0) {
            if (*p == 'W') {
                loc->lng = -loc->lng;
            }
        } else if (count == 9 && strlen(p) > 0) {
            loc->state |= HAS_ALT;
            loc->alt = atof(p);
        }
        
        p = strtoken(NULL, ',');
        count++;
    }
}

void nmeaParser(const char * nmea, GpsInfo* info) {
    char buff[256];
    if (strstr(nmea, "$GPGSV")) {
        strcpy(buff, nmea);
        parseGPGSV(buff, &info->s);
    } else if (strstr(nmea, "$GPGGA")) {
        strcpy(buff, nmea);
        parseGPGGA(buff, &info->loc);
    }
}

int main(int argc, char *argv[]) {
    GpsInfo info;
    string str[] = {
        "$GPGSV,2,1,08,02,74,042,45,04,18,190,36,07,67,279,42,12,29,323,36*77",
        "$GPGSV,2,2,08,15,30,050,47,19,09,158,,26,12,281,40,27,38,173,41*7B",
        "$GPGGA,210230,3855.4487,S,09446.0071,W,1,07,1.1,370.5,M,-29.5,M,,*7A"};

    for (auto s : str) {
        nmeaParser(s.c_str(), &info);
    }
    info.dump();
    return 0;
}

