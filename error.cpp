#include "base.h"

void fatalError(unsigned ErrorCode)
{
    switch (ErrorCode)
    {
        case 1:
            CLS;
            cerr<<"Unknown Fatal Error Detected, Program Will Now Terminate."<<endl;
            PAUSE;
            exit(1);
        case 2:
            cerr<<"Unsupported Platform, Program Will Now Terminate."<<endl;
            PAUSE;
            exit(2);
        case 3:
            cerr<<"Cannot create necessary threads(UI)."<<endl;
            PAUSE;
            exit(3);
        case 4:
            cerr<<"Cannot create necessary threads(gameMain)."<<endl;
            PAUSE;
            exit(3);
        default:
            exit(233);
    }
}
