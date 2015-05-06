//Theodore Nguyen 704-156-701 CS32 homework 3 winter 15


#include <iostream>
#include <string>
using namespace std;


//The function literally follows the psuedocode given in the spec in the order 
//North, east, south, west. 
//
//Checks base case, marks position, checks direction for wall/marked/unmarked, then
//calls itself if satisfies, returning true if the calling is satsified
//
//returns false if nothing gets satisfied

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{	
	//cout << "(" << sr << "," << sc << ")" << endl;
	if(sr == er && sc == ec)
		return true;
	maze[sr][sc] = 'D';
	//for(int i = 0; i != nRows; i++)
	//	cout << maze[i] << endl;
	if(maze[sr-1][sc] == '.' && maze[sr-1][sc] != 'X' && maze[sr-1][sc] != 'D')
		if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
			return true;
	
	if(maze[sr][sc+1] == '.' && maze[sr][sc+1] != 'X' && maze[sr][sc+1] != 'D')
                if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
                        return true;
	
	if(maze[sr+1][sc] == '.' && maze[sr+1][sc] != 'X' && maze[sr+1][sc] != 'D')
                if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
                        return true;
	
	if(maze[sr][sc-1] == '.' && maze[sr][sc-1] != 'X' && maze[sr][sc-1] != 'D')
                if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
                        return true;
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
        
            if (pathExists(maze, 10,10, 6,4, 1, 1))
                cout << "Solvable!" << endl;
            else
                cout << "Out of luck!" << endl;
        }*/
