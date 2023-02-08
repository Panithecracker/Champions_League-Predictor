# Monte-Carlo-and-Soccer-
Setting up a Monte Carlo simulation in order to return insight about the most probable matches that will be drawn from the Champions League drawing method, under its facing rules regrading nationalities,previous encounters and groups position for each team.

# How is the Champions League set up?
# Group Stage (prior to the Knockout Stage, which is the one of interest)
The group stage involves eight groups of four teams, with each club playing everyone else in that group home and away. The top two sides in each group move on to the round of 16 and the start of the knockout phase, while the third-placed team drops into the UEFA Europa League.
Below, the picture shows the results of the Group Stage for this last year:

![GROUPSTAGE_50](https://user-images.githubusercontent.com/97905110/217606580-79847af6-e18d-4149-8134-5fcfc7afc5d7.jpg)

# Knockout Stage: 16 teams and one *draw*
After the Group Stage mentioned above, the 16 teams that are left enter the Knockout stage and a special draw takes place, that will annunce the following 8 matches from these teams, reducing the size of teams to 8, which are the winners of the drawn macthes. To study the probabilities of each match to be drawn in this draw, it is essential to understand the three rules that govern this draw:
## Rule 1: Bowl splitting
* Teams are initially separated into two bowls: Group 1 bowl and Group 2 bowl
The match ups are made always so that a group 1 team ends up facing another one (if further rules mentioned are also satisfied) from group 2. Teams from the same group or bowl are never matched together! 
Note: Keep in mind from picture below, that there are in total 16 teams in the beginning of the tournament. 8 for each bowl. Look at the picture below to see this specifically for this year games.

## Rule 2: Country distinction
* Teams from the same country (or league, which is the same) are not eligible to play against each other
* When picking up a team from bowl number 1, an empty bowl is filled with teams from the second bowl (since these are only possible candidates for bowl 1 teams, as stated on Rule 1) which by Rule 2, they will be only those bowl 2 teams that do not play in the same nation where the picked team from bowl 1 plays. This rule application can be seen in the right side of the picture below, inside that "Sudoku" looking table. We actually made this table as a way of naming and illustrating all possible matches for the 16 soccer teams. To understand this second rule, use the table to see that Chelsea (english team), represented on the table with the name A4, has 0 probability of being matched with Liverpool(also plays in England), denoted by the name B0 on the table. See that the entry (A4,B0) has a 0 as its content.

## Rule 3: Group stage winners distinction
* This last rule its easy: A team from bowl 1 is there because it has been a first position winner from some of the 8 groups during the Group Stage . Similarly, a team in bowl 2 by definition of this bowl, has been a second position winner from some of the 8 groups during the Group Stage- Now, what rule 3 states is that no pair of winners (first and second positions ) can ever face each other. This pairs of Group Stage winners are colored equally in the picture below
See Rule 3 in action with the following example, based on the data from this last year:
After this yea´s Group Stage,m the pair (Real Madrid, Leipzing) was presented. Then, as Real Madrid is denoted by the name A5 and Leipzig by B4, check that the entry on the "Sudoku" table is 0, because as stated, the pair of teams that got classified on the same group during the Group Stage, have 0 probability of being matched up.

![Applied Math 🔗🔗-43](https://user-images.githubusercontent.com/97905110/217595741-010f23b6-3763-4f64-b885-e5fb9de40399.jpg)

# Deriving a system of linear equations to find the probabilities:
Similar to a Sudoku, the table we drew is useful to see that for each entry, the sum of the entries in its row must be exactly 1. The same holds true for the sum of the column entries. Therefore, since we have 64 entries (unkowns), the number of equations is 128. This is called an "overdetermined system" and it may have infinite solutions (still had some hope this was possible, since we were ignoring the conditions that the unknowns must be nonnegative raeal values from 0 to 1 as they represent probabilities) or no solution at all (this would mean that an exact solution doesnt exist so we would have to take a numerical approach)
Sadly, the system turned up to have no solution , as I showed it by coding a Matlab script that performed Gaussian Elimination on the augmented matrix (coded the algorithm with maximal pivoting to avoid roundoff errors), had rows of with all zeros in the coefficient parat and a nonzero in the independent one.
After this, it was clear to us that the system had no solution and we had to take another appraoch to estimate it -> Monte Carlo Simulation of hundreds of thousands of draws.

# Numerical Conclusions from simulation of 100000 draws:
By keeping track of the results in each of the draws (incrementing by a 1 the appropiate entry in the matrix of all possible team combinations) and in the end dividing by 100000, the  probabilities of each match were estimated to be:

