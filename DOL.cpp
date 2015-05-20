#include "DOL.h"

gamecube::dolExecutable::dolExecutable(std::string diskRootFilePath)
{
    m_DolFilePath = diskRootFilePath + "/boot.dol";
}

bool gamecube::dolExecutable::readDolExecutable()
{
    DWORD dwBytesRead;
    m_hDolFile = CreateFile(m_DolFilePath.c_str(), GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(m_hDolFile == INVALID_HANDLE_VALUE) return false;
    if(ReadFile(m_hDolFile, &m_Dol, sizeof(m_Dol), &dwBytesRead, NULL)) return true;
    else return false;
}

unsigned char* gamecube::dolExecutable::textFilePos()
{
    unsigned char *ptr = m_Dol.textFilePos;
    return ptr;
}

unsigned char* gamecube::dolExecutable::dataFilePos()
{
    unsigned char *ptr = m_Dol.dataFilePos;
    return ptr;
}

unsigned char* gamecube::dolExecutable::textMemAdress()
{
    unsigned char *ptr = m_Dol.textMemAdress;
    return ptr;
}
unsigned char* gamecube::dolExecutable::dataMemAdress()
{
    unsigned char *ptr = m_Dol.dataMemAdress;
    return ptr;
}

unsigned char* gamecube::dolExecutable::textSectionSize()
{
    unsigned char *ptr = m_Dol.textSectionSize;
    return ptr;
}

unsigned char* gamecube::dolExecutable::dataSectionSize()
{
    unsigned char *ptr = m_Dol.dataSectionSize;
    return ptr;
}

unsigned char* gamecube::dolExecutable::bssMemAdress()
{
    unsigned char *ptr = m_Dol.bssMemAddress;
    return ptr;
}

unsigned char* gamecube::dolExecutable::bssSize()
{
    unsigned char* ptr = m_Dol.bssSize;
    return ptr;
}

unsigned char* gamecube::dolExecutable::entryPoint()
{
    unsigned char* ptr = m_Dol.entryPoint;
    return ptr;
}
