#ifndef __WHEATMORSE_H__
#define __WHEATMORSE_H__

#include<iostream>

#define WMORSEFORM_SIZE_MAX 50
#define WMORSEFORM_SIZE 50
// From . to @ are Disable.

int WMorseFormCodes[WMORSEFORM_SIZE_MAX][8] = {
    // Customized
    {1,1,1,2,1}, // BackSpace
    {1,2,1,1,1}, // Space
    {1,2,1,1,1,2}, // Enter
    {1,1,2,2}, // Shift

    {2,1,2,2,1}, // [
    {2,1,2,2,1,2}, // ]
    {2,1,2,2,2}, // \

    // 7 in total
    
    // Official
    {1,2}, // a
    {2,1,1,1}, // b
    {2,1,2,1}, // c
    {2,1,1}, // d
    {1}, // e
    {1,1,2,1}, // f
    {2,2,1}, // g
    {1,1,1,1}, // h
    {1,1}, // i
    {1,2,2,2}, // j
    {2,1,2}, // k
    {1,2,1,1}, // l
    {2,2}, // m
    {2,1}, // n
    {2,2,2}, // o
    {1,2,2,1}, // p
    {2,2,1,2}, // q
    {1,2,1}, // r
    {1,1,1}, // s
    {2}, // t
    {1,1,2}, // u
    {1,1,1,2}, // v
    {1,2,2}, // w
    {2,1,1,2}, // x
    {2,1,2,2}, // y
    {2,2,1,1}, // z
    // 26 in total

    {2,2,2,2,2}, // 0
    {1,2,2,2,2}, // 1
    {1,1,2,2,2}, // 2
    {1,1,1,2,2}, // 3
    {1,1,1,1,2}, // 4
    {1,1,1,1,1}, // 5
    {2,1,1,1,1}, // 6
    {2,2,1,1,1}, // 7
    {2,2,2,1,1}, // 8
    {2,2,2,2,1}, // 9
    // 10 in total

    {1,2,1,2,1,2}, // .
    // {2,2,2,1,1,1}, // :
    {2,2,1,1,2,2}, // ,
    {2,1,2,1,2,1}, // ;
    // {1,1,2,2,1,1}, // ?
    {2,1,1,1,2}, // =
    {1,2,2,2,2,1}, // '
    {2,1,1,2,1}, // /
    // {2,1,2,1,2,2}, // !
    {2,1,1,1,1,2}, // -
    // {1,1,2,2,1,2}, // _
    // {1,2,1,1,2,1}, // "
    // {2,1,2,2,1}, // (
    // {2,1,2,2,1,2}, // )
    // {1,1,1,2,1,1,2}, // $
    // {1,2,2,1,2,1} // @
    // // 16 in total
    // 7 in total
};

int WMorseFormLen[WMORSEFORM_SIZE_MAX] = {
    // Customized
    5,5,6,4,
    5,6,5,

    // Official
    2,4,4,3,1,4,3, // a ~ g
    4,2,4,3,4,2,2, // h ~ n
    3,4,4,3,3,1,3, // o ~ u
    4,3,4,4,4, // v ~ z

    5,5,5,5,5,5,5,5,5,5, // 0 ~ 9

    6,6,6,5,6,5,6, // . ~ -
};

char WMorseFormChr[WMORSEFORM_SIZE_MAX] = {
    // Customized
    8, // BackSpace
    ' ', // Space
    13, // Enter
    16, // Shift

    '[',']','\\',

    // Official
    'a','b','c','d','e','f','g',
    'h','i','j','k','l','m','n',
    'o','p','q','r','s','t','u',
    'v','w','x','y','z',

    '0','1','2','3','4','5','6','7','8','9',

    '.',',',';','=','\'','/','-',
};

int WMorseFormChrToKey[WMORSEFORM_SIZE_MAX][2] = {
    {'[',219},
    {']',221},
    {'\\',220},

    {'.',190},
    {',',188},
    {';',186},
    {'=',187},
    {'\'',222},
    {'/',191},
    {'-',189},
};

char WMorseFind(int input[], int len) {
    // for(int i = 0; i < len; i++) printf("%d", input[i]);
    if(len > 8) {
        return 0;
    }
    for(int i = 0; i < WMORSEFORM_SIZE; i++) {
        if(WMorseFormChr[i] == 0) {
            return 0;
        }
        if(input[0] == WMorseFormCodes[i][0] && len == WMorseFormLen[i]) {
            bool found = true;
            for(int j = 1; j < len; j++) {
                if(input[j] != WMorseFormCodes[i][j]) {
                    found = false;
                    break;
                }
            }
            if(found == true) {
                return WMorseFormChr[i];
            }
        }
    }
    return 0;
}

int WMorseChrToKey(char _chr) {
    if(_chr == 0) {
        return 0;
    }
    for(int i = 0; i < WMORSEFORM_SIZE; i++) {
        if(WMorseFormChrToKey[i][0] == 0) {
            break;
        }
        if(WMorseFormChrToKey[i][0] == (int)_chr) {
            return WMorseFormChrToKey[i][1];
        }
    }
    return (int)_chr;
}

#endif
