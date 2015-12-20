#include "base.h"

void fatalError(unsigned ErrorCode)
{
    switch (ErrorCode)
    {
        case 1:
            CLS;
            cerr << "Unknown Fatal Error Detected, Program Will Now Terminate." << endl;
            PAUSE;
            exit(1);
        case 2:
            cerr << "Unsupported Platform, Program Will Now Terminate." << endl;
            PAUSE;
            exit(2);
        default:
            exit(233);
    }
}
