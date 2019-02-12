#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
	string maze1[10] = {
	  "XXXXXXXXXX",
	  "X...X....X",
	  "XX.X..XX.X",
	  "XX...X...X",
	  "X.X.X..XXX",
	  "X...X.X.XX",
	  "X.X.X....X",
	  "XXX.X.XX.X",
	  "X...X..X.X",
	  "XXXXXXXXXX",
	};
	
	string maze2[10] = {
	  "XXXXXXXXXX",
	  "X...X....X",
	  "XX.X..XX.X",
	  "XX...X...X",
	  "X.X.X..XXX",
	  "X...X.X.XX",
	  "X.X.X....X",
	  "XXX.X.XXXX",
	  "X...X..X.X",
	  "XXXXXXXXXX",
	};
	
	string maze3[10] = {
	  "XXXXXXXXXX",
	  "XXXXXXX..X",
	  "XX.......X",
	  "X..X....XX",
	  "X..X..XXXX",
	  "X..XXX.X.X",
	  "XX...X...X",
	  "X....XX..X",
	  "XXX.....XX",
	  "XXXXXXXXXX",
	};
	
	string maze4[10] = {
	  "XXXXXXXXXX",
	  "XXXXXXX..X",
	  "XX.....X.X",
	  "X..X....XX",
	  "X..X..XXXX",
	  "X..XXX.X.X",
	  "XX...X...X",
	  "X....XX..X",
	  "XXX.....XX",
	  "XXXXXXXXXX",
	};

	assert(pathExists(maze1, 10, 10, 1, 3, 8, 8));
	assert(!pathExists(maze2, 10, 10, 1, 3, 8, 8));
	assert(pathExists(maze3, 10, 10, 5, 6, 2, 8));
	assert(!pathExists(maze4, 10, 10, 5, 6, 2, 8));

	cout << ":o my... big.... BOIIIII! YOU PASSED ALL TEST CASES!?!?!?!! uWu~ IM A REBEL JUST FOR KICKS YAAA" << endl;
}