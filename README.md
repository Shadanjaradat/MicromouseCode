# MicromouseCode

This project is completed in compliance with the Micromouse Competition, in which a robot is designed and developed to expolore and solve a 16x16 maze with unkown wall configuration using a certain mapping and solving algorithm.


The code in this project is designed in C in which it explores, maps, and solves an 8x6 maze with unknown wall configuration. This task is essential as it allows the Micromouse to make decisions and move on its own.


Cells within the maze are represented by classes, in which the position, history, and cost are represented.

The algorithm implemented in this project is the Flood fill algorithm which depends on the cost of the cell, or how far the cell is from the goal. By moving to the adjacent cell that holds the least cost, the goal can be reached. This algorithm was chosen after the completion of an extensive search and by comparing different algorithms including A*, wall follower, and Depth first. Floodfill was chosen as it acquires a good balance between complexity and efficiency.


Since no physical testing will take place, the code will be implemented and simulated in C-lion. If the competition were still taking place physically, the code would be written in MPLAB to allow the user to control motors and trigger sensors.


The algorithm was tested by reading data from txt files, in which this data symbolizes the sensor data from the three sensors on the robot. Different maze configurations are represented by the different txt files used in testing. 


Requirements of Code : 

-	Starting position and orientation is known 
-	Goal cells are known
-	Square enclosing the four goal cells is accessible from one cell only



