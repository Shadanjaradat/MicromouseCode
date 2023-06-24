/* ****************************************************************************** */
// Programme Banner: File.c
// Created by Shadan Ibrahim
// Start Date: 11/03/2021
// End Date: 19/04/2021
// Description: This file includes all the functions created and called in the main.c
/* ****************************************************************************** */

//LIMITATION OF CODE: initial cell and orientation are specified before
#include "File.h"

//starting point
int current_cell[2] = {0,0}; //Maze_1
//int current_cell[2] = {0,0};

//Initial Orientation
//1-N 2-E 3-S 4-W
//int orientation = 2;  //Maze_1
int orientation = 1;

//goal cells
int GoalCells[4][2] = {{4, 3}, {4, 2}, {3, 3}, {3, 2}};
int neighbouring[4][2];

//cost
int FloodFill_1[8][6] = {{5, 4, 3, 3, 4, 5}, {4, 3, 2, 2, 3, 4}, {3, 2, 1, 1, 2, 3}, {2, 1, 0, 0, 1, 2}, {2, 1, 0, 0, 1, 2}, {3, 2, 1, 1, 2, 3}, {4, 3, 2, 2, 3, 4}, {5, 4, 3, 3, 4, 5}};

int path[50][2];
int reverse_path[50][2];
int p=0;







// function to check if position in range from 4 different sides
In_Range(int n) { //n as argument to specify which side is being checked

//In_Range = 1 --> inside of maze
//In_Range = 0 --> outside borders of maze

    switch (n) { //switch for diff sides of maze
        case 0:
            if (current_cell[0] > 0) { //lower row of the maze
                return (1);
            } else {
                return (0);
            }

        case 1:
            if (current_cell[1] > 0) { //left side of the maze
                return (1);
            } else {
                return (0);
            }

        case 10: //upper row of the maze
            if (current_cell[0] < (row - 1)) {
                return (1);
            } else {
                return (0);
            }

        case 11: //right side of the maze
            if (current_cell[1] < (col - 1)) {
                return (1);
            } else {
                return (0);
            }

    } //end switch
} //end function


//Function to be called whenever an error occurs
Error () {
    printf("\n***Error: Cannot Move This Direction -- Out of Margin***\n\n");
    return (1); //Error = 1 if there is something wrong
} //end of function

//Function called whenever user wants to print Data on the current cell
PrintData() {
    printf("\n\nNew Position: (%d, %d)\t", current_cell[0], current_cell[1]); //prints the position
    printf("Orientation: %d\n", orientation); //prints orientation 1-N, 2-E, 3-S, 4-W
    printf("History Visits: %d time(s)\n", cell[current_cell[0]][current_cell[1]].history); //print out history of cell
} //end function


// // // * * * * * * * // // //
//      Moving Functions  //

// --> turn right
move_right() {

    switch (orientation) { //depending on orientation, cell changes

        case 1: //North
            if (In_Range(11)) { //check if in range
                current_cell[1] = current_cell[1] + 1; //change position
                orientation++; //update orientation
            } else {
                Error(); //if not in range, error
            }
            break;

        case 2: //East
            if (In_Range(0)) { //check if in range
                current_cell[0] = current_cell[0] - 1; //change position
                orientation++; //update orientation
            } else {
                Error(); //not in range, Error
            }
            break;

        case 3: //South
            if (In_Range(1)) { //check if in range
                current_cell[1] = current_cell[1] - 1; //change position
                orientation++;  //update orientation
            } else {
                Error(); //not in range, Error
            }
            break;

        case 4: //West
            if (In_Range(10)) { //check if in range
                current_cell[0] = current_cell[0] + 1; //change position
                orientation = 1; //goes back to North
            } else {
                Error(); //not in range, Error
            }
            break;

    } //end of switch
} //end of function

