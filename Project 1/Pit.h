//Theodore Nguyen 704-156-701

#ifndef PIT_INCLUDED
#define PIT_INCLUDED

#include "globals.h"
#include <string>
#include "history.h"
class Player;
class Snake;
using namespace std;

class Pit
{
public:
	// Constructor/destructor
	Pit(int nRows, int nCols);
	~Pit();

	// Accessors
	int     rows() const;
	int     cols() const;
	Player* player() const;
	int     snakeCount() const;
	int     numberOfSnakesAt(int r, int c) const;
	void    display(std::string msg) const;
	History& history();

	// Mutators
	bool   addSnake(int r, int c);
	bool   addPlayer(int r, int c);
	bool   destroyOneSnake(int r, int c);
	bool   moveSnakes();

private:
	int     m_rows;
	int     m_cols;
	History m_history;
	Player* m_player;
	Snake*  m_snakes[MAXSNAKES];
	int     m_nSnakes;
};

#endif // PIT_INCLUDED