#pragma once
#include <cmath>

#define PI 3.14159265

namespace GameEngine {
    /**
     * Position structure.
     */
	struct Position {
        /**
         * construct a position.
         * by default at pos(0,0)
         * \param x
         * \param y
         */
		Position(size_t x = 0, size_t y = 0);

		int x;
		int y;

        /**
         * compare 2 position.
         * 
         * \param c
         * \return true if are at the same coordinates
         */
		bool operator==(const Position& c) const;
        /**
         * add 2 coordinates together.
         * 
         * \param c
         * \return Position
         */
		Position operator+(const Position& c) const;
		void set(size_t x, size_t y);


	};
    static const double DegToRad = PI / 180;

    /**
     * rotate a position of given radian.
     * 
     * \param pos
     * \param radians
     * \return 
     */
    static Position RotateRadians(const Position& pos, double radians)
    {
        int ca = std::cos(radians);
        int sa = std::sin(radians);
        return Position(ca * pos.x - sa * pos.y, sa * pos.x + ca * pos.y);
    }

    /**
     * rotate a position of given degree.
     *
     * \param pos
     * \param radians
     * \return
     */
    static Position Rotate(const Position& pos, double degrees)
    {
        return RotateRadians(pos, degrees * DegToRad);
    }


}