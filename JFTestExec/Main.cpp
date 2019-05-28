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

class Hi
{

};

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

	std::function qw = Test;

	bool test = IsCallable<decltype(Test)>::Value;
	FunctionTraits<decltype(&Test)>::FunctionPrototype;

	std::is_class<Hi>;

	//void(*Test)() = lambda2;

	int t = IsGlobalLambda<decltype(lambda)>::Value;
	int t2 = IsGlobalLambda<decltype(lambda2)>::Value;

	//std::is_class<decltype(Test)>::
	int t5 = __is_class(decltype(Test));

	int t4 = IsClass<Hi>::Value;

	//JFFunction funcTest4(Test);

    //JFSpinLock s;
    //JFScopeLock<JFSpinLock> sl(s);

	//JFApplication app;
	//app.Run();

    system("pause");
    
	return 0;
}