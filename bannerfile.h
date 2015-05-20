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
class gamecubeHeader //this is the format of the file 'opening.bnr' found in the root directory of every Gamecube disc. This file is the little image that is displayed in the cube menu when inserting a disc into the gamecube, when in menu mode.
{
public:

    gamecubeHeader(std::string DiskRootFilePath); ///constructor need the gamecude root file path
    bool isValid(); ///this function check if the openning.bnr is valid, if he's valid, this function return true, else function return false
    std::string getBNRtype(); ///this function return the BNR type (BNR1 for US / JP Game, BNR2 for EU game)
    bool readBannerFile(); ///this function read the banner file and return true if no error occured, else function return false. *** You need to use this function to get the file details)
    std::string gameName(); ///this function return the game's name
    std::vector<u32> getBanner(/*int* pWidth, int* pHeight*/); ///this function return the banner (tiny image) by a vector of unsigned int
    void getBannerPNG(std::string fileOutput);
    std::string compagnyName(); ///this function return the name of the compagny that developp the game
    std::string fullGameTitle(); ///this function return the full game title
    std::string compagnyFullName(); ///this function return the full name of the compagny that developp the game
    std::string gameDescriptionEN(); ///this function return a short description of the game (LANG:ENGLISH)
    std::string gameDescriptionDE(); ///this function return a short description of the game (LANG:DEUTSCH)
    std::string gameDescriptionFR(); ///this function return a short description of the game (LANG:FRENCH)
    std::string gameDescriptionES(); ///this function return a short description of the game (LANG:SPANISH)
    std::string gameDescriptionIT(); ///this function return a short description of the game (LANG:ITALIAN)
    std::string gameDescriptionNL(); ///this function return a short description of the game (LANG:NEARLAND)
    DWORD WINAPI getError(); ///this function return any error (if occured), function just return the GetLastError() function
    ~gamecubeHeader();

private:
    std::string m_DiskRootFilePath;
    HANDLE m_hBannerFile;
    BNR_EU m_bannerStruct;
    unsigned char BNR_TYPE;
};
}
