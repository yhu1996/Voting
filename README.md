# Voting System of Two Candidates

## Setup the problem

Consider a scenario where there are 100 individuals going to vote. Each person can support one party. 
Initially, 50 individuals endorse Party R, while the remaining 50 support Party B, with a fixed voting deadline. 
However, individuals retain the freedom to engage in discussions with friends and amend their votes before the deadline. 
Now, the question arises: In order for Party R to secure victory, what strategic allocation of initial supporters should it pursue?


## Modeling

### Ising Model
This problem can be framed as an Ising model. Visualizing individuals as points and the two parties as red and blue, we create a network where friendships between people are represented by links. 
So a social network can be represented by an abstract network. In this scenario, the temperature of the system (one key parameter in the Ising model) can be interpreted as external influences like the effects of social media or other societal factors. 


### Erdos-Renyi Model
In this project, we apply the Erdos-Renyi model to construct the random network:
We define N nodes, with each pair of nodes being connected with a probability p. Notably, the value of p aligns with the clustering coefficient. 

### Discussion
For simplicity, we can assume that if a majority of an individual's friends endorse the opposing party, that individual may reconsider their stance.
This resembles the Ising Model and with a deadline in place, we can limit the total time available for discussions.



### Initial Distribution
The last ingredient to define the problem lies in determining the initial distribution. Describing the initial distribution isn't always straightforward. In this project, we utilize two parameters to characterize it:
- Triangles in the initial network: 
  - There are four types of triangles in this model based on the number of nodes supporting Party R (or Party B) within the triangle (namely, 0, 1, 2, and 3 nodes). 
- Quadrilaterals in the initial network: 
  - There are six types of quadrilaterals in this model: 0, 1, 3, and 4 nodes supporting Party R plus 2 when 2 nodes supporting the same party
  - When two nodes support the same party in one quadrilateral, there are two variations:
    - The two nodes are connected.
    - The two nodes are not connected.

### Dynamics
The voting dynamics can be summarized as follows:
- $\sigma_i$ represents the color of $i$-th node: $\sigma_i=1$ (red), $\sigma_i=-1$ (blue)
- The Hamiltonian of the voting system is $H=\sum_{<i,j>}-J\sigma_i\sigma_j$
- The discussion process can be realized as the following: consider the $i$-th node and all its links at each step (time). The $i$-th node converts its $\sigma_i$ with probability $P(i)_{convert}$ based on their $\sigma$'s.
- After a certain number of steps (e.g. 10,000), compare the number of nodes with $\sigma=1$ and $\sigma=-1$.



## Method 
The simulation can be divided into the following three steps
- study the effects of probability $p$ and the system temperature $T$ in this voting system and find the optimum values of $p$ and $T$
- use the Metropolis Algorithm to simulate the voting dynamics and probe the relationships between different types of triangles (and quadrangles) in the network and the final number of Party R supporters.
- use the genetic algorithm to optimize the random network to make Party R always win


