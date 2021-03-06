#pragma once
#include <memory>
#include <vector>

#include "Tiles.h"
#include "Position.h"
#include <stdexcept>

namespace GameEngine {
	class GridManager;

	/**
	 * class containing data of a maze.
	 * a Grid contain TyileTypes values in a 2D Grid of size x, y
	 */
	class Grid
	{
	public : 
		using GridV = std::vector< std::vector<TileType>>;

	private :
		friend GridManager;
		GridV m_grid;
		size_t m_size_x, m_size_y;
	public:
		const wchar_t* m_name;
		/**
		 * Default construct of Grid.
		 * of size x and y and given name, the tiles are set to _Default type
		 * \param name
		 * \param x
		 * \param y
		 */
		Grid(const wchar_t* name, const size_t& x, const size_t& y);
		~Grid() noexcept;
		/**
		 * acces TileType at given Position.
		 * 
		 * \param pos
		 * \return TileType
		 */
		TileType at(const Position& pos);
		/**
		 * acces TileType type at given x and y.
		 *
		 * \param x
		 * \param y
		 * \return TileType
		 */
		TileType at(size_t x, size_t y);
		/**
		 * acces TileType at given x and y, and if do not exist(position not in grid return default or specified TileType).
		 *
		 * \param type by default _Default type
		 * \param x
		 * \param y
		 */
		TileType ator(size_t x, size_t y, TileType type = TileType::_Default);
		/**
		 * acces TileType at given Position, and if do not exist(position not in grid return default or specified TileType).
		 *
		 * \param pos
		 * \return TileType
		 */
		TileType ator(const Position& pos, TileType type = TileType::_Default);

		/**
		 * set the given TileType at the given position, if do not exist do nothing(position not in grid).
		 *
		 * \param pos
		 * \return TileType
		 */
		void set(TileType type, const Position& pos);
		/**
		 * set he given TileType at the given x and y, if do not exist do nothing(position not in grid).
		 *
		 * \param type
		 * \param x
		 * \param y
		 */
		void set(TileType type, size_t x, size_t y);

		/**
		 * return copy of size x.
		 * 
		 * \return 
		 */
		inline size_t size_x()
		{
			return m_size_x;
		}
		/**
		 * return copy of size y.
		 *
		 * \return
		 */
		inline size_t size_y()
		{
			return m_size_y;
		}

		/**
		 * return copy of the current grid.
		 *
		 * \return grid : std::vector< std::vector<TileType>>
		 */
		inline GridV grid() { return m_grid; }
	private :
		/**
		 * check if a pos exist in the grid.
		 * 
		 * \param pos
		 * \return trus if exist
		 */
		bool checkPos(const Position& pos);
		/**
		 * check if a pos exist in the grid .
		 *
		 * \param x
		 * \param y
		 * \return true if exist
		 */
		bool checkPos(size_t x, size_t y);

	};


	/**
	 * clas to manage grids.
	 * this class is a singleton
	 * all manipulation on a grid must passs through this class
	 */
	class GridManager {
		std::vector<std::unique_ptr<Grid>> grids;
		std::unique_ptr<Grid>* m_current;
	public:
		/**
		 * create a grid from a path with the given name.
		 * this method do not ensure the size of the final grid therfore evey line and cols in the given file must be of the same size
		 * \param path
		 */
		bool generate(const wchar_t* name, const char* path);
		/**
		 * load specified grid.
		 * 
		 * if i is out of range do nothing
		 * 
		 * \param i
		 */
		bool load(size_t i);
		
		/**
		 * return current loaded grid.
		 * 
		 * \return 
		 */
		std::unique_ptr<Grid>* current() const;


	// Singleton + constructor
	public:
		static GridManager& getInstance();
	private:
		GridManager();

	public:
		GridManager(GridManager const&) = delete;
		void operator=(GridManager const&) = delete;
	};
}

