#include "pch.h"
#include "CppUnitTest.h"
#include "../spaceInvaders/Game.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Function
{
	TEST_CLASS(Function)
	{
	public:
		TEST_METHOD(GameTest1)
		{
			Assert::AreEqual(1, 1);
		}
	};
}
