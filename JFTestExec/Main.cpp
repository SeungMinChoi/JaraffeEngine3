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

using namespace JFFoundation;

void Test()
{

}

template<class T>
struct TestFunction
{
};

template<class R, class... P>
struct TestFunction<R(P...)>
{
	using Type = R(*)(P...);

	TestFunction()
	{

	}
	TestFunction(Type t)
		: testMember(t)
	{}

	TestFunction& operator = (const TestFunction t)
	{
		testMember = t.testMember;
		return *this;
	}

	R Invoke(P... params)
	{
		return testMember(params...);
	}

	Type testMember;
};

int main()
{
	auto lambda = []()
	{};

	std::function<void()> qwe;

	JFFunction FuncTest1 = [](){};
	JFFunction FuncTest2 = lambda;
	JFFunction FuncTest3(Test);

	TestFunction<int()> TestFunction1;
	{
		int a = 5;
		int b = 3;

		auto lambda2 = [&a, &b]()
		{
			return a + b;
		};

		auto lambda3 = []()
		{
			return 0;
		};

		//TestFunction<int()> z(lambda2);
		//TestFunction<int()> z2(lambda3);

		using LambdaType2 = decltype(lambda2);
		using LambdaType3 = decltype(lambda3);

		//TestFunction1 = TestFunction<int()>(lambda2);
		auto t = std::is_trivially_copyable<decltype(&LambdaType2::operator())>::value;
		auto t2 = std::is_trivially_copyable<decltype(&LambdaType3::operator())>::value;
		int qwe = 0;
	}

	TestFunction1.Invoke();

    //JFSpinLock s;
    //JFScopeLock<JFSpinLock> sl(s);

	//JFApplication app;
	//app.Run();

    system("pause");
    
	return 0;
}