#pragma once

constexpr int MAP_RAND = 0;
constexpr int MAP_WALL = 1;
constexpr int MAP_PLAYER = 2;
constexpr int MAP_MONSTER = 3;
constexpr int RAND_PERCENT = 20;
constexpr int FLOOD_START_IDX = 100;

enum class E_CLASS : int {
	E_CLASS_NONE = 0,
	E_CLASS_KNIGHT = 1,
	E_CLASS_MAGICIAN = 2,
	E_CLASS_ARCHER = 3
};

enum class E_INPUT_KEY : int {
	E_INPUT_KEY_NONE = 0,
	E_INPUT_KEY_UP = 72,
	E_INPUT_KEY_DOWN = 80,
	E_INPUT_KEY_LEFT = 75,
	E_INPUT_KEY_RIGHT = 77
};

enum class CONSOLE_COLOR : short {
	BLACK = 0,
	DARK_BLUE = 1,
	DARK_GREEN = 2,
	DARK_SKYBLUE = 3,
	DARK_RED = 4,
	DARK_VOILET = 5,
	DAKR_YELLOW = 6,
	GRAY = 7,
	DARK_GRAY = 8,
	BLUE = 9,
	GREEN = 10,
	SKYBLUE = 11,
	RED = 12,
	VIOLET = 13,
	YELLOW = 14,
	WHITE = 15
};

enum class PLAYER_STATUS : short {
	NONE = 0,
	MONSTER = 1
};