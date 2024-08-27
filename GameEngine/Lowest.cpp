#include "Lowest.h"

using namespace std;

CustomBreakPoint::~CustomBreakPoint()
{
	if (id != 0)
	{
		cout << id << endl;
	}
}