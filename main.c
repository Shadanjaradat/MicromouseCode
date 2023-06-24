/* ****************************************************************************** */
// Programme Banner: Mapping Algorithm
// Created by Shadan Ibrahim
// Start Date: 10/03/2021
// End Date: 19/04/2020
// Description: This file includes the main function that calls the functions created in File.c using a menu based interface.
/* ****************************************************************************** */

#include "File.h"

int current_cell[2];
int orientation;


int main() {

    FloodArray(); //set cost for cells
    XY_values(); //set x and y values for cells

    printf("Initial: (%d, %d)  Orientation: %d\n", current_cell[0], current_cell[1], orientation);

    while (!AtGoal()) { //while the robot didnt reach the goal

        PathGeneration(current_cell); //add current cell to path
        ReadData(current_cell[0], current_cell[1]); //read data from sensors
        Move(current_cell[0], current_cell[1]); //move according to floodfill theorem

    }

    PathGeneration(current_cell); //add last cell to path
    InitialPath(); //generates first run path
    ReversePath(); //generates path for way back
    //BestPath(); //generates optimal path

    return(0);
}














