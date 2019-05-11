#include "JFEngine.h"

//#include <Windows.h>
#include <vector>
#include <algorithm>
#include <string>

#include "Foundation/JFTuple.h"

int main()
{
	JFTuple<int, float, double> a(5, 5.0f, 2.0);
	auto testValue0 = a.Item<0>();
	auto testValue1 = a.Item<1>();
	auto testValue2 = a.Item<2>();
	
	//auto asd = Get<0>(a);

    JFSpinLock s;
    JFScopeLock<JFSpinLock> sl(s);

	JFApplication app;
	app.Run();

	JFVector2 v = JFVector2::Zero;
	v.Dot(JFVector2(1));
    
	return 0;
}