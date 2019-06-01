#include "JFEngine.h"

#include <iostream>
using namespace std;
using namespace JFFoundation;

int main()
{
    JFThread thread([]()
    {
        int count = 0;
        while (++count <= 20)
        {
            printf("Hellow thread world\n");
            Sleep(100);
        }
    });

   //InternalImpl::DeduceFunctionTraits<decltype(Test)>::FunctionType;
    //JFSpinLock s;
    //JFScopeLock<JFSpinLock> sl(s);

	//JFApplication app;
	//app.Run();

    Sleep(1000);

    system("pause");
    
	return 0;
}