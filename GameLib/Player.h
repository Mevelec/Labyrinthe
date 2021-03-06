#pragma once
#include "Position.h"
#include "Grid.h"

namespace GameEngine {
	/**
	 * Virtual class of IA.
	 */
	class IA {
	protected :
		size_t m_count;
	public :
		/**
		 * Constructor.
		 * by default count is to 0
		 */
		IA();
		/**
		 * virtual method to move the passed pos.
		 * 
		 * \param pos
		 */
		virtual void move(Position& pos) = 0;
		/**
		 * return the number of steps.
		 * 
		 * \return 
		 */
		inline size_t count() const{
			return m_count;
		};
	};

	/**
	 * .
	 * move forward and turn left if cant move
	 */
	class IA_Left : public IA{
		Position direction;
	public:
		/**
		 * Constructor.
		 * by default direction is to right
		 */
		IA_Left();
		/**
		 * move.
		 * move forward and turn left if cant move 
		 * \param pos
		 */
		virtual void move(Position& pos);
	};
	/**
	 * .
	 * move forward and turn right if cant move
	 */
	class IA_Right : public IA {
		Position direction;
	public:
		/**
		 * Constructor.
		 * by default direction is to right
		 */
		IA_Right();
		/**
		 * move.
		 * move forward and turn right if cant move
		 * \param pos
		 */
		virtual void move(Position& pos);
	};

	/**
	 * .
	 * move forward and turn in a random direction if is at an intersection
	 */
	class IA_Random : public IA {
		Position direction;
		IA_Left left;
		/**
		 * check if a pos is walkable in the current grid.
		 * 
		 * \param t
		 * \return true if can walk on
		 */
		bool walkable(TileType t);
		/**
		 * check if a pos is an intersection.
		 *
		 * \param t
		 * \return true if is an intersection
		 */
		bool isIntersect(const Position& pos);
	public:
		/**
		 * Constructor.
		 * by default direction is to right
		 */
		IA_Random();
		/**
		 * move.
		 * move forward and turn in a random direction if is at an intersection
		 * \param pos
		 */
		virtual void move(Position& pos);
	};
	
	/**
	 * .
	 * move in diagonal and turn left if cant move
	 */
	class IA_Stair : public IA {
		size_t rRot;
		size_t lRot;
		IA_Left left;
		Position direction;
	public:
		/**
		 * Constructor.
		 * by default direction is to rigth
		 * lRot and rRot to 0
		 */
		IA_Stair();
		/**
		 * move.
		 * move in diagonal and turn left if cant move
		 * \param pos
		 */
		virtual void move(Position& pos);
	};
	
	/**
	 * move forward and turn if can't move further but remember walked tiles. 
	 */
	class IA_Solve : public IA {
		Position direction;
		Grid::GridV m_grid;
		std::vector<Position> path;
		bool solved;
		/**
		 * check if a pos is walkable in the current grid.
		 *
		 * \param pos
		 * \return true if can walk on
		 */
		bool walkable(const Position& pos);
		size_t rewind = 0;
	public:
		/**
		 * Constructor.
		 * by default direction is to right and rewind to 0
		 */
		IA_Solve();
		/**
		 * move forward and turn if can't move further but remember walked tiles.
		 *
		 * \param pos
		 * \return
		 */
		virtual void move(Position& pos);
	};




	/**
	 * Virtual class.
	 * must be implemented to be runnable(moved by ticks)
	 */
	class Runnable {
	public :
		virtual void step() = 0;
	};

	/**
	 * Character class.
	 */
	class Character : public Runnable
	{
	protected :
		Position m_pos;
		IA* m_IA;
		bool m_finished;
	public :
		const char* m_name;

	public:
		/**
		 * construct a character.
		 * at pos (0,0) and given name and no IA
		 * \param 
		 */
		Character(const char*);
		/**
		 * construct a character.
		 * at given pos (0,0) and name and with no IA
		 * \param
		 */
		Character(const char*, const Position& pos);

		/**
		 * return current position of the character.
		 * 
		 * \return 
		 */
		inline const Position& getPosition() { return m_pos; }

		/**
		 * let the player increment it's steps .
		 * player move in time 
		 */
		virtual void step();
		/**
		 * check if the player finished the maze.
		 * 
		 * \return true if finished
		 */
		bool finished();

		/**
		 * set an IA to the character.
		 * 
		 * \param ia
		 */
		void setIA(IA* ia);

		/**
		 * acces the current IA.
		 * 
		 * \return 
		 */
		inline const IA* getIA() {
			return m_IA ;
		}

		/**
		 * set position of the character.
		 * 
		 * \param pos
		 */
		inline void setPos(const Position& pos) {
			m_pos = pos;
		}
	};
}