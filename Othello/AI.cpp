#include "base.h"
#include "extern.h"
#include <algorithm>

string AI()
{
	random_shuffle(validCoord.begin(), validCoord.end());
	string AI=validCoord[0];
	return AI;
}