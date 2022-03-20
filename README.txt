

This is my implementation of the game "Hey, that's my fish!". 

1. The game runs within a "while" loop, which goes until both the player and the AI fails to make a move. 
A function is responsible for checking 8 directions around a point on the game board to see if there is any legal move. 
After that, the player is prompted to input their move in the form: "DIRECTION [Number of steps]. 
Then, a function will check to see if the input is a legal move. If it is, the game continues to the AI's turn. If not, the user will be asked to submit another input.

2. The board was constructed as a structure called "Grid", which consists of a character that represents the point's value and pointers to the 8 directions around it. My board was implemented using malloc() of 36 Grids. 
Then, I iterated through these points on the board and assign pointers to the 8 directions around them. After that I went over to the 4 edges of the board and assign the pointers poiting out of the board "NULL". Using loops, I was able to set all the points' values.

3. The AI uses a greedy algorithm to find the best move locally at every stage of the game.
I implemented the AI by firstly using a function that looks at all the 8 directions around its current standing point. Then the function simulate through all the paths to find highest point it can score in each.
The AI will pass on points that has been travelled to, or the point that the player is currently on. After that, the paths are compared to find the one with the most number of points to be gained and the AI will travel to that place. 
