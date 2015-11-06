//Theodore Nguyen 704-156-701

#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
private:
	int m_rows;
	int m_cols;
	char m_histgrid[20][40];
};

#endif // HISTORY_INCLUDED