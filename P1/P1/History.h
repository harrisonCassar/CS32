#ifndef HISTORY_H

#define HISTORY_H

class Arena;

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
private:
	Arena* m_arena;
};

#endif