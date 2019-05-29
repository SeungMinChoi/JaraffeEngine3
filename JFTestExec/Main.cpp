//#include "JFEngine.h"
#include "Foundation/JFFunction.h"
#include "Foundation/JFTypeTraits.h"

#include <iostream>
//#include <Windows.h>
#include <vector>
#include <algorithm>
#include <string>

#include <thread>
#include <functional>

using namespace std;
using namespace JFFoundation;

void Test()
{

}

int main()
{
	int a, b;
	auto lambda = [&a, &b]()
	{
		printf("Instance lambda");
	};

	auto lambda2 = []()
	{
		printf("GlobalFunction lambda");
	};
	JFFunction funcTest(lambda);
	JFFunction<void()> funcTest2(lambda);
	JFFunction funcTest3(lambda2);
	JFFunction funcTest4(Test);

    //auto t1 = IsGlobalLambda<decltype(lambda)>::Value;
    //auto t2 = IsGlobalLambda<decltype(lambda2)>::Value;
    //JFSpinLock s;
    //JFScopeLock<JFSpinLock> sl(s);

	//JFApplication app;
	//app.Run();

    system("pause");
    
	return 0;
}