#pragma once
#include <memory>
#include <unordered_map>

namespace GameEngine {
	/**
	 * enum of tiles types.
	 */
	enum class TileType {
		_Default = 0,
		PATH     = 200,
		PATH_WALKED     = 201,
		Wall     = 100,
		Start    = 802,
		End      = 801
	};
}