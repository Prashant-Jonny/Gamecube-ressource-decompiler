#include "bannerfile.h"

const int lut5to8[] = { 0x00,0x08,0x10,0x18,0x20,0x29,0x31,0x39,
						0x41,0x4A,0x52,0x5A,0x62,0x6A,0x73,0x7B,
						0x83,0x8B,0x94,0x9C,0xA4,0xAC,0xB4,0xBD,
						0xC5,0xCD,0xD5,0xDE,0xE6,0xEE,0xF6,0xFF };
const int lut4to8[] = { 0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
						0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF };
const int lut3to8[] = { 0x00,0x24,0x48,0x6D,0x91,0xB6,0xDA,0xFF };


static inline gamecube::u32 gamecube::decode5A3(gamecube::u16 val)
{
    const u32 bg_color = 0x00000000;

	int r, g, b, a;

	if (val & 0x8000)
	{
		r = lut5to8[(val >> 10) & 0x1f];
		g = lut5to8[(val >> 5) & 0x1f];
		b = lut5to8[(val) & 0x1f];
		a = 0xFF;
	}
	else
	{
		a = lut3to8[(val >> 12) & 0x7];
		r = (lut4to8[(val >> 8) & 0xf] * a + (bg_color & 0xFF) * (255 - a)) / 255;
		g = (lut4to8[(val >> 4) & 0xf] * a + ((bg_color >> 8) & 0xFF) * (255 - a)) / 255;
		b = (lut4to8[(val) & 0xf] * a + ((bg_color >> 16) & 0xFF) * (255 - a)) / 255;
		a = 0xFF;
	}
	return (a << 24) | (r << 16) | (g << 8) | b;
}

void gamecube::decode5A3image(u32* dst, u16* src, int width, int height)
{
    for (int y = 0; y < height; y += 4)
    {
        for (int x = 0; x < width; x += 4)
        {
            for (int iy = 0; iy < 4; iy++, src += 4)
            {
                for (int ix = 0; ix < 4; ix++)
                {
                u32 RGBA = gamecube::decode5A3(gamecube::swap16(src[ix]));
                dst[(y + iy) * width + (x + ix)] = RGBA;
                }
            }
        }
    }
}

gamecube::gamecubeHeader::gamecubeHeader(std::string DiskRootFilePath)
{
    m_DiskRootFilePath = DiskRootFilePath;
}

bool gamecube::gamecubeHeader::isValid()
{
    DWORD dwBytesRead;
    std::string bannerFilePath = m_DiskRootFilePath + "/opening.bnr";
    HANDLE hTest = CreateFile(bannerFilePath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    char data[5] = "";
    ReadFile(hTest, &data,4, &dwBytesRead, NULL);
    if(strcmp(data, "BNR1") == 0 || strcmp(data, "BNR2") == 0){
        SetFilePointer(hTest, 0, 0, 0);
        CloseHandle(hTest);
        if(strcmp(data, "BNR1") == 0){BNR_TYPE = '1';}
        if(strcmp(data, "BNR2") == 0){BNR_TYPE = '2';}
        return true;
    }
    else {SetFilePointer(hTest, 0, 0, 0); CloseHandle(hTest); return false;}
}

std::string gamecube::gamecubeHeader::getBNRtype()
{
    if(BNR_TYPE == '1'){
        return "BNR1";
    }
    else return "BNR2";
}

bool gamecube::gamecubeHeader::readBannerFile()
{
    DWORD dwBytesRead;
    std::string bannerFilePath = m_DiskRootFilePath + "/opening.bnr";
    m_hBannerFile = CreateFile(bannerFilePath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(m_hBannerFile == INVALID_HANDLE_VALUE) return false;
    if(ReadFile(m_hBannerFile, &m_bannerStruct, sizeof(m_bannerStruct), &dwBytesRead, NULL)) return true; //on lit le bnr et on remplit la structures
    else return true;
}

std::vector<gamecube::u32> gamecube::gamecubeHeader::getBanner(/*int* pWidth, int* pHeight*/)
{
    std::vector<gamecube::u32>Buffer;
    Buffer.resize(DVD_BANNER_WIDTH * DVD_BANNER_HEIGHT);
    gamecube::decode5A3image(&Buffer[0], m_bannerStruct.graphicalData, DVD_BANNER_WIDTH, DVD_BANNER_HEIGHT);
    /*pWidth = DVD_BANNER_WIDTH;
    *pHeight = DVD_BANNER_HEIGHT;*/
    return Buffer;
}

void gamecube::gamecubeHeader::getBannerPNG(std::string fileOutput)
{

}

std::string gamecube::gamecubeHeader::gameName()
{
    std::string output = (const char*)m_bannerStruct.comment->shortTitle;
    return output;
}

std::string gamecube::gamecubeHeader::compagnyName()
{
    std::string output = (const char*)m_bannerStruct.comment->shortMaker;
    return output;
}

std::string gamecube::gamecubeHeader::fullGameTitle()
{
    std::string output = (const char*)m_bannerStruct.comment->longTitle;
    return output;
}

std::string gamecube::gamecubeHeader::compagnyFullName()
{
    std::string output = (const char*)m_bannerStruct.comment->longMaker;
    return output;
}

std::string gamecube::gamecubeHeader::gameDescriptionEN()
{
    std::string output = (const char*)m_bannerStruct.comment[0].comment;
    return output;
}

std::string gamecube::gamecubeHeader::gameDescriptionDE()
{
    std::string output = (const char*)m_bannerStruct.comment[1].comment;
    return output;
}

std::string gamecube::gamecubeHeader::gameDescriptionFR()
{
    std::string output = (const char*)m_bannerStruct.comment[2].comment;
    return output;
}

std::string gamecube::gamecubeHeader::gameDescriptionES()
{
    std::string output = (const char*)m_bannerStruct.comment[3].comment;
    return output;
}

std::string gamecube::gamecubeHeader::gameDescriptionIT()
{
    std::string output = (const char*)m_bannerStruct.comment[4].comment;
    return output;
}

std::string gamecube::gamecubeHeader::gameDescriptionNL()
{
    std::string output = (const char*)m_bannerStruct.comment[5].comment;
    return output;
}

DWORD WINAPI gamecube::gamecubeHeader::getError()
{
    return GetLastError();
}

gamecube::gamecubeHeader::~gamecubeHeader()
{
    //ctor
}
