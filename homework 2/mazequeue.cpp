//Theodore Nguyen 704-156-701 W2015 CS32 homework 2

#include <iostream>
#include <string>
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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	queue<Coord> coordQueue;
	coordQueue.push(Coord(sr,sc));
	maze[sr][sc] = 'D';
	do
	{
		Coord current = coordQueue.front();
	//	cout << "Current position is (" << current.r() << "," << current.c() << ")." << endl;
		//for (int i = 0; i != nRows; i++)
	//	{
		//	cout << maze[i] << endl;
	//	}
	//	cout << "------------------------------------------------------" << endl;
		coordQueue.pop();
		if(current.r() == er && current.c() == ec)
			return true;
		else
		{
			if(maze[current.r() - 1][current.c()] != 'X' && maze[current.r() - 1][current.c()] != 'D')
			{
				coordQueue.push(Coord(current.r() -1,current.c()));
				maze[current.r()-1][ current.c()] = 'D';
			}
			if(maze[current.r()][current.c()+1] != 'X' && maze[current.r()][current.c()+1] != 'D') 
			{
				coordQueue.push(Coord(current.r(), current.c() +1));
				maze[current.r()][current.c()+1] = 'D';
			}
			if(maze[current.r() + 1][current.c()] != 'X' && maze[current.r() + 1][current.c()] != 'D')
			{
				coordQueue.push(Coord(current.r()+1, current.c()));
				maze[current.r()+1][current.c()] = 'D';
			}
			if(maze[current.r()][current.c()-1] != 'X' && maze[current.r()][current.c()-1] != 'D')
			{
				coordQueue.push(Coord(current.r(), current.c()-1));
				maze[current.r()][current.c()-1] = 'D';
			}
		}
	}while(!coordQueue.empty());
	return false;
}

/*
int main()
{
             string maze[10] = {
                "XXXXXXXXXX",
                "X........X",
                "XX.X.XXXXX",
                "X..X.X...X",
                "X..X...X.X",
                "XXXX.XXX.X",
                "X.X....XXX",
                "X..XX.XX.X",
                "X...X....X",
                "XXXXXXXXXX"
            };
            if (pathExists(maze, 10,10, 6,4, 1,1))
                cout << "Solvable!" << endl;
            else
                cout << "Out of luck!" << endl;

}*/
