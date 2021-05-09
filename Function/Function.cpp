#include "pch.h"
#include "CppUnitTest.h"
#include "Game.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Function
{
	TEST_CLASS(Function)
	{
	public:
		TEST_METHOD(endGame)
		{
			auto g = new Game(1, true);
		}
	};
}
