#include "JFEngine.h"

//#include <Windows.h>
#include <vector>
#include <algorithm>
#include <string>

int main()
{
	JFThread t([]()
	{
		
	});

	JFApplication app;

	JFVector2 v = JFVector2::Zero;
	v.Dot(JFVector2(1));

	return 0;
}