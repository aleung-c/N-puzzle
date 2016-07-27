#include "Npuzzle.hpp"

/*
**	Point Object with x, y coordinates
*/
class Point
{
	public:
					Point();
					Point(int x, int y);
			Point	&operator=(const Point &other);

			int		getX();
			int		getY();

			void	setX(int x);
			void	setY(int y);
			void	setCoord(int x, int y);

	private:
			int		_x;
			int		_y;
};