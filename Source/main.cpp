#include<iostream>
#include<windows.h>

#include "WheatMorse.h"

#define MorseKey 190
#define DIkey 190
#define DAkey 189
#define BACKSPACEkey 8

#define DItime 125
#define Overtime 400

using namespace std;

bool shiftMode = false;

class _simkey {
    public:
        void down(int vkey) {
            keybd_event(vkey,0,0,0);
        }
        void up(int vkey) {
            keybd_event(vkey,0,KEYEVENTF_KEYUP,0);
        }
        void press(int vkey) {
            down(vkey);
            up(vkey);
        }
};

bool key_press(int vkey) {
    return (GetAsyncKeyState(vkey) & 0x8000) ? true : false;
}

bool check_shift(int vkey) {
    
    return false;
}

bool checkSpecialKey(int vkey) {
    printf("    ");
    switch(vkey) {
        case 0:
            printf("Unknown Input\n");
            return true;
        case 8:
            printf("BackSpace\n");
            return true;
        case ' ':
            printf("Space\n");
            return true;
        case 13:
            printf("Enter\n");
            return true;
        case 16:
            if(shiftMode) {
                printf("Shift Mode Off\n");
            } else {
                printf("Shift Mode On\n");
            }
            shiftMode = !shiftMode;
            return true;
    }
    return false;
}

int main() {
    printf("_________________________________________________\n");
    printf("|                                               |\n");
    printf("|         MorseKeyInput is running now.         |\n");
    printf("|    You can press . key to input MorseCode.    |\n");
    printf("|                                               |\n");
    printf("|_______________________________________________|\n");
    printf("|      You can use ...-. to BackSpace.          |\n");
    printf("|      You can use .-... to Space.              |\n");
    printf("|      You can use .-...- to Enter.             |\n");
    printf("|      You can use ..-- to change Shift mode.   |\n");
    printf("|_______________________________________________|\n");
    
    _simkey simkey;

    int kpretime = 0; // key pressing time
    int kreltime = 0; // key releasing time
    int klen = 0; // key length

    int MorseInputs[1024] = {0}; // 0 noone, 1 DI, 2 DA

    DWORD krelIntime = 0;

    bool shiftModeWas = shiftMode;

    while(1) {
        if(shiftMode != shiftModeWas) {
            if(shiftMode == true) {
                simkey.down(16);
            } else {
                simkey.up(16);
            }
            shiftModeWas = shiftMode;
        }
        // kpretime = 0;
        if(key_press(MorseKey)) {
            if(DIkey != MorseKey) {
                simkey.press(BACKSPACEkey);
                simkey.press(DIkey);
            }
            // kreltime = 0;
            DWORD kpreIntime = GetTickCount();
            bool DAshowed = false;
            while(key_press(MorseKey)) {
                // kpretime++;
                // Sleep(1);
                DWORD kpreOuttime = GetTickCount();
                kpretime = int(kpreOuttime - kpreIntime);
                if(kpretime >= DItime && DAshowed == false) {
                    DAshowed = true;
                    simkey.press(BACKSPACEkey);
                    simkey.press(DAkey);
                }
            }
            // printf("%d\n",kpretime);
            if(kpretime < DItime) { // input DI
                printf(".");
                MorseInputs[klen] = 1; // DI = 1
                // simkey.press(DIkey);
            } else { // input DA
                printf("-");
                MorseInputs[klen] = 2; // DA = 2
                // simkey.press(DAkey);
            }
            klen++;
            krelIntime = GetTickCount();
        } else {
            DWORD krelOuttime = GetTickCount();
            // kreltime++;
            kreltime = int(krelOuttime - krelIntime);
            if(kreltime > Overtime && klen > 0) {
                char output = WMorseFind(MorseInputs, klen);
                int outputKey = WMorseChrToKey(output);
                for(int i = 0; i < klen; i++) {
                    MorseInputs[i] = 0;
                    simkey.press(BACKSPACEkey);
                }
                if(checkSpecialKey(outputKey) == false) {
                    printf("  %d  [%c] key:%d\n", klen, output, outputKey);
                }
                if(outputKey != 16) { // Is not shift.
                    simkey.press(output >= 'a' && output <= 'z' ? outputKey - 32 : outputKey); // Output Here.
                }
                klen = 0;
            }
            Sleep(1);
        }
    }
    return 0;
}
