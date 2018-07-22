#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <assert.h>
#include <time.h>



#include <vector>
using namespace std;

#include "DSMTester.h"
#include "ExecutorHashTable.h"
#include "Server.h"
using namespace DS;

#include <iostream>
using namespace std;


int
main(int argc, char **argv)
{
	DSMTester   dsm;
	try
	{
		const int bufSize = 512;
		char buffer[bufSize];
		do
		{
			cout << ">";
			cin.getline(buffer, bufSize);
		} while (buffer[0] != 0 && dsm.executeCommand(buffer));
	}
	catch (char* str)
	{
		cout << "Caught unknown exception " << str << "\n";
	}
	cout << "Program ended";
	return 0;
}
