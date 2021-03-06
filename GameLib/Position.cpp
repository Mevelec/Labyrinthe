#include "Position.h"

namespace GameEngine {
	Position::Position(size_t x, size_t y) : x(x), y(y) {}

	bool Position::operator==(const Position& c) const {
		return (c.x == x && c.y == y);
	}

	Position Position::operator+(const Position& c) const
	{
		return Position(this->x + c.x, this->y + c.y );
	}

	void Position::set(size_t x, size_t y) {
		this->x = x;
		this->y = y;
	}

}