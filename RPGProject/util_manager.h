#pragma once
#include "pch.h"
#include "enum.h"
#include <iostream>
#include <random>
#include <Windows.h>


class MoveManager {
public:
	static std::pair<int, int> random_direct() {
		const auto& directs = get_directs();
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, directs.size() - 1);

		auto direct = directs[dis(gen)];
		return std::make_pair(direct[0], direct[1]);
	}

	static const std::vector<std::vector<int>>& get_directs() {
		static const std::vector<std::vector<int>> directs = {
			{1, 0},   // 아래
			{0, 1},   // 오른쪽
			{-1, 0},  // 위
			{0, -1}   // 왼쪽
		};

		return directs;
	}
};

class ConsoleManager {
public:
	static void clear_console() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		csbi.dwCursorPosition.X = 0;
		csbi.dwCursorPosition.Y = 0;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), csbi.dwCursorPosition);
	}
	static void set_console_color(CONSOLE_COLOR color) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
	}
};