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
    JFFunction<void()> funcTest5;
    {
        int a, b;
        auto lambda = [a, b]()
        {
            printf("Instance lambda");
        };

        auto lambda2 = [](int i)
        {
            printf("GlobalFunction lambda");
        };
        JFFunction funcTest(lambda);
        JFFunction<void()> funcTest2(lambda);
        JFFunction funcTest3(lambda2);
        JFFunction funcTest4(Test);

        funcTest5 = lambda;
    }

    funcTest5.Invoke();
    
   //InternalImpl::DeduceFunctionTraits<decltype(Test)>::FunctionType;
    //JFSpinLock s;
    //JFScopeLock<JFSpinLock> sl(s);

	//JFApplication app;
	//app.Run();

    system("pause");
    
	return 0;
}