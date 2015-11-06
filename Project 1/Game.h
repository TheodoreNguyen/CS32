//Theodore Nguyen 704-156-701

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

class Pit;

class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nSnakes);
	~Game();

	// Mutators
	void play();

private:
	Pit* m_pit;
};

#endif // GAME_INCLUDED