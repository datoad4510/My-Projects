#include "olcConsoleGameEngine.h"
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

struct Circle
{
	double m;
	int x;
	int y;
	int rad;
	int vx;
	int vy;
	Circle(){}
	Circle(int my_x, int my_y, int my_rad, double mass) 
	{ 
		x = my_x; 
		y = my_y;
		rad = my_rad;
		m = mass;
	}
	void operator()(int my_x, int my_y, int my_rad, double mass)
	{
		x = my_x;
		y = my_y;
		rad = my_rad;
		m = mass;
	}
};

class Circle_Collision : public olcConsoleGameEngine
{
public:
	Circle_Collision()
	{
		m_sAppName = L"Collisions";
	}
private:
	Circle c1;
	Circle c2;
	bool had_collision = false;

protected:
	void draw_circle(Circle c)
	{
		FillCircle(c.x, c.y, c.rad, 0x2588, FG_RED);
	}
	virtual bool OnUserCreate()
	{
		default_random_engine dre(time(NULL));
		uniform_int_distribution<int> uid_rad(1,min(m_nScreenWidth / 8, m_nScreenHeight / 8));
		int radius1 = uid_rad(dre);
		int radius2 = uid_rad(dre);
		uniform_int_distribution<short> uid_v(-10, 10);
		uniform_real_distribution<double> urd_m(0.1, 10);
		uniform_int_distribution<int> uid_x1(radius1, m_nScreenWidth - radius1);
		uniform_int_distribution<int> uid_y1(radius1, m_nScreenHeight - radius1);
		uniform_int_distribution<int> uid_x2(radius2, m_nScreenWidth - radius2);
		uniform_int_distribution<int> uid_y2(radius2, m_nScreenHeight - radius2);
		int x1 = uid_x1(dre);
		int y1 = uid_y1(dre);
		int x2 = uid_x2(dre);
		int y2 = uid_y2(dre);
		while ( (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) < (radius1 + radius2)*(radius1 + radius2) )
		{
			int x1 = uid_x1(dre);
			int y1 = uid_y1(dre);
			int x2 = uid_x2(dre);
			int y2 = uid_y2(dre);
		}
		c1(x1, y1, radius1,urd_m(dre));
		c2(x2, y2, radius2, urd_m(dre));
		c1.vx = uid_v(dre);
		c1.vy = uid_v(dre);
		c2.vx = uid_v(dre);
		c2.vy = uid_v(dre);
		
		draw_circle(c1);
		draw_circle(c2);
		return true;
	}
	virtual bool OnUserUpdate(float x)
	{
		Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ');//fill with spaces
		if ((c1.x - c2.x)*(c1.x - c2.x) + (c1.y - c2.y)*(c1.y - c2.y) <= (c1.rad + c2.rad)*(c1.rad + c2.rad) && had_collision == false)
		{
			int temp1 = c1.vx;
			c1.vx = ((c1.m - c2.m) / (c1.m + c2.m))*c1.vx + ((2 * c2.m) / (c1.m + c2.m))*c2.vx;
			c2.vx = ((2 * c1.m) / (c1.m + c2.m))*temp1 + ((c2.m - c1.m) / (c1.m + c2.m))*c2.vx;

			int temp2 = c1.vy;
			c1.vy = ((c1.m - c2.m) / (c1.m + c2.m))*c1.vy + ((2 * c2.m) / (c1.m + c2.m))*c2.vy;
			c2.vy = ((2 * c1.m) / (c1.m + c2.m))*temp1 + ((c2.m - c1.m) / (c1.m + c2.m))*c2.vy;
			had_collision = true;//this is for not getting stuck!
		}
		else
		{
			had_collision = false;
		}
		if (c1.x <= c1.rad && c1.vx < 0  || c1.x >= m_nScreenWidth - c1.rad && c1.vx > 0)
			c1.vx = -1 * c1.vx;
		if (c1.y <= c1.rad && c1.vy < 0 || c1.y >= m_nScreenHeight - c1.rad && c1.vy > 0)
			c1.vy = -1 * c1.vy;
		if (c2.x <= c2.rad && c2.vx < 0 || c2.x >= m_nScreenWidth - c2.rad && c2.vx > 0)
			c2.vx = -1 * c2.vx;
		if (c2.y <= c2.rad && c2.vy < 0 || c2.y >= m_nScreenHeight - c2.rad && c2.vy > 0)
			c2.vy = -1 * c2.vy;
		c1.x = c1.x + c1.vx;
		c1.y = c1.y + c1.vy;
		c2.x = c2.x + c2.vx;
		c2.y = c2.y + c2.vy;
		draw_circle(c1);
		draw_circle(c2);
		return true;
	}
};

int main()
{
	Circle_Collision program;
	program.ConstructConsole(200, 200, 2, 2);
	program.Start();
	cout << "aaaa" << endl;
}