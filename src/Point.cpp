#include "../includes/Npuzzle.hpp"

Point::Point(int x, int y): _x(x), _y(y)
{

}

int Point::getX()
{
	return (_x);
}

int Point::getY()
{
	return (_y);
}
