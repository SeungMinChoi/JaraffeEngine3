#include "JFSize.h"

using namespace JFFramework;

const JFSize JFFramework::JFSize::Zero = JFSize();

JFFramework::JFSize::JFSize()
	: width(0)
	, height(0)
{}

JFFramework::JFSize::JFSize(float s)
	: width(s)
	, height(s)
{}

JFFramework::JFSize::JFSize(float _width, float _height)
	: width(_width)
	, height(_height)
{}
