#include "Player.h"
namespace GameEngine {

	Character::Character(const char* name) :
		m_name(name),
		m_pos(0, 0),
		m_IA(nullptr)
	{
		m_finished = false;
	}
	Character::Character(const char* name, const Position& pos) :
		m_name(name),
		m_pos(pos),
		m_IA(nullptr)
	{
		m_finished = false;
	}

	void Character::step()
	{
		if (m_IA) {
			m_IA->move(m_pos);
		}
	}

	bool Character::finished()
	{
		if (GridManager::getInstance().current()->operator->()->ator(m_pos) == TileType::End) {
			m_finished = true;
		}
		return m_finished;
	}

	void Character::setIA(IA* ia)
	{
		if (m_IA != nullptr) {
			delete m_IA;
		}
		m_IA = ia;
	}

	IA_Left::IA_Left() :
		direction({ 1, 0 })
	{
	}

	void IA_Left::move(Position& pos) {
		std::unique_ptr<Grid>* grid = GridManager::getInstance().current();
		if (grid) {
			if (GridManager::getInstance().current()->operator->()->ator(pos) == TileType::End) {
				return;
			}
			++m_count;

			//front
			TileType t = grid->operator->()->ator(pos + direction);
			if (t == TileType::PATH || t == TileType::End || t == TileType::Start) {
				pos.x += direction.x;
				pos.y += direction.y;
				return;
			}
			//left
			t = grid->operator->()->ator(pos + Rotate(direction, -90));
			if (t == TileType::PATH || t == TileType::End || t == TileType::Start) {
				direction = Rotate(direction, -90);
				pos.x += direction.x;
				pos.y += direction.y;
				return;
			}
			//back
			t = grid->operator->()->ator(pos + Rotate(direction, 180));
			if (t == TileType::PATH || t == TileType::End || t == TileType::Start) {
				direction = Rotate(direction, 180);
				pos.x += direction.x;
				pos.y += direction.y;
				return;
			}
			//right
			t = grid->operator->()->ator(pos + Rotate(direction, 90));
			if (t == TileType::PATH || t == TileType::End || t == TileType::Start) {
				direction = Rotate(direction, 90);
				pos.x += direction.x;
				pos.y += direction.y;
				return;
			}
		}
	}
	IA_Right::IA_Right() :
		direction({ 1, 0 })
	{
	}
	void IA_Right::move(Position& pos) {
		std::unique_ptr<Grid>* grid = GridManager::getInstance().current();
		if (grid) {
			if (GridManager::getInstance().current()->operator->()->ator(pos) == TileType::End) {
				return;
			}
			++m_count;

			//front
			TileType t = grid->operator->()->ator(pos + direction);
			if (t == TileType::PATH || t == TileType::End || t == TileType::Start) {
				pos.x += direction.x;
				pos.y += direction.y;
				return;
			}
			//left
			t = grid->operator->()->ator(pos + Rotate(direction, 90));
			if (t == TileType::PATH || t == TileType::End || t == TileType::Start) {
				direction = Rotate(direction, 90);
				pos.x += direction.x;
				pos.y += direction.y;
				return;
			}
			//back
			t = grid->operator->()->ator(pos + Rotate(direction, 180));
			if (t == TileType::PATH || t == TileType::End || t == TileType::Start) {
				direction = Rotate(direction, 180);
				pos.x += direction.x;
				pos.y += direction.y;
				return;
			}
			//right
			t = grid->operator->()->ator(pos + Rotate(direction, -90));
			if (t == TileType::PATH || t == TileType::End || t == TileType::Start) {
				direction = Rotate(direction, -90);
				pos.x += direction.x;
				pos.y += direction.y;
				return;
			}
		}
	}
	bool IA_Random::walkable(TileType t) {
		if (t == TileType::PATH || t == TileType::End || t == TileType::Start) {
			return true;
		}
		return false;
	}
	bool IA_Random::isIntersect(const Position& pos) {
		std::unique_ptr<Grid>* grid = GridManager::getInstance().current();

		TileType t1 = grid->operator->()->ator(pos + direction);
		TileType t2 = grid->operator->()->ator(pos + Rotate(direction, -90));
		TileType t3 = grid->operator->()->ator(pos + Rotate(direction, 180));
		TileType t4 = grid->operator->()->ator(pos + Rotate(direction, 90));
		if (static_cast<int>(walkable(t1)) + static_cast<int>(walkable(t2)) + static_cast<int>(walkable(t3)) + static_cast<int>(walkable(t4)) > 1) {
			return true;
		}
		return false;
	}
	IA_Random::IA_Random() :
		direction({ 1, 0 })
	{
	}
	void IA_Random::move(Position& pos) {
		std::unique_ptr<Grid>* grid = GridManager::getInstance().current();
		if (grid) {
			if (GridManager::getInstance().current()->operator->()->ator(pos) == TileType::End) {
				return;
			}
			++m_count;
			//front
			TileType t = grid->operator->()->ator(pos + direction);
			if (!isIntersect(pos)) {
				left.move(pos);
				return;
			}
			else {
				bool moved = false;
				while (!moved) {
					int c = rand() % 4;
					if (c == 0) {
						//left
						t = grid->operator->()->ator(pos + Rotate(direction, -90));
						if (walkable(t)) {
							direction = Rotate(direction, -90);
							pos.x += direction.x;
							pos.y += direction.y;
							return;
						}
					}
					else if (c == 1) {
						//back
						t = grid->operator->()->ator(pos + Rotate(direction, 180));
						if (walkable(t)) {
							direction = Rotate(direction, 180);
							pos.x += direction.x;
							pos.y += direction.y;
							return;
						}
					}
					else if (c == 2) {
						//back
						t = grid->operator->()->ator(pos + Rotate(direction, 90));
						if (walkable(t)) {
							direction = Rotate(direction, 90);
							pos.x += direction.x;
							pos.y += direction.y;
							return;
						}
					}
					else {
						//right
						t = grid->operator->()->ator(pos + direction);
						if (walkable(t)) {
							pos.x += direction.x;
							pos.y += direction.y;
							return;
						}
					}
				}
			}
		}
	}

