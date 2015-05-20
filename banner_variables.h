#ifndef BANNER_VARIABLES
#define BANNER_VARIABLES
#endif // BANNER_VARIABLES
#include <windows.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#define DVD_BANNER_WIDTH 96
#define DVD_BANNER_HEIGHT 32

namespace gamecube
{
typedef unsigned short u16;
typedef unsigned int u32;
static inline u32 decode5A3(u16 val);
//unsigned short _byteswap_ushort(unsigned short val) {return (val<<8) + (val>>8);}
inline u16 swap16(u16 _data) {return (_data<<8) + (_data>>8);}
void decode5A3image(u32* dst, u16* src, int width, int height);

struct DVDBannerComment
{
    char shortTitle[32]; // Short game title shown in IPL menu
    char shortMaker[32]; // Short developer, publisher names shown in IPL menu
    char longTitle[64]; // Long game title shown in IPL game start screen
    char longMaker[64]; // Long developer, publisher names shown in IPL game start screen
    char comment[128]; // Game description shown in IPL game start screen in two lines.
};

struct BNR_US //banner file format US / JP type
{
    u32 magicWord; // 'BNR2'
    u32 padding[7];
    u16 graphicalData[DVD_BANNER_WIDTH * DVD_BANNER_HEIGHT]; // RGB5A3 96x32 texture image
    DVDBannerComment comment[1]; // Comments in six languages (only 1 for BNR1 type)
};

struct BNR_EU //banner file format EU type
{
    u32 magicWord; // 'BNR2'
    u32 padding[7];
    u16 graphicalData[DVD_BANNER_WIDTH * DVD_BANNER_HEIGHT]; // RGB5A3 96x32 texture image
    DVDBannerComment comment[6]; // Comments in six languages (only 1 for BNR1 type)
};

static const u32 BNR1_SIZE = sizeof(BNR_US);
static const u32 BNR2_SIZE = sizeof(BNR_EU);
}
