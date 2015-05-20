#include <windows.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

namespace gamecube
{
struct DOL //structure used by dolExecutable class
{
    unsigned char textFilePos[0x001B]; //Text[0..6] sections File Positions
    unsigned char dataFilePos[0x002B]; //Data[0..10] sections File Positions
    unsigned char textMemAdress[0x001B]; //Text[0..6] sections Mem Address
    unsigned char dataMemAdress[0x002B]; //Data[0..10] sections Mem Address
    unsigned char textSectionSize[0x001B]; //Text[0..6] sections Sizes
    unsigned char dataSectionSize[0x002B]; //Data[0..10] sections Sizes
    unsigned char bssMemAddress[0x04]; //BSS Mem address
    unsigned char bssSize[0x04]; //BSS Size
    unsigned char entryPoint[0x04]; //the entry point
    unsigned char unusued[0x1C]; //unusued data
    //unsigned char data[3E77A1]; //dol data
};
class dolExecutable //This is a custom GameCube program file format, which is directly booted by GameCubes' BIOS (to be exact, by the apploader on retail discs. a different apploader could well load a binary in whatever different format.).
{
public:

    dolExecutable(std::string DiskRootFilePath);
    bool readDolExecutable();
    unsigned char* textFilePos();
    unsigned char* dataFilePos();
    unsigned char* textMemAdress();
    unsigned char* dataMemAdress();
    unsigned char* textSectionSize();
    unsigned char* dataSectionSize();
    unsigned char* bssMemAdress();
    unsigned char* bssSize();
    unsigned char* entryPoint();

private:
    std::string m_DolFilePath;
    DOL m_Dol;
    HANDLE m_hDolFile;
};
}
