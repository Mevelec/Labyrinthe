#include "pch.h"
#include "CppUnitTest.h"

#include <Grid.h>
#include <iostream>
#include <filesystem>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace GameTest
{
	TEST_CLASS(Grid)
	{
	public:

		TEST_METHOD(TestAt)
		{
			GameEngine::Grid g(L"lab", 5, 5);
			Assert::IsTrue(GameEngine::TileType::_Default == g.at(0, 0));
			try {
				Assert::IsTrue(GameEngine::TileType::_Default == g.at(5, 5));
				Assert::IsTrue(false);
			}
			catch (const std::out_of_range& e) {
				Assert::IsTrue(true);
			}
		}
		TEST_METHOD(TestAtor)
		{
			GameEngine::Grid g(L"lab", 5, 5);
			Assert::IsTrue(GameEngine::TileType::_Default == g.ator(0, 0));
			try {
				Assert::IsTrue(GameEngine::TileType::_Default == g.ator(5, 5));
				Assert::IsTrue(true);
			}
			catch (const std::out_of_range& e) {
				Assert::IsTrue(false);
			}
		}

		TEST_METHOD(TestSet)
		{
			GameEngine::Grid g(L"lab", 5, 5);
			Assert::IsTrue(GameEngine::TileType::_Default == g.at(0, 0));
			g.set(GameEngine::TileType::Wall, 0, 0);
			Assert::IsTrue(GameEngine::TileType::Wall == g.at(0, 0));

			try {
				g.set(GameEngine::TileType::Wall, 10, 0);
				Assert::IsTrue(true);
			}
			catch (const std::out_of_range& e) {
				Assert::IsTrue(false);
			}
		}
	};

	TEST_CLASS(GridManager)
	{
	public:

		TEST_METHOD(TestGenerate)
		{
			GameEngine::GridManager::getInstance().generate(L"lab1", "../../../Game/lab1_10x10.txt");
			Assert::IsTrue(GameEngine::GridManager::getInstance().load(0));
			std::unique_ptr<GameEngine::Grid>* g = GameEngine::GridManager::getInstance().current();
			Assert::IsNotNull(g);
			Assert::AreEqual(g->operator->()->m_name, L"lab1");
			Assert::AreEqual(g->operator->()->size_x(), static_cast<size_t>(31));
			Assert::AreEqual(g->operator->()->size_y(), static_cast<size_t>(21));
			Assert::IsTrue(g->operator->()->at(0, 0) == GameEngine::TileType::Start);
			Assert::IsTrue(g->operator->()->at(30, 20) == GameEngine::TileType::End);
			Assert::IsTrue(g->operator->()->at(0, 1) == GameEngine::TileType::PATH);
			Assert::IsTrue(g->operator->()->at(0, 3) == GameEngine::TileType::Wall);
		}
		TEST_METHOD(TestLoad)
		{
			if(!GameEngine::GridManager::getInstance().load(0)){
				GameEngine::GridManager::getInstance().generate(L"lab1", "../../../Game/lab1_10x10.txt");
			}
			GameEngine::GridManager::getInstance().generate(L"lab3", "../../../Game/lab3_3x3.txt");

			Assert::IsTrue(GameEngine::GridManager::getInstance().load(0));
			std::unique_ptr<GameEngine::Grid>* g = GameEngine::GridManager::getInstance().current();
			Assert::AreEqual(g->operator->()->m_name, L"lab1");
			Assert::AreEqual(g->operator->()->size_x(), static_cast<size_t>(31));
			Assert::AreEqual(g->operator->()->size_y(), static_cast<size_t>(21));
			GameEngine::GridManager::getInstance().load(1);
			g = GameEngine::GridManager::getInstance().current();
			Assert::AreEqual(g->operator->()->m_name, L"lab3");
			Assert::AreEqual(g->operator->()->size_x(), static_cast<size_t>(10));
			Assert::AreEqual(g->operator->()->size_y(), static_cast<size_t>(7));

		}
	};
}