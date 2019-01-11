#include <iostream>
#include <windows.h>

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
			m_deaths[i][j] = '.';
		}
	}
}

bool History::record(int r, int c)
{
	if (r < 1 || c < 1 || r > m_rows || c > m_cols)
		return false;
	
	if (m_deaths[r-1][c-1] == '.')
		m_deaths[r-1][c-1] = 'A';
	else if (m_deaths[r-1][c-1] < 'Z')
		m_deaths[r-1][c-1]++;

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
			cout << m_deaths[r][c];
		}

		cout << endl;
	}
	cout << endl;
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// YOU MAY MOVE TO ANOTHER FILE ALL THE CODE FROM HERE TO THE END OF FILE, BUT
// BE SURE TO MOVE *ALL* THE CODE; DON'T MODIFY OR REMOVE ANY #IFDEF, ETC.
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD upperLeft = { 0, 0 };
	DWORD dwCharsWritten;
	FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
		&dwCharsWritten);
	SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
	static const char* term = getenv("TERM");
	if (term == nullptr || strcmp(term, "dumb") == 0)
		cout << endl;
	else
	{
		static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
		cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
	}
}

#endif