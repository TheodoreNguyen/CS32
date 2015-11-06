//Theodore Nguyen 704-156-701

#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;
	for (int r = 0; r < m_rows; r++)
		for (int c = 0; c < m_cols; c++)
			m_histgrid[r][c] = '.';
}

bool History::record(int r, int c)
{
	if (r <= 0 || r > m_rows || c <= 0 || c > m_cols)
		return false;
	else
	{
		if (m_histgrid[r][c] == '.')
			m_histgrid[r][c] = 'A';
		else if (m_histgrid[r][c] >= 'A' && m_histgrid[r][c] < 'Z')
			m_histgrid[r][c] = char(int(m_histgrid[r][c]) + 1);
		return true;
	}
}

void History::display() const
{
	clearScreen();
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
			cout << m_histgrid[r][c];
		cout << endl;
	}
	cout << endl;
}