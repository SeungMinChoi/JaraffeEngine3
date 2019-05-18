#include "JFEngine.h"

//#include <Windows.h>
#include <vector>
#include <algorithm>
#include <string>

#include "Foundation/JFTuple.h"
#include "Foundation/JFFunction.h"
#include "Foundation/JFTypeTraits.h"

#include <functional>

#include <type_traits>

void TestFunc(int a, int b)
{
    printf("hi");
}

class T
{
public:
	void operator () ()
	{

	}
};

class T1
{
public:

};

class T2 final
{
	void operator () ()
	{

	}
};

int main()
{
	JFTuple<int, float, double> a(5, 5.0f, 2.0);
	auto testValue0 = a.Item<0>();
	auto testValue1 = a.Item<1>();
	auto testValue2 = a.Item<2>();
	//td::index_sequence<1>::value_type;
	//auto asd = Get<0>(a);

    //std::index_sequence<1>::value_type;

	std::function funcTest = [a](int a, int b){};
	//auto sasas =[](int a, int b)
	//{};

	//FunctionTraits<decltype(sasas)> xzc;

	//JFFunction testFunc = [](int a, int b){};
	//
	//(*testFunc)(1, 2);
	//

	auto zxcz = [](int a, int b){};
	bool sadasd = IsCallable<decltype(zxcz)>::Value;

    JFFunction testFunc2{ TestFunc };
	//bool sadasd1 = testFunc2.Test();
	//bool zxczxcasd = testFunc2.t();
    testFunc2.Invoke(1, 2);

	auto labda = [a](int a, int b){  printf("hi"); };
	auto globalLabda = [](int a, int b){  printf("hi"); };
	JFFunction testFunc3 = std::move(labda);
	JFFunction testFunc4 = std::move(globalLabda);
	testFunc3.Invoke(1, 2);
	//bool sadasd2 = testFunc3.Test();
	//bool zxczxc = testFunc3.t();

	//testFunc3.Invoke(1, 2);
    
	//testFunc2.Invoke();
	//
	//(*testFunc2)(1, 2);

//	//(*testFunc)(1, 2);
//	//testFunc(1, 2);
//	//JFFunction<void(int, int)> testFunc2 = [](int a, int b)
	//{
	//
	//};

	

    JFSpinLock s;
    JFScopeLock<JFSpinLock> sl(s);

	JFApplication app;
	app.Run();

	JFVector2 v = JFVector2::Zero;
	v.Dot(JFVector2(1));

    system("pause");
    
	return 0;
}