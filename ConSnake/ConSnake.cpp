#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>

using namespace std;

void what(int);
void gain();
void loss();
int rnd(int, int, int);
void delay(unsigned char, unsigned char, unsigned char, unsigned char);
int compare(int, int);
void frame();
void status();
void clear();

int dir, x = 0, y = 0, p = rnd(1, 60, 1), q = rnd(1, 25, 1), stage = 1, life = 4, points = 0, speed = 10, width = 1, h[100][2];

int main()
{
	int u = 0, c = 0, l = 0;
	u -= width;
	frame();
	do
	{
		delay(speed, 0, 0, 0);
		if (kbhit() != 0)
		{
			getch();
			dir = getch();
		}
		what(dir);
		gotoxy(p, q);
		cout << char(36);
		gotoxy(x, y);
		cout << char(1);
		status();
		h[l][0] = x;
		h[l][1] = y;
		l++;
		if (u < 0)
			u++;
		else
		{
			gotoxy(h[c][0], h[c][1]);
			cout << ' ';
			c++;
			if (c == width + 1)
				c = 0;
			if (l == width + 1)
				l = 0;
		};
	} while (dir != 27);
}

void what(int dir)
{
	switch (dir)
	{
	case 75: x--;	break;
	case 77: x++;	break;
	case 72: y--;	break;
	case 80: y++;
	}
	if (p == x && q == y)
		gain();
	else if (x >= 60 || x <= 0 + 1 || y >= 25 || y <= 0 + 1)
		loss();
}

int rnd(int a, int b, int c)
{
	int z = a - 1;
	randomize();
	for (; z < a || z == c;)
		z = random(b);
	return z;
}

int compare(int a, int b)
{
	int r = 0;
	for (int i = 0; i < 4; i++)
	{
		if (h[i][0] == a && h[i][1] == b)
			r = 1;
		else
		{
			r = 0;
			break;
		}
	}
	return r;
}

void delay(unsigned char n, unsigned char s, unsigned char m, unsigned char h)
{
	struct time t, T;
	gettime(&t);
	gettime(&T);
	t.ti_hour += h;
	t.ti_min += m;
	t.ti_sec += s;
	t.ti_hund += n;
	while (
		(T.ti_hour < t.ti_hour) ||
		(T.ti_hour == t.ti_hour && T.ti_min < t.ti_min) ||
		(T.ti_hour == t.ti_hour && T.ti_min == t.ti_min && T.ti_sec < t.ti_sec) ||
		(T.ti_hour == t.ti_hour && T.ti_min == t.ti_min && T.ti_sec == t.ti_sec && T.ti_hund < t.ti_hund))
		gettime(&T);
}

void gain()
{
	cout << '\a';
	width++;
	points += 100 * stage / 2;
	p = rnd(2, 60, x);
	q = rnd(2, 25, y);
	if (life < 9 && points > 2500)
	{
		life++;
		points -= 2500;
	}
	if (life * points > stage * 2000 && stage < 9)
	{
		clear();
		stage++;
		if (speed > 0)
			speed--;
		if (life < 9)
			life++;
		else
			points += 1000;
	}
}

void loss()
{
	cout << '\a';
	life--;
	if (life < 0)
	{
		gotoxy(26, 12);
		cout << "Game Over";
	}
	x = rnd(1, 60, x);
	y = rnd(1, 25, y);
}

void frame()
{
	clrscr();
	int i;
	for (i = 0; i < 22; i++)
		cout << char(-51);
	cout << "\4THE REAL SNAKE\4";
	for (i = 0; i < 22; i++)
		cout << char(-51);
	for (i = 0; i < 6; i++)
		cout << char(-51);
	cout << ">STATUS<";
	for (i = 0; i < 6; i++)
		cout << char(-51);
	gotoxy(68, 4);
	cout << "Stage:";
	gotoxy(69, 10);
	cout << "Life";
	gotoxy(68, 16);
	cout << "Points";
	gotoxy(68, 18);
	cout << char(36);
	for (i = 2; i < 25; i++)
	{
		gotoxy(1, i);
		cout << char(-70);
		gotoxy(60, i);
		cout << char(-70);
		gotoxy(80, i);
		cout << char(-70);
	}
	for (i = 0; i < 79; i++)
		cout << char(-51);
	gotoxy(1, 1);
	cout << char(-55);
	gotoxy(60, 1);
	cout << char(-53);
	gotoxy(80, 1);
	cout << char(-69);
	gotoxy(1, 25);
	cout << char(-56);
	gotoxy(60, 25);
	cout << char(-54);
	//	gotoxy(80,25);
	//		cout << char(-68);
	//	gotoxy(1,1);
	gotoxy(62, 23);
	cout << " UJJWAL SINGH -XI";
}

void status()
{
	int i;
	gotoxy(70, 6);
	cout << stage;
	gotoxy(61, 12);
	for (i = 0; i < 18; i++)
		cout << ' ';
	gotoxy(70 - 2 * (life / 2), 12);
	for (i = life; i > 0; i--)
		cout << "\3 ";
	if (life % 2 == 0)
		cout << '.';
	gotoxy(70, 18);
	cout << points;
}

void clear()
{
	for (int i = 2; i < 25; i++)
	{
		gotoxy(2, i);
		for (int j = 0; j < 58; j++)
			cout << ' ';
	}
}