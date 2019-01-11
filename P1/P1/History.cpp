#include <iostream>

#include "globals.h"
#include "History.h"
#include "Arena.h"

using namespace std;

History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;
	for (int i = 0; i < MAXROWS; i++)
	{
		for (int j = 0; j < MAXCOLS; j++)
		{
			m_deaths[i][j] = 0;
		}
	}
}

bool History::record(int r, int c)
{
	if (r <= 0 || c <= 0 || r > m_rows || c > m_cols)
		return false;

	if (m_deaths[r][c] < 26)
		m_deaths[r][c]++;

	return true;
}

void History::display() const
{
	// Position (row,col) of the arena coordinate system is represented in
	// the array element grid[row-1][col-1]
	int r, c;

	// Draw the grid
	clearScreen();
	for (r = 0; r < m_rows; r++)
	{
		for (c = 0; c < m_cols; c++)
		{
			if (m_deaths[r][c] == 0)
				cout << ".";
			else
				cout << ('A' + (m_deaths[r][c] - 1));
		}

		cout << endl;
	}
	cout << endl;
}