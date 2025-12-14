# Monte-Carlo-and-Soccer-
Setting up a Monte Carlo simulation in order to estimate the most probable matches that will be drawn from the Champions League draw, under its facing rules regarding nationalities,previous encounters and groups position for each team.

# How is the Champions League set up?
# Group Stage (prior to the Knockout Stage)
The group stage involves eight groups of four teams, with each club playing everyone else in that group home and away. The top two sides in each group move on to the round of 16 and the start of the knockout phase, while the third-placed team drops into the UEFA Europa League.
Below, the picture shows last year Group Stage results:

![GROUPSTAGE_50](https://user-images.githubusercontent.com/97905110/217606580-79847af6-e18d-4149-8134-5fcfc7afc5d7.jpg)

# Knockout Stage: 16 teams and one *draw*
After the Group Stage, the 16 teams that are left enter the Knockout stage and a special draw takes place, which will announce the following 8 matches from these teams, reducing the size of teams to 8, which are the winners of the drawn matches. To study the probabilities of each match to be drawn, it is essential to understand the three rules that govern this draw:
## Rule 1: Bowl splitting
* Teams are initially separated into two bowls: Group 1 bowl and Group 2 bowl
The match ups are made always so that a group 1 team ends up facing another one (if further rules mentioned later are also satisfied) from group 2. Teams from the same group never face each other! 
Note: Keep in mind from the picture below that there are 16 teams in the beginning of the tournament; 8 for each bowl. Look at the picture below to see the example for this year draw.

## Rule 2: Country distinction
* Teams from the same country (or league, equivalently) are not eligible to play against each other.
* When picking up a team from bowl 1, an empty bowl is filled with teams from bowl 2 (since these are only possible candidates for bowl 1 teams, as stated on Rule 1) which also,by Rule 2, they can only be those bowl 2 teams that do not play in the same nation in which the picked team from bowl 1 plays. This rule application can be seen in the right side of the picture below, inside that "Sudoku" looking table. I actually made this table as a way of naming and illustrating all possible matches for the 16 soccer teams. To understand this second rule, use the table to see that Chelsea (english team), represented on the table with the name A4, has 0 probability of being matched with Liverpool(also plays in England), denoted by the name B0 on the table. See that the entry (A4,B0) has a value of 0.

## Rule 3: Group stage winners distinction
* This last rule is pretty easy: A team from bowl 1 is there because it has been a first position winner from some of the 8 groups during the Group Stage . Similarly, a team in bowl 2 has been a second position winner from some of the 8 groups during the Group Stage- Now, what rule 3 states is that no pair of winners (first and second positions ) can ever face each other. This pairs of Group Stage winners are colored equally in the picture below
See Rule 3 in action with the following example, based on the data from this last year:
After this year´s Group Stage, the pair (Real Madrid, Leipzing) was presented. Then, as Real Madrid is denoted by the name A5 and Leipzig by B4, check that the entry on the "Sudoku" table is 0, because as stated, the pair of teams that got classified on the same group during the Group Stage, have 0 probability of being matched up.
By combining the last two rules, see that there are impossibles match ups already, that is, with 0 probability. There are exactly 16 of these (check with the table)
![Applied Math 🔗🔗-43](https://user-images.githubusercontent.com/97905110/217595741-010f23b6-3763-4f64-b885-e5fb9de40399.jpg)

# Deriving a system of linear equations to find the probabilities:
Similar to a Sudoku, the structure of the table made is convenient for a reason : for each entry, the sum of the entries in its row must be 1. The same holds for the sum of the column entries. Therefore, we have 64-16 = 48 nonzero entries (unkowns) constrained by 16 equations. This is an "underdetermined system" so it may have infinitely many solutions or no solution (in any case, we know that the problem has a unique solution so this fact already hinted that the conditions were only necessary but not sufficient). However, note that we should also enforce additional 48 nonnegativity constraints as the quantities are probabilites.
As expected, the above system admits infinitely many solutions, which I proved by coding a Matlab script that performed Gaussian Elimination on the augmented matrix ( with maximal pivoting to minimize roundoff errors), finding more than one solution. This just confirmed our intuition that we were lacking more equations, but these remaining ones do not seem to be tractable from the drawing conditions.
We had hit a dead end with our analytical approach so we pivoted into a nummerical one -> Monte Carlo Simulation of hundreds of thousands of draws.

# Numerical Conclusions after simulating 10E6 draws:
The sampling was done in C++ but we ended up discovering another inconvenience that popped up with this approach: if you just perform the simulation by following the outlined drawing conditions, there are instances where a team may be left unmatched unless a drawing rule is violated. Equivalently, throughout the draw process, picking a possible opponent for a runner up (according to the rules) can lead to a situation where another runner up is left without possible opponents and thus force a contradiction if paired with the remaining teams. Therefore, the simulation must detect this scenarios and not count them for the probability computation. This is precisely how we programmed our algorithm but we later discovered a more sophisticated method which in fact solves the problem exactly by essentially distinguising among possible and admissible opponents, using perfect-matching finding and maximum matching algoritms from Graph theory, which allows to determine the unconditional and conditional probabilities as the drawing takes place. We learned about the full details by reading Julien Guyon's and Frederic Meunier notes:  [UEFA Draw Probability Calculator (PDF)](docs/ExactProbabilities_ChampionsLeague_RoundOf16_text_website-1.pdf)

### Relative frequencies approach probabilities as the number of repetitions of the experiment approaches infinity.Then, the probabilities of particular matches taking place this year can be estimated with an error less than any E>0, as long as we look at the relative frequency of that match after simulating N=N(E) tournament draws (N is expected to grow as E shrinks).
By keeping track of the results in each of the draws (incrementing by a 1 the appropiate entry in the matrix of all possible team combinations) and in the end dividing by 100000, the  probabilities of each match were estimated to be:

![probsteams](https://user-images.githubusercontent.com/97905110/217650644-6b33bf8a-108d-45d4-976d-63db1c11c23e.png)

which is surprisingly similar to the one's published by the sport magazine that motivated us to start this project (this is in percentage, ie: multiplied by 100) :

![source_1_50](https://user-images.githubusercontent.com/97905110/217651668-124cbfbf-33f5-40c0-b9c4-1d13cfbebb8f.jpg)

