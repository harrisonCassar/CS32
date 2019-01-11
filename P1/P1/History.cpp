#include "History.h"
#include "Arena.h"

History::History(int nRows, int nCols)
{

}

bool History::record(int r, int c)
{
	if (r <= 0 || c <= 0 || r > m_arena->rows() || c > m_arena->cols())
		return false;

}

void History::display() const
{

}