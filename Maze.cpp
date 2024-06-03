// Implementation of Maze class
// By max glover
//it 279
//maze implementaion

#include "Maze.h"
#include "DisjointSet.h"
using namespace std;

Maze::Maze(int rows, int cols)
{
    numRows = rows;
    numColumns = cols;
    int numCells = rows * cols;
    mazeWalls = new CellWalls[numCells];
    mazeWalls[numCells - 1].east = false;
}

Maze &Maze::operator=(const Maze &rhs)
{
    if (this != &rhs)
    {
        delete [] mazeWalls;
        this->copy(rhs);
    }
    return *this;
}

void Maze::generateMaze()
{
    int numCells = numRows * numColumns;
    DisjointSet mySet(numCells);
    bool mazeComplete = false;
    int numSets=numCells;

    //mySet.find(0)!=mySet.find(numCells-1)
    // to do -- see assignment instructions for details
    while (numSets>1)
    {
        int random = rand()%numCells;
        int direction = rand()%4;

        if (direction==0 && (random%numColumns)!=0)
        {
            if (mySet.find(random)!=mySet.find(random-1))
            {
                mazeWalls[random-1].east = false;
                mySet.doUnion(random, random-1);
                numSets--;
            }
            
        }
        else if (direction==0)
        {
            direction =2;
            if (mySet.find(random)!=mySet.find(random+1))
            {
                mazeWalls[random].east = false;
                mySet.doUnion(random, random+1);
                numSets--;
            }
            
        }
        if (direction==1 && (random+numColumns)<numCells-1)
        {
            if (mySet.find(random)!=mySet.find(random+numColumns))
            {
                mazeWalls[random].south = false;
                mySet.doUnion(random, random+numColumns);
                numSets--;
            }
            
        }
        else if (direction==1)
        {
            direction=3;
            if (mySet.find(random)!=mySet.find(random-numColumns))
            {
                mazeWalls[random-numColumns].south = false;
                mySet.doUnion(random, random-numColumns);
                numSets--;
            }
            
        }
        if (direction==2 && (random%numColumns)!=numColumns-1)
        {
            if (mySet.find(random)!=mySet.find(random+1))
            {
                mazeWalls[random].east = false;
                mySet.doUnion(random, random+1);
                numSets--;
            }
            
        }
        else if (direction==2)
        {
            direction = 0;
            if (mySet.find(random)!=mySet.find(random-1))
            {
                mazeWalls[random-1].east = false;
                mySet.doUnion(random, random-1);
                numSets--;
            }
            
        }
        if (direction==3 && (random-numColumns)>0)
        {
            if (mySet.find(random)!=mySet.find(random-numColumns))
            {
                mazeWalls[random-numColumns].south = false;
                mySet.doUnion(random, random-numColumns);
                numSets--;
            }
            
        }
        else if (direction==3 )
        {
            direction = 1;
            if (mySet.find(random)!=mySet.find(random+numColumns))
            {
                mazeWalls[random].south = false;
                mySet.doUnion(random, random+numColumns);
                numSets--;
            }
            
        }
        
    }
    mazeComplete = true;
    
}


void Maze::generateEarlyMaze()
{
    int numCells = numRows * numColumns;
    DisjointSet mySet(numCells);
    bool mazeComplete = false;

    // to do -- see assignment instructions for details
    while (mySet.find(0)!=mySet.find(numCells-1))
    {
        int random = rand()%numCells;
        int direction = rand()%4;

        if (direction==0 && (random%numColumns)!=0)
        {
            if (mySet.find(random)!=mySet.find(random-1))
            {
                mazeWalls[random-1].east = false;
                mySet.doUnion(random, random-1);
            }
            
        }
        else if (direction==0)
        {
            direction =2;
            if (mySet.find(random)!=mySet.find(random+1))
            {
                mazeWalls[random].east = false;
                mySet.doUnion(random, random+1);
            }
            
        }
        if (direction==1 && (random+numColumns)<numCells-1)
        {
            if (mySet.find(random)!=mySet.find(random+numColumns))
            {
                mazeWalls[random].south = false;
                mySet.doUnion(random, random+numColumns);
            }
            
        }
        else if (direction==1)
        {
            direction=3;
            if (mySet.find(random)!=mySet.find(random-numColumns))
            {
                mazeWalls[random-numColumns].south = false;
                mySet.doUnion(random, random-numColumns);
            }
            
        }
        if (direction==2 && (random%numColumns)!=numColumns-1)
        {
            if (mySet.find(random)!=mySet.find(random+1))
            {
                mazeWalls[random].east = false;
                mySet.doUnion(random, random+1);
            }
            
        }
        else if (direction==2)
        {
            direction = 0;
            if (mySet.find(random)!=mySet.find(random-1))
            {
                mazeWalls[random-1].east = false;
                mySet.doUnion(random, random-1);
            }
            
        }
        if (direction==3 && (random-numColumns)>0)
        {
            if (mySet.find(random)!=mySet.find(random-numColumns))
            {
                mazeWalls[random-numColumns].south = false;
                mySet.doUnion(random, random-numColumns);
            }
            
        }
        else if (direction==3 )
        {
            direction = 1;
            if (mySet.find(random)!=mySet.find(random+numColumns))
            {
                mazeWalls[random].south = false;
                mySet.doUnion(random, random+numColumns);
            }
            
        }
        
    }
    mazeComplete = true;
    
}

void Maze::print(ostream &outputStream)
{
    // print the top row of walls
    for (int i = 0; i < numColumns; i++)
        outputStream << " _";
    outputStream << '\n';
    for (int i = 0; i < numRows; i++)
    {
        int cellbase = i * numColumns;
        // print west wall (except at entrance)
        if (i == 0)
            outputStream << ' ';
        else
            outputStream << '|';
        for (int j = 0; j < numColumns; j++)
        {
            if (mazeWalls[cellbase + j].south)
                outputStream << '_';
            else
                outputStream << ' ';
            if (mazeWalls[cellbase + j].east)
                outputStream << '|';
            else
                outputStream << ' ';
        }
        outputStream << '\n';
    }
}

void Maze::copy(const Maze &orig)
{
    this->numRows = orig.numRows;
    this->numColumns = orig.numColumns;
    int numCells = numRows * numColumns;
    mazeWalls = new CellWalls[numCells];
    for (int i = 0; i < numCells; i++)
    {
        this->mazeWalls[i] = orig.mazeWalls[i];
    }
}
