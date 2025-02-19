/* 
	petals.cpp
	MSVC, ISO C++20
	growing and rotating petals - use full screen for best effect
*/

#include "pch.h"
const float pi2 = 2 * M_PI;
const int rows = 29; 
const int columns = 95;
const int size = rows * columns;
const int m_y = (rows + 1) / 2;
const int m_x = (columns + 1) / 2;

// r and c must be odd
char display[rows][columns];
const char symbols[] = { '*', '+', '-', '$', '#', '@', '^' };

static void display_points() {
	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < columns; ++x) {
			std::cout << display[y][x];
		}
		std::cout << '\n';
	}
	// move cursor up n lines w ANSI escape \033[nA
	std::cout << "\033[" << rows << "A";
};

void plot(int x, int y) {
	char c;
	c = symbols[rand() % 7];
	display[y][x] = c;
}
static int normalize_x(const int& x) {
	int normalized = m_x + x;
	//  clamp x within range
	return std::max(0, std::min(columns - 1, normalized));
};
static int normalize_y(const int& y) {
	int normalized = m_y + y;
	// clamp y within range
	return std::max(0, std::min(rows - 1, normalized));
};
int main()
{
	const int r = 22;
	float dt = 0;
	float n = -0.25;
	bool inc = true;
	while (true) {
		std::memset(display, ' ', size);
		// as theta 0->2pi, for radius 0->r, as time varies, calc x, y for given radius at each angle
		// 0 < n < 6 as well
		n += inc ? 0.25 : -0.25;
		if (n >= 6) {
			inc = false;
		}
		else if (n <= 0) {
			inc = true;
		}

		for (float theta = 0; theta < pi2; theta += 0.01) {
			// r = a*cos(ktheta) - > scaling r
			int r_ = r * std::abs(cos(n * theta + dt));
			int x = normalize_x(static_cast<int>(r_ * cos(theta)));
			int y = normalize_y(static_cast<int>(r_ * sin(theta)));
			plot(x, y);
		}
		display_points();
		dt += 0.5;
	}
}
