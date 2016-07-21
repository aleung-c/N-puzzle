#include "Npuzzle.hpp"

/*
**	Point Object with x, y coordinates
*/
class Point
{
	public:
				Point(int x, int y);
			int getX();
			int getY();
	private:
			int _x;
			int _y;
};