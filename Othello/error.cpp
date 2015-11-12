#include "base.h"

void fatalError()
{
	SLP(300);
	CLS;
	cerr<<"Fatal Error Detected, Program Will Now Terminate."<<endl;
	PAUSE;
	exit(-1);
}