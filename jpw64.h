#ifndef _JPW64_H_
#define _JPW64_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef unsigned char byte;

const int poly = 0x163;

const byte CK[12][8] = {
    {0x00, 0x07, 0x0e, 0x15, 0x1c, 0x23, 0x2a, 0x31},
    {0x38, 0x3f, 0x46, 0x4d, 0x54, 0x5b, 0x62, 0x69},
    {0x70, 0x77, 0x7e, 0x85, 0x8c, 0x93, 0x9a, 0xa1},
    {0xa8, 0xaf, 0xb6, 0xbd, 0xc4, 0xcb, 0xd2, 0xd9},
    {0xe0, 0xe7, 0xee, 0xf5, 0xfc, 0x03, 0x0a, 0x11},
    {0x18, 0x1f, 0x26, 0x2d, 0x34, 0x3b, 0x42, 0x49},
    {0x50, 0x57, 0x5e, 0x65, 0x6c, 0x73, 0x7a, 0x81},
    {0x88, 0x8f, 0x96, 0x9d, 0xa4, 0xab, 0xb2, 0xb9},
    {0xc0, 0xc7, 0xce, 0xd5, 0xdc, 0xe3, 0xea, 0xf1},
    {0xf8, 0xff, 0x06, 0x0d, 0x14, 0x1b, 0x22, 0x29},
    {0x30, 0x37, 0x3e, 0x45, 0x4c, 0x53, 0x5a, 0x61},
    {0x68, 0x6f, 0x76, 0x7d, 0x84, 0x8b, 0x92, 0x99}
};

const byte Sbox[256] = {
    0x96, 0x89, 0x14, 0x95, 0xda, 0x97, 0x17, 0x9d, 0xbd, 0x99, 0x16, 0xc1, 0x5b, 0xdc, 0x13, 0x60, 
    0x0e, 0x3b, 0x1c, 0x7a, 0xdb, 0xf8, 0x30, 0xa6, 0x70, 0xb8, 0xb3, 0x93, 0x54, 0x52, 0xe0, 0x1e, 
    0xd7, 0xee, 0x4d, 0xe3, 0xde, 0x50, 0xed, 0x23, 0x3d, 0x68, 0xa1, 0x8c, 0xc8, 0x6a, 0x83, 0x90,
    0xe8, 0xe2, 0x81, 0xfb, 0x04, 0xc4, 0x19, 0xa4, 0xfa, 0x79, 0xf4, 0x5e, 0xad, 0xb6, 0xdf, 0x45,
    0x36, 0x2e, 0xa7, 0x9f, 0x76, 0xc7, 0x2c, 0x7f, 0xb2, 0x1f, 0xf5, 0xc5, 0x26, 0x27, 0x41, 0x42, 
    0x43, 0x74, 0xe4, 0xba, 0x0d, 0x44, 0x9b, 0xf7, 0xb4, 0x8e, 0xe5, 0x63, 0x11, 0x78, 0x98, 0xae,
    0xa9, 0x00, 0xac, 0xbe, 0x10, 0x4c, 0x20, 0xb5, 0xd2, 0xf3, 0xbf, 0x5c, 0x51, 0x31, 0x82, 0xd4,
    0xa0, 0x6b, 0x6c, 0xa3, 0xaa, 0xf0, 0xff, 0xc2, 0x06, 0xd9, 0x8b, 0x35, 0x32, 0x69, 0x72, 0xe1,
    0xc6, 0xbb, 0xca, 0x39, 0x03, 0x46, 0x12, 0xc3, 0xe6, 0x6d, 0x3e, 0x5a, 0xcb, 0x08, 0x62, 0x73, 
    0x84, 0xfd, 0x5f, 0x34, 0x2a, 0x85, 0x3f, 0xef, 0xce, 0x53, 0x4e, 0x29, 0x7d, 0xbc, 0xfc, 0x4b,
    0x7c, 0x66, 0xe7, 0x1b, 0xa2, 0x71, 0x80, 0x6f, 0x56, 0x7e, 0xf2, 0x28, 0x1d, 0x49, 0x2b, 0xd6,
    0x8a, 0xa8, 0x9a, 0x94, 0x22, 0x92, 0x61, 0x02, 0x55, 0xcd, 0xec, 0x4a, 0x9c, 0xd0, 0x87, 0x05, 
    0x09, 0x4f, 0xdd, 0x01, 0x86, 0x6e, 0x8f, 0xcf, 0xd5, 0x38, 0xf6, 0x57, 0xc0, 0x21, 0x0a, 0xaf,
    0xb9, 0x25, 0x24, 0x67, 0x0f, 0xd1, 0xfe, 0xf9, 0x75, 0xf1, 0x48, 0x18, 0x91, 0x58, 0xb7, 0x0b,
    0x8d, 0x77, 0x65, 0x59, 0xeb, 0x5d, 0x0c, 0x33, 0x88, 0xea, 0xa5, 0x9e, 0x2f, 0x3a, 0xb1, 0x1a,
    0xd3, 0xcc, 0x3c, 0x37, 0x15, 0x7b, 0x47, 0xab, 0xc9, 0x40, 0x64, 0xb0, 0xe9, 0x07, 0x2d, 0xd8
};

