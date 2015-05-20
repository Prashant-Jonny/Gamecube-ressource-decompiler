#include <iostream>
#include <conio.h>
#include "DOL.h"
#include "bannerfile.h"

using namespace std;

int main()
{
    std::string GCDiskPAth = "./Mario Sunshine Decompilated/Disc Extracted";
    std::vector <gamecube::u32>BannerImage;
    gamecube::gamecubeHeader gcHeader(GCDiskPAth);
    gamecube::dolExecutable dolExec(GCDiskPAth);
    cout << "Gamecube CD Res decompiler V0.5 !" << endl << endl;
    if(!gcHeader.isValid()){
        cout<< "Error, banner file isnt  valid !" << endl;
        cout<< "Last error:" << gcHeader.getError() << endl;
        getch();
        return -1;
    }
    if(!gcHeader.readBannerFile()){
        cout << "Error:" << gcHeader.getError() << " when trying to read the banner file !" << endl;
        getch();
        return -1;
    }
    cout << "*** BNR FILE INFORMATION ***" << endl;
    std::cout << "game name:" << gcHeader.gameName() << endl;
    std::cout << "compagny name:" << gcHeader.compagnyName() << endl;
    std::cout << "Compagny full name:" << gcHeader.compagnyFullName() << endl;
    std::cout << "Full game title:" << gcHeader.fullGameTitle() << endl;
    std::cout << "Game description FR:" << gcHeader.gameDescriptionFR() << endl;
    BannerImage = gcHeader.getBanner();
    std::cout << std::endl;
    if(!dolExec.readDolExecutable()){
        cout<<"Error when trying to read the dol executable file." << endl;
        getch();
        return -1;
    }
    std::cout <<"*** DOL executable ***" << std::endl;
    std::cout <<"Text file pos:"<< std::hex<<"0x"<<std::uppercase<<(int)dolExec.textFilePos()<<endl;
    std::cout <<"Data file pos:"<<std::hex<<"0x"<<std::uppercase<<(int)dolExec.dataFilePos()<<endl;
    std::cout<<"Text mem adress:"<<std::hex<<"0x"<<std::uppercase<<(int)dolExec.textMemAdress()<<endl;
    std::cout<<"Data mem adress:"<<std::hex<<"0x"<<std::uppercase<<(int)dolExec.dataMemAdress()<<endl;
    std::cout<<"Text section size:"<<std::hex<<"0x"<<std::uppercase<<(int)dolExec.textSectionSize()<<endl;
    std::cout<<"Data section size:"<<std::hex<<"0x"<<std::uppercase<<(int)dolExec.dataSectionSize()<<endl;
    std::cout<<"BSS Mem adress:"<<std::hex<<"0x"<<std::uppercase<<(int)dolExec.bssMemAdress()<<endl;
    std::cout<<"BSS Section size:"<<std::hex<<"0x"<<std::uppercase<<(int)dolExec.bssSize()<<endl;
    std::cout<<"Entry point:"<<std::hex<<"0x"<<std::uppercase<<(int)dolExec.entryPoint()<<endl;

    return 0;
}
