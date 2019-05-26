//#include "JFEngine.h"
#include "Foundation/JFFunction.h"

#include <iostream>
//#include <Windows.h>
#include <vector>
#include <algorithm>
#include <string>

#include <thread>
#include <functional>

using namespace JFFoundation;

void Test()
{

}

int main()
{
	auto lambda = []()
	{};


	std::function<void()> qwe;

	JFFunction FuncTest1 = [](){};
	JFFunction FuncTest2 = lambda;
	JFFunction FuncTest3(Test);

    //JFSpinLock s;
    //JFScopeLock<JFSpinLock> sl(s);

	//JFApplication app;
	//app.Run();

    system("pause");
    
	return 0;
}