	IA_Stair::IA_Stair() :
		direction({ 1, 0 }),
		rRot(0),
		lRot(0)
	{
	}

	void IA_Stair::move(Position& pos) {
		std::unique_ptr<Grid>* grid = GridManager::getInstance().current();
		if (grid) {
			if (GridManager::getInstance().current()->operator->()->ator(pos) == TileType::End) {
				return;
			}
			++m_count;

			//front
			TileType t = grid->operator->()->ator(pos + direction);
			if (t == TileType::PATH || t == TileType::End || t == TileType::Start) {
				pos.x += direction.x;
				pos.y += direction.y;
				return;
			}
			left.move(pos);
		}
	}
	IA_Solve::IA_Solve() :
		direction({ 1, 0 }),
		rewind(0)
	{
		m_grid = GridManager::getInstance().current()->operator->()->grid();
		solved = false;
	}

	bool IA_Solve::walkable(const Position& pos) {
		std::unique_ptr<Grid>* grid = GridManager::getInstance().current();
		if (grid && pos.x < m_grid[0].size() && pos.y < m_grid.size()) {
			TileType t1 = grid->operator->()->ator(pos);
			TileType t2 = m_grid[pos.y][pos.x];
			if ((t1 == TileType::PATH || t1 == TileType::End || t1 == TileType::Start) && (t2 == TileType::PATH || t2 == TileType::End || t2 == TileType::Start)) {
				return true;
			}
		}
		return false;
	}

	void IA_Solve::move(Position& pos) {
		if (!solved) {
			++m_count;
			bool moved = false;
			path.push_back(pos);
			//front
			if (walkable(pos + direction)) {
				pos.x += direction.x;
				pos.y += direction.y;
			}
			//left
			else if (walkable(pos + Rotate(direction, -90))) {
				direction = Rotate(direction, -90);
				pos.x += direction.x;
				pos.y += direction.y;
				moved = true;
			}
			//back
			else if (walkable(pos + Rotate(direction, 180))) {
				direction = Rotate(direction, 180);
				pos.x += direction.x;
				pos.y += direction.y;
				moved = true;
			}
			//right
			else if (walkable(pos + Rotate(direction, 90))) {
				direction = Rotate(direction, 90);
				pos.x += direction.x;
				pos.y += direction.y;
				moved = true;
			}
			else {
				if (path.size() > 2) {
					path.pop_back();
					path.pop_back();
					pos = path.back();
				}
			}

			if (GridManager::getInstance().current()->operator->()->ator(pos) == TileType::End) {
				solved = true;
				path.push_back(pos);
				moved = true;
				pos = { 0, 0 };
			}
			m_grid[pos.y][pos.x] = TileType::PATH_WALKED;
		}
		else {
			++rewind;
			if (rewind >= path.size()) rewind = 0;
			pos = path[rewind];

		}

	}
	IA::IA() : 
		m_count(0)
	{
	}
}
