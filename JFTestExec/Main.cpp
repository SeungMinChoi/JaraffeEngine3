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

    JFString str("hi every one");
    str.Erase(10,3);
    str.Append("ne");
    str.Reverse();

    JFStringW strW(L"안녕하세요.");
    strW.Erase(1, 2);
    strW.Append(L"ne");
    strW.Reverse();

    Sleep(1000);

    system("pause");
    
	return 0;
}