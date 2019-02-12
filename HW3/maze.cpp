bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr < 0  ||  sr >= nRows  ||  sc < 0  || sc >= nCols  ||
        er < 0  ||  er >= nRows  ||  ec < 0  || ec >= nCols  ||
        maze[sr][sc] != '.'  ||  maze[er][ec] != '.')
       return false;

    if (sr == er  &&  sc == ec)
        return true;

    //update maze to indicate point has now been found
    maze[sr][sc] = 'X';

    //check each direction
    if (maze[sr-1][sc] != 'X')
    {
        if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
            return true;
    }
    if (maze[sr+1][sc] != 'X')
    {
        if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
    }
    if (maze[sr][sc-1] != 'X')
    {
        if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    }
    if (maze[sr][sc+1] != 'X')
    {
        if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;
    }

    return false;
}