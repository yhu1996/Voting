# Voting System of Two Candidates

## Setup the problem

Suppose that there are 100 people and two parties. Each person can support one party. 
At first, there are 50 people supporting Party R and 50 people supporting Party B. The deadline for voting is fixed. 
People can discuss with friends and change their opinions before the deadline. 
Here is the question: if Party R wants to win, what is the best distribution of its initial supporters? 


## Modeling

### Ising Model
This problem actually can be interpreted as an Ising model problem. Use points to represent people, red and blue to represent two parties. 
If two people are friends, there will be a link between two corresponding nodes. So a social network can be represented by an abstract network. 
The temperature of the system can be interpreted as all other external influence, for example, the effect of social media. 

### Erdos-Renyi Model
In this project, we choose Erdos-Renyi model as the construction of the random network: 
  We have N nodes and every pair of nodes being connected with probability p.
  The value of p is equal to the clustering coefficient

### Discussion
For the discussions, we can assume that if most of one person's friends support the opposite party, this person may change the opinion. 
Therefore this process is similar to the Ising Model. Given that there is a deadline, we can fix the total discussion time. 

### Initial Distribution
The last part is the initial distribution. Generally it's not straightforward to describe the initial distribution. In this project, we consider two parameters to describe the initial distribution:
- The triangles in the initial network
  - there are four types of triangles in this model: zero node, one node, two nodes, and three nodes supporting Party R(or Party B) in the triangle.
- The quadrilaterals in the initial network
  - there are six types of quadrilaterals in this model: 0, 1, 3, and 4 nodes supporting Party R  + 2 when 2 nodes supporting the same party
  - when there are 2 nodes supporting the same party in one quadrilateral, there are two types of quadrilaterals: the one is these two nodes are connected; the other one is these two nodes are not connected


### Dynamics
The voting dynamics can be summarized as follow:
- $\sigma_i$ represents the color of i-th node,$\sigma_i=1$ (red), $\sigma_i=-1$ (blue)
- The Hamiltonian of the voting system is $H=\sum_{<i,j>}-J\sigma_i\sigma_j$
- Discussion process: consider i-th node and its friends each time. According to their $\sigma$'s, i-th node converts its $\sigma_i$ with probability $P(i)_{convert}$.
- After 10,000 times discussion, compare the number of nodes with $\sigma=1$ and $\sigma=-1$.



## Method 
Random network is usually used to simulate real network. In this project, I use random network model to simulate the voting dynamics and try to find the best initial condition.

The simulation can be divided into following three steps
- study the effects of probability p and the system temperature T in this voting system and find the optimum values of p and T
- use Metropolis Algorithm to simulate voting dynamics and probe the relationships between different kinds of triangles (and quadrangles) in the network and the final number of Party R supporters.
- use genetic algorithm to optimize random network and make Party R always win


