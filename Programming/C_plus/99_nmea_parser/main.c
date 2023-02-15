#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
    Satellite() {
        reset();
    }
    
    void reset() {
        state = 0;
        prn = 0;
        ele = 0;
        azi = 0;
        snr = 0;
    }
    
    void dump() {
        printf("  state=%x prn=%02d ele=%02d azi=%03d snr=%02d\n",
            state, prn, ele, azi, snr);
    }
};

class Satellites {
public:
    vector<Satellite> s;
    Satellites() {}
    
    void dump() {
        printf("num=%zu\n", s.size());
        for (size_t i = 0; i < s.size(); i++) {
            s[i].dump();
        }
    }
};

class Location {
public:
    #define HAS_LOC 0x1
    #define HAS_UTC 0x2
    #define HAS_ALT 0x4
    int state;
    int utc;
    double lat;
    double lng;
    float alt;
    Location() {
        state = 0;
        lat = 0;
        lng = 0;
        alt = 0;
    }
    
    void dump() {
        printf("state=%x lat=%lf lng=%lf utc=%d alt=%f\n",
            state, lat, lng, utc, lat);
    }
};

class GpsInfo {
public:
    Location loc;
    Satellites s;
    GpsInfo() {}
    
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
    if (p) *p = 0;
    return out;
}

void parseGPGSV(char* nmea, Satellites* s) {
    //     0 1 2  3  4  5   6  7  8  9  10 11 12 13  14 15 16 17 18  19
    //$GPGSV,2,1,08,02,74,042,45,04,18,190,36,07,67,279,42,12,29,323,36*77
    int sent_num = 0;
    int curr_sent = 0;
    int count = 0;
    char* p = NULL;
    Satellite sat;
    
    p = strchr(nmea, '*');
    if (p) *p = 0;
    p = strtoken(nmea, ',');
    while (p) {
        if (count == 0 ) {
        } else if (count == 1) {
            sent_num = atoi(p);
        } else if (count == 2) {
            curr_sent = atoi(p);
            if (curr_sent == 1) {
                s->s.clear();
            }
            if (curr_sent == sent_num) {
                //Satellites is ready
            }
        } else if (count == 3) {
            // the number of satellite
        } else {
            if (count % 4 == 0 && strlen(p) > 0) {
                sat.reset();
                sat.state |= HAS_PRN;
                sat.prn = atoi(p);
            } else if (count % 4 == 1 && strlen(p) > 0) {
                sat.state |= HAS_ELE;
                sat.ele = atoi(p);
            } else if (count % 4 == 2 && strlen(p) > 0) {
                sat.state |= HAS_AZI;
                sat.azi = atoi(p);
            } else if (count % 4 == 3 && strlen(p) > 0) {
                sat.state |= HAS_SNR;
                sat.snr = atoi(p);
            }
            if (count % 4 == 3) {
                s->s.push_back(sat);
            }
        }
        p = strtoken(NULL, ',');
        count++;
    }
}

void parseGPGGA(char* nmea, Location* loc) {
    //     0      1         2 3          4 5 6  7   8     9 10   11 12 13 14
    //$GPGGA,210230,3855.4487,S,09446.0071,W,1,07,1.1,370.5,M,-29.5,M,,*7A
    char* p = NULL;
    int count = 0;
    
    p = strchr(nmea, '*');
    if (p) *p = 0;
    p = strtoken(nmea, ',');
    while (p) {
        if (count == 0) {
        } else if (count == 1 && strlen(p) > 0) {
            loc->state |= HAS_UTC;
            loc->utc = atoi(p);
        } else if (count == 2 && strlen(p) > 0) {
            loc->state |= HAS_LOC;
            loc->lat = atof(p);
            loc->lat /= 100;
            double fraction = loc->lat - (int)loc->lat;
            loc->lat += fraction/60*100 - fraction;
        } else if (count == 3 && strlen(p) > 0) {
            if (*p == 'S') {
                loc->lat = -loc->lat;
            }
        } else if (count == 4 && strlen(p) > 0) {
            loc->lng = atof(p);
            loc->lng /= 100;
            double fraction = loc->lng - (int)loc->lng;
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

int main() {
    vector<string> nmea1 = {
        "$GPGSV,2,1,08,02,74,042,45,04,18,190,36,07,67,279,42,12,29,323,36*77",
        "$GPGSV,2,2,08,15,30,050,47,19,09,158,,26,12,281,40,27,38,173,41*7B",
        "$GPGGA,210230,3855.4487,S,09446.0071,W,1,07,1.1,370.5,M,-29.5,M,,*7A",
    };
    GpsInfo info;
    
    for (string nmea : nmea1) {
        char buff[512];
        const char* p = nmea.c_str();
        if (strstr(p, "$GPGSV")) {
            strcpy(buff, p);
            parseGPGSV(buff, &info.s);
        } else if (strstr(p, "$GPGGA")) {
            strcpy(buff, p);
            parseGPGGA(buff, &info.loc);
        }
        
    }
        
    info.dump();
    sort(info.s.s.begin(), info.s.s.end(), [](Satellite s1, Satellite s2) {
        return s1.snr < s2.snr;
        });
    info.dump();
    
    return 0;
}