const byte iSbox[256] = {
    0x61, 0xc3, 0xb7, 0x84, 0x34, 0xbf, 0x78, 0xfd, 0x8d, 0xc0, 0xce, 0xdf, 0xe6, 0x54, 0x10, 0xd4,
    0x64, 0x5c, 0x86, 0x0e, 0x02, 0xf4, 0x0a, 0x06, 0xdb, 0x36, 0xef, 0xa3, 0x12, 0xac, 0x1f, 0x49,
    0x66, 0xcd, 0xb4, 0x27, 0xd2, 0xd1, 0x4c, 0x4d, 0xab, 0x9b, 0x94, 0xae, 0x46, 0xfe, 0x41, 0xec,
    0x16, 0x6d, 0x7c, 0xe7, 0x93, 0x7b, 0x40, 0xf3, 0xc9, 0x83, 0xed, 0x11, 0xf2, 0x28, 0x8a, 0x96,
    0xf9, 0x4e, 0x4f, 0x50, 0x55, 0x3f, 0x85, 0xf6, 0xda, 0xad, 0xbb, 0x9f, 0x65, 0x22, 0x9a, 0xc1,
    0x25, 0x6c, 0x1d, 0x99, 0x1c, 0xb8, 0xa8, 0xcb, 0xdd, 0xe3, 0x8b, 0x0c, 0x6b, 0xe5, 0x3b, 0x92,
    0x0f, 0xb6, 0x8e, 0x5b, 0xfa, 0xe2, 0xa1, 0xd3, 0x29, 0x7d, 0x2d, 0x71, 0x72, 0x89, 0xc5, 0xa7,
    0x18, 0xa5, 0x7e, 0x8f, 0x51, 0xd8, 0x44, 0xe1, 0x5d, 0x39, 0x13, 0xf5, 0xa0, 0x9c, 0xa9, 0x47,
    0xa6, 0x32, 0x6e, 0x2e, 0x90, 0x95, 0xc4, 0xbe, 0xe8, 0x01, 0xb0, 0x7a, 0x2b, 0xe0, 0x59, 0xc6,
    0x2f, 0xdc, 0xb5, 0x1b, 0xb3, 0x03, 0x00, 0x05, 0x5e, 0x09, 0xb2, 0x56, 0xbc, 0x07, 0xeb, 0x43,
    0x70, 0x2a, 0xa4, 0x73, 0x37, 0xea, 0x17, 0x42, 0xb1, 0x60, 0x74, 0xf7, 0x62, 0x3c, 0x5f, 0xcf,
    0xfb, 0xee, 0x48, 0x1a, 0x58, 0x67, 0x3d, 0xde, 0x19, 0xd0, 0x53, 0x81, 0x9d, 0x08, 0x63, 0x6a,
    0xcc, 0x0b, 0x77, 0x87, 0x35, 0x4b, 0x80, 0x45, 0x2c, 0xf8, 0x82, 0x8c, 0xf1, 0xb9, 0x98, 0xc7,
    0xbd, 0xd5, 0x68, 0xf0, 0x6f, 0xc8, 0xaf, 0x20, 0xff, 0x79, 0x04, 0x14, 0x0d, 0xc2, 0x24, 0x3e,
    0x1e, 0x7f, 0x31, 0x23, 0x52, 0x5a, 0x88, 0xa2, 0x30, 0xfc, 0xe9, 0xe4, 0xba, 0x26, 0x21, 0x97,
    0x75, 0xd9, 0xaa, 0x69, 0x3a, 0x4a, 0xca, 0x57, 0x15, 0xd7, 0x38, 0x33, 0x9e, 0x91, 0xd6, 0x76
};

byte gmul (int a) {
    a <<= 1;
    if ((a & 0x100) == 0x100) {
        a ^= poly;
    }
    return (byte)(a & 0xff);
}

//multiply on GF(256)
byte _multiply(byte a, byte b) {
    byte result = 0;
    while (b > 0) {
        if (b % 2 == 1) {
            result ^= a;
        }
        a = gmul((int)a);
        b >>= 1;
    }
    return result;
}

