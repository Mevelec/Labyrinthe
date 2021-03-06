#include "Grid.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

namespace GameEngine {
	Grid:: Grid(const wchar_t* name, const size_t& x, const size_t& y) : m_name(name), m_size_x(x), m_size_y(y) {
		this->m_grid = std::vector<std::vector<TileType>>(m_size_x, std::vector<TileType>(m_size_y, TileType::_Default));
	}
	Grid::~Grid() noexcept {

	}
	TileType Grid::at(const Position& pos) {
		if (!checkPos(pos)) throw std::out_of_range("can't acces in grid");
		return m_grid[pos.y][pos.x];
	}
	TileType Grid::at(size_t x, size_t y) {
		if (!checkPos(x, y)) throw std::out_of_range("can't acces in grid");
		return m_grid[y][x];
	}

	TileType Grid::ator(size_t x, size_t y, TileType type) {
		if (!checkPos(x, y)) return type;
		return m_grid[y][x];
	}
	TileType Grid::ator(const Position& pos, TileType type) {
		if (!checkPos(pos)) return type;
		return m_grid[pos.y][pos.x];
	}

	void Grid::set(TileType type, const Position& pos) {
		if (!checkPos(pos)) return;
		m_grid[pos.y][pos.x] = type;
	}
	void Grid::set(TileType type, size_t x, size_t y) {
		if (!checkPos(x, y)) return;
		m_grid[y][x] = type;
	}


	bool Grid::checkPos(const Position& pos) {
		return checkPos(pos.x, pos.y);
	}
	bool Grid::checkPos(size_t x, size_t y) {
		if (x > m_size_x - 1 || y > m_size_y - 1) {
			return false;
		}
		return true;
	}







	GridManager& GridManager::getInstance()
	{
		static GridManager    instance;
		return instance;
	}

	GridManager::GridManager() :
		m_current(nullptr)
	{
	}
	bool GridManager::generate(const wchar_t* name, const char* path)
	{
		std::ifstream file;
		std::unique_ptr<Grid> grid = std::make_unique<Grid>(name, 0,0);
		file.open(path);
		if (!file) {
			return false;
		}

		char x;
		file.unsetf(std::ios_base::skipws);
		size_t line = 0;

		// iterate over each lines 
		std::string str;
		while (getline(file, str))
		{
			grid->m_grid.push_back(std::vector<TileType>(0));
			std::istringstream ss(str);
			ss.unsetf(std::ios_base::skipws);
			//iterate over each char in the current line
			while (ss >> x) {
				if (x == '#') {
					grid->m_grid[line].push_back(TileType::Wall);
				}
				else if (std::isspace(x)) {
					grid->m_grid[line].push_back(TileType::PATH);
				}
				else {
					grid->m_grid[line].push_back(TileType::_Default);
				}
			}
			line++;
		}
		grid->m_size_x = grid->m_grid[0].size();
		grid->m_size_y = line;

		grid->m_grid[0][0] = TileType::Start;
		grid->m_grid[grid->m_size_y-1][grid->m_size_x -1] = TileType::End;
		file.close();
		grids.push_back(std::move(grid));

		return true;
	}
	bool GridManager::load(size_t i)
	{
		if (grids.size() > i) {
			m_current = &grids[i];
			return true;
		}
		return false;
	}

	std::unique_ptr<Grid>* GridManager::current() const
	{
		return m_current;
	}

}