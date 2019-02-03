#include <iostream>
#include <queue>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise

/*int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "X.XX.XX..X",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };
        
    if (pathExists(maze, 10,10, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}*/

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	queue<Coord> qu;

	//push starting point to stack
	Coord start(sr,sc);
	qu.push(start);

	//update maze to indicate point has now been found
	maze[sr][sc] = 'X';

	while (!qu.empty())
	{
		//set our current at the top of the stack
		Coord current = qu.front();
		qu.pop();

		//if our current position is the ending position, return true
		if (current.r() == er && current.c() == ec)
			return true;

		if (maze[current.r()+1][current.c()] == '.')
		{
			Coord temp(current.r()+1,current.c());
			qu.push(temp);
			maze[current.r()+1][current.c()] = 'X';
		}

		if (maze[current.r()][current.c()-1] == '.')
		{
			Coord temp(current.r(),current.c()-1);
			qu.push(temp);
			maze[current.r()][current.c()-1] = 'X';
		}

		if (maze[current.r()-1][current.c()] == '.')
		{
			Coord temp(current.r()-1,current.c());
			qu.push(temp);
			maze[current.r()-1][current.c()] = 'X';
		}

		if (maze[current.r()][current.c()+1] == '.')
		{
			Coord temp(current.r(),current.c()+1);
			qu.push(temp);
			maze[current.r()][current.c()+1] = 'X';
		}
	}
}



