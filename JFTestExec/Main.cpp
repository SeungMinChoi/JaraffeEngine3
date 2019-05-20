#include "JFEngine.h"

#include <iostream>
//#include <Windows.h>
#include <vector>
#include <algorithm>
#include <string>

#include <thread>

int main()
{
    JFSpinLock s;
    JFScopeLock<JFSpinLock> sl(s);

	JFApplication app;
	app.Run();

	JFVector2 v = JFVector2::Zero;
	v.Dot(JFVector2(1));

    system("pause");
    
	return 0;
}