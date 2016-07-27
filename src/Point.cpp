#include "../includes/Npuzzle.hpp"

Point::Point()
{

}

Point::Point(int x, int y): _x(x), _y(y)
{

}

Point	&Point::operator=(const Point &other)
{
	_x = other._x;
	_y = other._y;
	return (*this);
}

int		Point::getX()
{
	return (_x);
}

int		Point::getY()
{
	return (_y);
}

void	Point::setX(int x)
{
	_x = x;
}

void	Point::setY(int y)
{
	_y = y;
}

void	Point::setCoord(int x, int y)
{
	_x = x;
	_y = y;
}