//--> turn left
move_left() {

    switch (orientation) { //depends on orientation

        case 1: //North
            if (In_Range(1)) { //check if in range
                current_cell[1] = current_cell[1] - 1;
                orientation = 4; //orientation updates
            } else {
                Error(); //if not in range, Error
            }
            break;

        case 2:
            if (In_Range(10)) {
                current_cell[0] = current_cell[0] + 1;
                orientation--;
            } else {
                Error();
            }
            break;

        case 3 :

            if (In_Range(11)) {
                current_cell[1] = current_cell[1] + 1;
                orientation--;
            } else {
                Error();
            }
            break;

        case 4:

            if (In_Range(0)) {
                current_cell[0] = current_cell[0] - 1;
                orientation--;
            } else {
                Error();
            }
            break;
    } //end of switch

} //end of function

// go forward
move_forward() {

    switch (orientation) { //depends on orientation
        case 1: //NORTH
            if (In_Range(10)) { //check if in range
                current_cell[0] = current_cell[0] + 1;
                //orientation stays the same, no turning
            } else {
                Error(); //if not in range, Error
            }
            break;


        case 2: //EAST
            if (In_Range(11)) {
                current_cell[1] = current_cell[1] + 1;
            } else {
                Error();
            }
            break;

        case 3: //SOUTH
            if (In_Range(0)) {
                current_cell[0] = current_cell[0] - 1;
            } else {
                Error();
            }
            break;

        case 4: //WEST
            if (In_Range(1)) {
                current_cell[1] = current_cell[1] - 1;
            } else {
                Error();
            }
            break;
    } //end of switch
} //end of function

//uturn if surrounded dead end
GoBack() {

    cell[current_cell[0]][current_cell[1]].dead_end = 1; //this cell is a dead end

    //checking orientation to know how to uturn
    switch (orientation) {  //depends on orientation
        case 1: //NORTH
        current_cell[0] = current_cell[0] - 1;
        orientation = 3; //update orientation
        break;

        case 2: //EAST
        current_cell[1] = current_cell[1] - 1;
        orientation = 4;
        break;

        case 3: //SOUTH
        current_cell[0] = current_cell[0] + 1;
        orientation = 1;
        break;

        case 4: //WEST
        current_cell[1] = current_cell[1] + 1;
        orientation = 2;
    }

} //end of function


