/* ****************************************************************************** */
// Programme Banner: File.h
// Created by Shadan Ibrahim
// Start Date: 10/03/2021
// End Date: 19/04/2021
// Description: This file includes all the headers, definitions, and global variables used in File.c and main.c
/* ****************************************************************************** */

//#ifndef FILEPROCESSING_FILE_H
//#define FILEPROCESSING_FILE_H
//#endif


//Libraries used
#include <stdio.h>
#include <stdlib.h>

//definiions
#define col 6
#define row 8
#define threshold 7


//definition of different maze to be tested on
#define Maze_1 "C:\\Users\\Shadan\\Desktop\\MazeMicromouse\\Maze_1.txt" //comp
#define Maze_2 "C:\\Users\\Shadan\\Desktop\\MazeMicromouse\\Maze_2.txt" //closed end
#define Maze_3 "C:\\Users\\Shadan\\Desktop\\MazeMicromouse\\Maze_3.txt" //to the right
#define Maze_4 "C:\\Users\\Shadan\\Desktop\\MazeMicromouse\\Maze_4.txt" //to the right Hcost
#define Maze_5 "C:\\Users\\Shadan\\Desktop\\MazeMicromouse\\Maze_5.txt" //to the right Hcost
#define Maze_6 "C:\\Users\\Shadan\\Desktop\\MazeMicromouse\\Maze_6.txt" //to the right Hcost
#define Maze_7 "C:\\Users\\Shadan\\Desktop\\MazeMicromouse\\Maze_7.txt" //to the right Hcost
#define Maze_8 "C:\\Users\\Shadan\\Desktop\\MazeMicromouse\\Maze_8.txt" //EXAMPLE

//File Pointers used for reading Data
FILE *ptr;

struct cells {

    int cost; //cost
    int x, y; //position
    int history; //how many times visited
    int N, W, E, S; //wall configuration 1 or 0
    int Sensor[3][48];
    int dead_end; //1- dead end, 0- not dead end or not visited


}; struct cells cell[8][6];



//function prototypes
int In_Range(int);
int Error();
int move_right();
int move_left();
int move_forward();
int ReadData(int, int);
int AtGoal();
int GoBack();
int PrintData();
int XY_values();
int Neighbours(int, int);
int FloodArray();
int InitialPath();
int PathGeneration();
int Move(int, int);
int CompareCost(int);
int BestPath();
int ReversePath();