byte** GenerateKey(byte key[]) {
    byte** roundKey = (byte **)malloc(13 * sizeof(byte *));
    for (int i=0;i<13;i++) {
        roundKey[i] = (byte *)malloc(8 * sizeof(byte));
    }

    //original key
    for (int i=0;i<8;i++) {
        roundKey[0][i] = key[i];
    }

    //key expansion
    for (int i=1;i<13;i++) {
        byte tem[8];
        for (int j=0;j<8;j++) {
            tem[j] = roundKey[i-1][j] ^ roundKey[i-1][(j+3)%8] ^ roundKey[i-1][(j+4)%8] ^ roundKey[i-1][(j+5)%8] ^ CK[i][j];
        }
        tem[7] = Sbox[tem[7]];
        tem[5] = Sbox[tem[5]];
        tem[3] = Sbox[tem[3]];
        tem[1] = Sbox[tem[1]];

        tem[6] = tem[6] ^ tem[7];
        tem[4] = tem[4] ^ tem[5];
        tem[2] = tem[2] ^ tem[3];
        tem[0] = tem[0] ^ tem[1];

        roundKey[i][0] = tem[1]; 
        roundKey[i][1] = tem[2]; 
        roundKey[i][2] = tem[3]; 
        roundKey[i][3] = tem[0];
        roundKey[i][4] = tem[7]; 
        roundKey[i][5] = tem[4]; 
        roundKey[i][6] = tem[5]; 
        roundKey[i][7] = tem[6];

        /*for (int j=0;j<8;j++) {
            printf("%02x ", roundKey[i][j]);
        }
        printf("\n");*/
    }

    return roundKey;
}

//Byte Substitution
byte* SubByte(byte state[]) {
    byte* result = (byte *)malloc(8 * sizeof(byte));

    for (int i=0;i<8;i++) {
        result[i] = Sbox[state[i]];
    }

    return result;
}

//inverse Byte Substitution
byte* inv_SubByte(byte state[]) {
    byte* result = (byte *)malloc(8 * sizeof(byte));

    for (int i=0;i<8;i++) {
        result[i] = iSbox[state[i]];
    }

    return result;
}

//shift between bits and bytes
byte* Shift_Bit_Byte(byte state[]) {
    byte* result = (byte *)malloc(8 * sizeof(byte));

    result[0] = (state[0] >> 1) ^ ((state[0] << 7) & 0b10000000);
    result[1] = (state[4] >> 5) ^ ((state[4] << 3) & 0b11111000);
    result[2] = (state[7] >> 4) ^ ((state[7] << 4) & 0b11110000);
    result[3] = state[3];
    result[4] = (state[1] >> 2) ^ ((state[1] << 6) & 0b11000000);
    result[5] = (state[5] >> 6) ^ ((state[5] << 2) & 0b11111100);
    result[6] = (state[6] >> 3) ^ ((state[6] << 5) & 0b11100000);
    result[7] = (state[2] >> 7) ^ ((state[2] << 1) & 0b11111110);

    return result;
}

//inverse shift between bits and bytes
byte* inv_Shift_Bit_Byte(byte state[]) {
    byte* result = (byte *)malloc(8 * sizeof(byte));

    result[0] = (state[0] << 1) ^ ((state[0] >> 7) & 0b00000001);
    result[1] = (state[4] << 2) ^ ((state[4] >> 6) & 0b00000011);
    result[2] = (state[7] << 7) ^ ((state[7] >> 1) & 0b01111111);
    result[3] = state[3];
    result[4] = (state[1] << 5) ^ ((state[1] >> 3) & 0b00011111);
    result[5] = (state[5] << 6) ^ ((state[5] >> 2) & 0b00111111);
    result[6] = (state[6] << 3) ^ ((state[6] >> 5) & 0b00000111);
    result[7] = (state[2] << 4) ^ ((state[2] >> 4) & 0b00001111);

    return result;
}

