#include "pch.h"
#include "map_manager.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "enum.h"

void MapManager::move(int x, int y) {
	int move_x = _current_x + x;
	int move_y = _current_y + y;

	if (_columns <= move_x || _rows <= move_y || 0 > move_x || 0 > move_y) {
		return;
	}
	int current = _map[move_x][move_y];
	if (current == 1) {
		return;
	}

	_map[_current_x][_current_y] = 0;
	_current_x = move_x;
	_current_y = move_y;
	_map[_current_x][_current_y] = 2;
}

void MapManager::print_map() const {
	std::cout << "Print my map:" << std::endl;
	for (const auto& row : _map) {
		for (int cell : row) {
			switch (cell) {
			case 0:
				std::cout << "бр" << " ";
				break;
			case 1:
				std::cout << "бс" << " ";
				break;
			case 2:
				std::cout << "б┌" << " ";
				break;
			}
		}
		std::cout << std::endl;
	}
}


void MapManager::move_map() {
	int nInputKey = 0;

	while (true)
	{
		if (::_kbhit() > 0)
		{
			nInputKey = ::_getch();
			printf("Key : %d\n", nInputKey);
		}
		else nInputKey = 0;
		switch (static_cast<E_INPUT_KEY>(nInputKey))
		{
		case E_INPUT_KEY::E_INPUT_KEY_NONE: {
			break;
		}
		case E_INPUT_KEY::E_INPUT_KEY_UP: {
			std::cout << "up";
			move(-1, 0);
			print_map();
			break;
		}
		case E_INPUT_KEY::E_INPUT_KEY_DOWN: {
			std::cout << "down";
			move(1, 0);
			print_map();
			break;
		}
		case E_INPUT_KEY::E_INPUT_KEY_LEFT: {
			std::cout << "left";
			move(0, -1);
			print_map();
			break;
		}
		case E_INPUT_KEY::E_INPUT_KEY_RIGHT: {
			std::cout << "right";
			move(0, 1);
			print_map();
			break;
		}
		default: break;
		}

		::Sleep(100);
	}
}