//This function reads sensor data from txt file
ReadData(int x, int y) {
    int i = 0, d, j; //local variables used

    if ((ptr = fopen(Maze_5, "r")) == NULL) { //open file
        printf("Error! opening file"); //if not able, print out error
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    for (d = 0; d < 50; d++) { //iteration to read multiple lines
        for (i = 0; i < 3; i++) { //three sensor values
            fscanf(ptr, "%d", &cell[x][y].Sensor[i][d]);
        }
    }
    fclose(ptr); //close file

    //Sensor[0] --> West sensor
    //Sensor[1] --> North sensor
    //Sensor[2] --> East sensor
    // each cell will have W N E as 1 or 0 indicating if there are walls

            //int j is used here to go to a new line of Data each time function is called
            if (cell[x][y].Sensor[0][j]  > threshold) { //determine if there are walls or not - based on threshold chosen
                cell[x][y].W = 1; // cell[x][y] has a wall on the left
            }

            else
                cell[x][y].W = 0; //no wall on the left

            if (cell[x][y].Sensor[1][j]  > threshold) {
                cell[x][y].N = 1; //wall on North
            }

            else
                cell[x][y].N = 0; //no wall North

            if (cell[x][y].Sensor[2][j]  > threshold) {
                cell[x][y].E = 1; //wall on east
            }

            else
                cell[x][y].E = 0; //no wall on east

            printf("W:%d N:%d E:%d\n", cell[x][y].W, cell[x][y].N, cell[x][y].E);

j++; //iterates to process new line of data whenever function is called
} //end of function

//This function assigns x and y (position) values for each cell
XY_values () {
    int i, j;
    for (i = 0; i < 8; i++) { //double loop to iterate through maze
        for (j = 0; j < 6; j++) {
            cell[i][j].x = i; //x represents row
            cell[i][j].y = j; //y represents column
        }
    }
} //end of function


//This function checks if current_cell = one of the goal cells
AtGoal () {
    int j=0, i=0; //local variables used

    for (i=0; i<4; i++) { //loop iterates through the 4 goal cells
        if (GoalCells[i][0] == current_cell[0] && GoalCells[i][1] == current_cell[1]) {
            j++; //indicates cell matches goal cell
        }
    }
    if (j>0) { //if goal reached
        printf("\n\nOne of the goal points is reached!\n");
        printf("Goal Cell is : (%d,%d)",current_cell[0], current_cell[1]);
        return (1); //AtGoal = 1
    }

    else //if not
        return(0); //AtGoal = 0

            }

//This Function finds the neighbours of current cell, N E S W if in range
Neighbours(int x, int y) {
//neighbouring[4][2] = {{x+1, y}, {x, y+1}, {x-1, y}, {x, y-1}}
//                       {North,    East,     South,    West}

    if (In_Range(10)) { //uses In_Range function to check upper row of maze

        //North Neighbour of current_cell
        neighbouring[0][0] = x+1; //row value changes
        neighbouring[0][1] = y; //column stays the same
        printf("(%d, %d)\t", neighbouring[0][0], neighbouring[0][1]); //print out neighbour position
        printf("cost:%d\t\t", cell[x+1][y].cost); //prints out the cost of neighbour
    }

    else { //if not in range, no North neighbour
        printf("--\t\t");  //print out -- to indicate no neighbour
    }

    if (In_Range(1)) { //uses In_Range function to check left column of maze

        //West Neighbour of current_cell
        neighbouring[1][0] = x;  //row stays the same
        neighbouring[1][1] = y - 1; //column shifts to the left
        printf("(%d, %d)\t", neighbouring[1][0], neighbouring[1][1]);
        printf("cost:%d\t\t", cell[x][y-1].cost);
    }
    else { //not in range, no west neighbour
        printf("--\t\t");
    }

    if (In_Range(11)) { //uses In_Range function to check right column of maze

        //East Neighbour of current_cell
        neighbouring[2][0] = x; //row stays the same
        neighbouring[2][1] = y + 1; //column shifts to the right
        printf("(%d, %d)\t", neighbouring[2][0], neighbouring[2][1]);
        printf("cost:%d\t\t", cell[x][y+1].cost);
    }

    else { //not in range, no east neighbour
        printf("--\t\t");
    }

    if (In_Range(0)) { //uses In_Range function to check lower row of maze

        //South Neighbour of current_cell
        neighbouring[3][0] = x - 1; //row shifts down
        neighbouring[3][1] = y; //column stays the same
        printf("(%d, %d)\t", neighbouring[3][0], neighbouring[3][1]);
        printf("cost:%d\n", cell[x-1][y].cost);
    }

    else { //not in range, no south neighbour
        printf("--\n");
    }

} //end of function

FloodArray() { //This function feeds in the cost of each cell
    int i=0, j=0;

    //assigning the cost to cells
    for (i=0; i < row ; i++) {
        for (j=0; j < col ; j++) {
            cell[i][j].cost = FloodFill_1[i][j];
            // printf("Cost of cell(%d, %d) is %d\n", x, y, cell[x][y].h);
        }
    }
} //end of function

InitialPath() { //This function prints out the path followed
    int j =0;
    printf("\n\nPath:\t\t\t");
    for (j=0; j<p; j++) {
        printf("(%d, %d)\t", path[j][0], path[j][1]);
    }
    printf("\nSetps walked: %d\n", p);

} //end of function

ReversePath() {
    int j =0;
    int x = p;
    p--;
    printf("\nReverse Path:\t");

    for (j=0; j<x; j++) {
        reverse_path[j][0] = path[p][0];
        reverse_path[j][1] = path[p][1];
        p--;
        printf("(%d, %d)\t", reverse_path[j][0], reverse_path[j][1]);
    }

    printf("\n\n");
}

PathGeneration() { //This function generates the path
    //path[0][0] = 7;
    //path[0][1] = 0;

    path[p][0] = current_cell[0]; //x
    path[p][1] = current_cell[1]; //y
    p++;

} //end of function


Move(int x, int y) {
    //if there are two walls, go to third
    //if there is one wall, compare 2 costs
    //if there are no walls, smallest neighbour

Neighbours(current_cell[0], current_cell[1]);

switch (orientation) {

    case 1: //NORTH ORIENTATION
    if (!cell[x][y].N) { //No North
        if (cell[x][y].E) { //east wall
            if (cell[x][y].W) { //west wall
                move_forward();
            } else { // no left
                CompareCost(3); //N W
            }
        } else { //no east
            if (!cell[x][y].W) {
                CompareCost(1); // N W E
            } else {
                CompareCost(2); // N E
            }

        }
    } else if (cell[x][y].N) { // if there is north wall
        if (cell[x][y].E) { //and east
            if (cell[x][y].W) { //and west
                GoBack();
            } else { //no west
                move_left();
            }
        } else if (!cell[x][y].E)  { //no east
            if (!cell[x][y].W) { //no west
                CompareCost(4); //E W
            } else if (cell[x][y].W) { //West wall
                move_right();
            }
        }
    }
    break;

    case 2: //EAST ORIENTATION
        if (!cell[x][y].N) { //No North
            if (cell[x][y].E) { //east wall
                if (cell[x][y].W) { //west wall
                    move_forward();
                } else { // no left
                    CompareCost(2); //N E
                }
            } else { //no east
                if (!cell[x][y].W) {
                    CompareCost(1); // N E S
                } else {
                    CompareCost(5); //E S
                }

            }
        } else { // if there is north wall
            if (cell[x][y].E) { //and east
                if (cell[x][y].W) { //and west
                    GoBack();
                } else { //no west
                    move_left();
                }
            } else { //no east
                if (!cell[x][y].W) { //no west
                    CompareCost(7); //N S
                } else { //West wall
                    move_right();
                }
            }

        }
        break;

    case 3: //SOUTH ORIENTATION
        if (!cell[x][y].N) { //No North
            if (cell[x][y].E) { //east wall
                if (cell[x][y].W) { //west wall
                    move_forward();
                } else { // no left
                    CompareCost(5); //S E
                }
            } else { //no east
                if (!cell[x][y].W) {
                    CompareCost(1); // N E S
                } else {
                    CompareCost(6); //W S
                }

            }
        } else { // if there is north wall
            if (cell[x][y].E) { //and east
                if (cell[x][y].W) { //and west
                    GoBack();
                } else { //no west
                    move_left();
                }
            } else { //no east
                if (!cell[x][y].W) { //no west
                    CompareCost(4); //W E
                } else { //West wall
                    move_right();
                }
            }
        }
    break;

    case 4: //WEST ORIENTATION
        if (!cell[x][y].N) { //No North
            if (cell[x][y].E) { //east wall
                if (cell[x][y].W) { //west wall
                    move_forward();
                } else { // no left
                    CompareCost(6); //S W
                }
            } else { //no east
                if (!cell[x][y].W) {
                    CompareCost(1); // N W S
                } else {
                    CompareCost(3); //N W
                }

            }
        } else { // if there is north wall
            if (cell[x][y].E) { //and east
                if (cell[x][y].W) { //and west
                    GoBack();
                } else { //no west
                    move_left();
                }
            } else { //no east
                if (!cell[x][y].W) { //no west
                    CompareCost(7); //N S
                } else { //West wall
                    move_right();
                }
            }
        }
        break;
}
    PrintData();
}

CompareCost(int n) {
    int min, i; //variable used to find least cost
    switch (n) {

        case 1: //compare 3 cells N W E
            min = cell[neighbouring[0][0]][neighbouring[0][1]].cost; //set the cost of first neighbour as min

            for (i = 0; i < 4; i++) { //loop to compare cost of 4 neighbouring cells
                if (cell[neighbouring[i][0]][neighbouring[i][1]].cost <= min &&
                    !cell[neighbouring[i][0]][neighbouring[i][1]].dead_end) {
                    min = cell[neighbouring[i][0]][neighbouring[i][1]].cost;
                }
            }

            if (cell[neighbouring[0][0]][neighbouring[0][1]].cost == min &&
                !cell[neighbouring[0][0]][neighbouring[0][1]].dead_end) { //NORTH CELL
                if (orientation == 1) {
                    move_forward();
                } else if (orientation == 2) {
                    move_left();
                } else if (orientation == 4) {
                    move_right();
                }
            }

            if (cell[neighbouring[1][0]][neighbouring[1][1]].cost == min &&
                !cell[neighbouring[1][0]][neighbouring[1][1]].dead_end) { //WEST CELL
                if (orientation == 1) {
                    move_left();
                } else if (orientation == 3) {
                    move_right();
                } else if (orientation == 4) {
                    move_forward();
                }
            }

            if (cell[neighbouring[2][0]][neighbouring[2][1]].cost == min &&
                !cell[neighbouring[2][0]][neighbouring[2][1]].dead_end) { //EAST CELL
                if (orientation == 1) {
                    move_right();
                } else if (orientation == 2) {
                    move_forward();
                } else if (orientation == 3) {
                    move_left();
                }
            }

            if (cell[neighbouring[3][0]][neighbouring[3][1]].cost == min &&
                !cell[neighbouring[3][0]][neighbouring[3][1]].dead_end) { //SOUTH CELL
                if (orientation == 2) {
                    move_right();
                } else if (orientation == 3) {
                    move_forward();
                } else if (orientation == 4) {
                    move_left();
                }
            }

            break;

        case 2: // compare N and E
            if (cell[neighbouring[0][0]][neighbouring[0][1]].cost <=
                cell[neighbouring[2][0]][neighbouring[2][1]].cost &&
                !cell[neighbouring[0][0]][neighbouring[0][1]].dead_end) { //NORTH
                if (orientation == 1) {
                    move_forward();
                } else if (orientation == 2) {
                    move_left();
                }
            } else { //EAST
                if (!cell[neighbouring[2][0]][neighbouring[2][1]].dead_end) {
                    if (orientation == 1) {
                        move_right();
                    } else if (orientation == 2) {
                        move_forward();
                    }
                }
            }
            break;

        case 3: //compare N and W
            if (cell[neighbouring[0][0]][neighbouring[0][1]].cost <=
                cell[neighbouring[1][0]][neighbouring[1][1]].cost &&
                !cell[neighbouring[0][0]][neighbouring[0][1]].dead_end) { //NORTH
                if (orientation == 1) {
                    move_forward();
                } else if (orientation == 4) {
                    move_right();
                }
            } else { //WEST
                if (cell[neighbouring[1][0]][neighbouring[1][1]].cost <
                    cell[neighbouring[0][0]][neighbouring[0][1]].cost) {
                    if (!cell[neighbouring[1][0]][neighbouring[1][1]].dead_end) {
                        if (orientation == 1) {
                            move_left();
                        } else if (orientation == 4) {
                            move_forward();
                        }
                    }
                }
                    /*if (cell[neighbouring[1][0]][neighbouring[1][1]].cost ==
                        cell[neighbouring[0][0]][neighbouring[0][1]].cost) {
                        //move to unvisited
                        if (cell[neighbouring[1][0]][neighbouring[1][1]].history <=
                            cell[neighbouring[0][0]][neighbouring[0][1]].history) {
                            if (orientation == 1) {
                                move_left();
                            }
                            else if (orientation == 4) {
                                move_forward();
                            }
                        }
                    }
                } */
            }
            break;

        case 4: //compare E and W
            if (cell[neighbouring[2][0]][neighbouring[2][1]].cost <=
                cell[neighbouring[1][0]][neighbouring[1][1]].cost &&
                !cell[neighbouring[2][0]][neighbouring[2][1]].dead_end) { //EAST
                if (orientation == 1) {
                    move_right();
                } else if (orientation == 3) {
                    move_left();
                }
            } else { //WEST
                if (!cell[neighbouring[1][0]][neighbouring[1][1]].dead_end) {
                    if (orientation == 1) {
                        move_left();
                    } else if (orientation == 3) {
                        move_right();
                    }
                }
            }
            break;
        case 5: //compare E and S
            if (cell[neighbouring[2][0]][neighbouring[2][1]].cost <=
                cell[neighbouring[3][0]][neighbouring[3][1]].cost &&
                !cell[neighbouring[2][0]][neighbouring[2][1]].dead_end) { //EAST
                if (orientation == 2) {
                    move_forward();
                } else if (orientation == 3) {
                    move_left();
                }
            } else { //SOUTH
                if (!cell[neighbouring[3][0]][neighbouring[3][1]].dead_end) {
                    if (orientation == 2) {
                        move_right();
                    } else if (orientation == 3) {
                        move_forward();
                    }
                }
            }
            break;


        case 6: //compare W and S
            if (cell[neighbouring[1][0]][neighbouring[1][1]].cost <= cell[neighbouring[3][0]][neighbouring[3][1]].cost && !cell[neighbouring[1][0]][neighbouring[1][1]].dead_end) { //WEST
                if (orientation == 3) {
                    move_right();
                }
                else if (orientation == 4) {
                    move_forward();
                }
            }
            else { //SOUTH
                if (!cell[neighbouring[3][0]][neighbouring[3][1]].dead_end) {
                    if (orientation == 3) {
                        move_forward();
                    } else if (orientation == 4) {
                        move_left();
                    }
                }
            }
            break;

        case 7: //compare N and S
            if (cell[neighbouring[0][0]][neighbouring[0][1]].cost <= cell[neighbouring[3][0]][neighbouring[3][1]].cost && !cell[neighbouring[0][0]][neighbouring[0][1]].dead_end) { //NORTH
                if (orientation == 2) {
                    move_left();
                }
                else if (orientation == 4) {
                    move_right();
                }
            }
            else { //SOUTH
                if (!cell[neighbouring[3][0]][neighbouring[3][1]].dead_end) {
                    if (orientation == 2) {
                        move_right();
                    } else if (orientation == 4) {
                        move_left();
                    }
                }
            }
        break;

    } //end of switch

} //end of function


int flag1, flag2;
int logCtr = 0;
int totalExtraction = 0;
int totalSize = 29;
int array[29][2] = {
        {7,0}, {7,1}, {6,1}, {5,1}, {6,1}, {6,0}, {5,0}, {4,0}, {4,1}, {3,1}, {2,1}, {2,2}, {1,2}, {1,3}, {2,3}, {2,4}, {2,5}, {3,5}, {4,5}, {5,5}, {5,4}, {4,4}, {3,4}, {4,4}, {5,4}, {6,4}, {6,3}, {5,3}, {4,3}
        //{7,0}, {6,0}, {5,0}, {4,0}, {4,1}, {3,1}, {2,1}, {2,2}, {1,2}, {1,3}, {2,3}, {2,4}, {2,5}, {3,5}, {4,5}, {5,5}, {5,4}, {6,4}, {6,3}, {5,3}, {4,3}
};

// Function to find the duplicate pairs
void findEqualAndMark(int *v){
    // Assuming the size of array is 12
    int i, j;
    for(i = 0; i < totalSize - 1; i++){
        // Flag 1 is for the location of first pair before match
        flag1 = i;
        // With the current index, we loop over the remaining
        // elements to see if there is a duplicate
        for(j = i + 1; j < totalSize; j++){
            // Condition to find duplicate
            printf("j is: %d\n", j);
            printf("(%d, %d)\t", path[i][0], path[i][1]);
            if((path[i][0] == path[j][0]) && (path[i][1] == path[j][1])){
                // If duplicate is found, set it's location as second flag
                flag2 = j;
                // Print the pair of flags to record the locations of duplicate pairs
                printf("Equal pair: %d, %d\n", i, j);
                // every even element in the allocated memory is the beginning location of the pair
                // and every odd element is the end location of the pair

                // Use a pointer to save the locations to malloc'd dynamic memory
                *(v + logCtr) = i;
                *(v + logCtr + 1) = j;
                // Assuming first match is the largest, first remove this element
                if(logCtr < 1){
                    // Get the number of elements to be extracted in order to be able
                    // to define a properly sized fresh memory block
                    // e.g. this can be used for a new malloc after calling this function
                    // or after recursion
                    totalExtraction = abs(*(v + logCtr) - *(v + logCtr + 1));
                    // Print for debugging purposes
                    printf("Total to be extracted: %d\n", totalExtraction);
                }
                // Increment by 2 since this is a double array, a better practice is to
                // increment by col (column size)
                logCtr += 2;

            }
        }
    }
}
// Using the pointer to freshly allocated memory, we extract the marked locations
// Size is passed to this function
void extractMarked(int *v, int size){
    int k, ctr = 0;
    // Set indexX and indexY (e.g. the pair) starting from the 0th element of pointer
    int indX = *v;
    int indY = *(v+1);
    // Print for debugging purposes
    printf("\nIndex x is: %d", indX);
    printf("\nIndex x is: %d\n", indY);
    //printf("We will extract)
    printf("### First extraction result ### \n");
    printf("\n");
    // H
    for(k = 0 ; k < p * 2 ; k++){
        // Increment pointer by 1 for pointer's first index
        // Because we only want to remove duplicates
        // Set the second index as the line to remove until, e.g. *(p+1)
        if (k < *v + 1 || *(v+1)){
            if (ctr < size){
                ctr++;
                printf("(%d, %d)\t", array[k][0], array[k][1]);
            }
            //printf("(%d, %d)\t", *(p+k), *(p+k+1));
            //printf("[%d]", *(p+k));
            //printf("[%d]\t", *(p+k+1));
        }
    }
    printf("\n");
}

// Fill the pointer passed here with whatever the array has
void populate(int *v){
    int m;
    for(m = 0 ; m < totalSize; m+=2){
        *(v + m) =array[m][0];
        *(v + m + 1) = array[m][1];
    }
}


int BestPath(){
    // Let us create dynamic memory for storing our potential pairs,
    // pLog is for logging the duplicate locations
    int *pLog;
    int i, k;
    // pArray is for putting in the new array, e.g. optimal one.
    int *pArray;
    pLog = (int *)malloc(p * 2 * sizeof(int));
    pArray = (int *)malloc(p * 2 * sizeof(int));
    //populate(pArray);
    // Check if we actually allocated the memory
    if(pLog == NULL){
        printf("Memory allocation failed");
        exit(1);
    }

    // Get the duplicate coordinates
    findEqualAndMark(pLog);
    // Get the size of the future optimal array
    int newSize = totalSize - totalExtraction;

    // Print pointer contents to see duplicate coordinates
    for(k = 0 ; k < p * 2 ; k+=2){
        printf("[%d]", *(pLog+k));
        printf("[%d]\t", *(pLog+k+1));
    }
    printf("\n");

    // Extract the duplicates and get the final array
    extractMarked(pLog, newSize);


    // Print the original array for visual comparison
    printf("Array is: \n");
    for (i = 0 ; i < totalSize; i++){
        printf("(%d, %d)\t", array[i][0], array[i][1]);
    }
    printf("\nDone!\n");


    return 0;
}