//diffusion layer based on MDS code
/* matrix:
    
    0x82 0xc4 0x34 0xf6
    0xf6 0x82 0xc4 0x34
    0x34 0xf6 0x82 0xc4
    0xc4 0x34 0xf6 0x82
*/
byte* MDS(byte state[]) {
    byte* result = (byte *)malloc(8 * sizeof(byte));

    result[0] = _multiply(state[0], 0x82) ^ _multiply(state[1], 0xf6) ^ _multiply(state[2], 0x34) ^ _multiply(state[3], 0xc4);
    result[1] = _multiply(state[0], 0xc4) ^ _multiply(state[1], 0x82) ^ _multiply(state[2], 0xf6) ^ _multiply(state[3], 0x34);
    result[2] = _multiply(state[0], 0x34) ^ _multiply(state[1], 0xc4) ^ _multiply(state[2], 0x82) ^ _multiply(state[3], 0xf6);
    result[3] = _multiply(state[0], 0xf6) ^ _multiply(state[1], 0x34) ^ _multiply(state[2], 0xc4) ^ _multiply(state[3], 0x82);

    result[4] = _multiply(state[4], 0x82) ^ _multiply(state[5], 0xf6) ^ _multiply(state[6], 0x34) ^ _multiply(state[7], 0xc4);
    result[5] = _multiply(state[4], 0xc4) ^ _multiply(state[5], 0x82) ^ _multiply(state[6], 0xf6) ^ _multiply(state[7], 0x34);
    result[6] = _multiply(state[4], 0x34) ^ _multiply(state[5], 0xc4) ^ _multiply(state[6], 0x82) ^ _multiply(state[7], 0xf6);
    result[7] = _multiply(state[4], 0xf6) ^ _multiply(state[5], 0x34) ^ _multiply(state[6], 0xc4) ^ _multiply(state[7], 0x82);

    return result;
}

//inverse diffusion layer based on MDS code
/* matrix:
    
    0xc4 0x65 0xc8 0x8b
    0x8b 0xc4 0x65 0xc8
    0xc8 0x8b 0xc4 0x65
    0x65 0xc8 0x8b 0xc4
*/
byte* inv_MDS(byte state[]) {
    byte* result = (byte *)malloc(8 * sizeof(byte));

    result[0] = _multiply(state[0], 0xc4) ^ _multiply(state[1], 0x8b) ^ _multiply(state[2], 0xc8) ^ _multiply(state[3], 0x65);
    result[1] = _multiply(state[0], 0x65) ^ _multiply(state[1], 0xc4) ^ _multiply(state[2], 0x8b) ^ _multiply(state[3], 0xc8);
    result[2] = _multiply(state[0], 0xc8) ^ _multiply(state[1], 0x65) ^ _multiply(state[2], 0xc4) ^ _multiply(state[3], 0x8b);
    result[3] = _multiply(state[0], 0x8b) ^ _multiply(state[1], 0xc8) ^ _multiply(state[2], 0x65) ^ _multiply(state[3], 0xc4);

    result[4] = _multiply(state[4], 0xc4) ^ _multiply(state[5], 0x8b) ^ _multiply(state[6], 0xc8) ^ _multiply(state[7], 0x65);
    result[5] = _multiply(state[4], 0x65) ^ _multiply(state[5], 0xc4) ^ _multiply(state[6], 0x8b) ^ _multiply(state[7], 0xc8);
    result[6] = _multiply(state[4], 0xc8) ^ _multiply(state[5], 0x65) ^ _multiply(state[6], 0xc4) ^ _multiply(state[7], 0x8b);
    result[7] = _multiply(state[4], 0x8b) ^ _multiply(state[5], 0xc8) ^ _multiply(state[6], 0x65) ^ _multiply(state[7], 0xc4);

    return result;
}

byte* AddRoundKey(byte state[], byte roundKey[]) {
    byte* result = (byte *)malloc(8 * sizeof(byte));

    for (int i=0;i<8;i++) {
        result[i] = state[i] ^ roundKey[i];
    }

    return result;
}

byte* encrypt(byte plaintext[], byte key[]) {
    byte** roundKey = GenerateKey(key);

    byte* state = (byte *)malloc(8 * sizeof(byte));
    for (int i=0;i<8;i++) {
        state[i] = plaintext[i];
    }

    state = AddRoundKey(state, roundKey[0]);

    for (int i=1;i<12;i++) {
        state = AddRoundKey(MDS(Shift_Bit_Byte(SubByte(state))), roundKey[i]);
    }

    //the last round is without MDS
    state = AddRoundKey(Shift_Bit_Byte(SubByte(state)), roundKey[12]);

    return state;
}

byte* decrypt(byte ciphertext[], byte key[]) {
    byte** roundKey = GenerateKey(key);

    byte* state = (byte *)malloc(8 * sizeof(byte));
    for (int i=0;i<8;i++) {
        state[i] = ciphertext[i];
    }

    state = AddRoundKey(state, roundKey[12]);

    for (int i=11;i>0;i--) {
        state = inv_MDS(AddRoundKey(inv_SubByte(inv_Shift_Bit_Byte(state)), roundKey[i]));
    }

    state = AddRoundKey(inv_SubByte(inv_Shift_Bit_Byte(state)), roundKey[0]);

    return state;
}

#endif