#include "JFEngine.h"

//#include <Windows.h>
#include <vector>
#include <algorithm>
#include <string>

#include "Foundation/JFTuple.h"
#include "Foundation/JFFunction.h"

#include <functional>

void TestFunc(int a, int b)
{
	
}

int main()
{
	JFTuple<int, float, double> a(5, 5.0f, 2.0);
	auto testValue0 = a.Item<0>();
	auto testValue1 = a.Item<1>();
	auto testValue2 = a.Item<2>();
	//std::index_sequence<1>::value_type;
	//auto asd = Get<0>(a);

	std::function funcTest = [](int a, int b){};

	//auto sasas =[](int a, int b)
	//{};

	//FunctionTraits<decltype(sasas)> xzc;

	//JFFunction testFunc = [](int a, int b){};
	//
	//(*testFunc)(1, 2);
	//
	JFFunction testFunc2 = TestFunc;
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
    
	return 0;
}