Inspired by Melanie Mitchell's book "Complexity: A Guided Tour". I've decided to try and replicate her Genetic Algorithm. Essentially a robot is created which lives in a matrix that either has empty cells or cans. The robot is created from 243 genes which will tell the robot which way to move or whether it should pick up a can or remain still. Over a series of generations, the robots which perform the best will be able to reproduce and pass on their "good" genes. At the end of the experiment the latest generation will be output along with each participants score.

Each of the 243 genes will either be one of seven commands to the robot (AKA "Robby").
0=MoveNorth;
1=MoveSouth;
2=MoveEast;
3=MoveWest;
4=StayPut;
5=PickUp;
6=RandomMove;

In all of the simulated Robbies, the genes are selected at random. Also, the position of the cans on the map are also set as random, although each map is guaranteed to have 50% of the cells set to cans. Each Robby will be allowed to have 200 actions per generation before a fitness level is output. At the end of each generation the top 20 of 100 Robbies is selected to pass on its genes to the next generation. This is repeated for 1,000 generations to find optimal Robby genetics.

The genes from one generation to the next are all generated from the genes of the top 20 Robbies. The remaining 80 lower positions of each generation are a mixture of healthy ancestor genes and random new genes (a one in 10 chance of new genes). Also, during the gene mixture process there is a small (a one in 100 chance) of a gene mutation. This would replace either an already random gene or a previous generation's gene.

Points are scored as follows:
CanFound += 10;
PickUpNonExistentCan -= 1;
HitWall -= 5;