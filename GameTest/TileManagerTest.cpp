#include "pch.h"
#include "CppUnitTest.h"

#include <Tiles.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameTest
{
	TEST_CLASS(Tile)
	{
	public:

		TEST_METHOD(TestGetType)
		{
			GameEngine::Tile a(GameEngine::TileType::Wall);
			GameEngine::Tile b(GameEngine::TileType::_Default);

			Assert::IsTrue(GameEngine::TileType::Wall == a.getType());
			Assert::IsTrue(GameEngine::TileType::_Default == b.getType());
		}
	};

	TEST_CLASS(TileManager)
	{
	public:

		TEST_METHOD(TestGetCreateTile)
		{
			std::shared_ptr<GameEngine::Tile> a = GameEngine::TileManager::getInstance().getTile(GameEngine::TileType::Wall);
			std::shared_ptr<GameEngine::Tile> b = GameEngine::TileManager::getInstance().getTile(GameEngine::TileType::Wall);
			std::shared_ptr<GameEngine::Tile> c = GameEngine::TileManager::getInstance().getTile(GameEngine::TileType::_Default);

			Assert::IsTrue(a == b);
			Assert::IsFalse(a == c);
			Assert::IsTrue(GameEngine::TileType::Wall == a->getType());
			Assert::IsTrue(GameEngine::TileType::_Default == c->getType());
		}

	};
}