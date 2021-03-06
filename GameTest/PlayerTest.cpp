#include "pch.h"
#include "CppUnitTest.h"

#include <Player.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameTest
{
	TEST_CLASS(Position)
	{
	public:

		TEST_METHOD(TestCreate)
		{
			GameEngine::Position pos1;
			Assert::AreEqual(0, pos1.x);
			GameEngine::Position pos2(2, 4);
			Assert::AreEqual(2, pos2.x);
			Assert::AreEqual(4, pos2.y);
		}
		TEST_METHOD(TestEqual)
		{
			GameEngine::Position pos1;
			GameEngine::Position pos2(2, 3);
			GameEngine::Position pos3(2, 3);
			Assert::IsFalse(pos1 == pos2);
			Assert::IsTrue(pos2 == pos3);
		}
		TEST_METHOD(TestAdd)
		{
			GameEngine::Position pos1(1, 1);
			GameEngine::Position pos2(2, 3);
			GameEngine::Position pos3(3, 4);

			Assert::IsTrue(pos2+pos1 == pos3);
		}
	};

	TEST_CLASS(Player)
	{
	public:
		
		TEST_METHOD(TestGetPos)
		{
			GameEngine::Character c1("character 1");
			GameEngine::Character c2("character 2", {2, 2});

			GameEngine::Position pos;
			Assert::IsTrue(pos == c1.getPosition());
			pos.set(2, 2);
			Assert::IsTrue(pos == c2.getPosition());
		}
	};
};

