# Enigma
Simulation of Enigma (Academic Project)

# Input:
Defintions of parts of the machine:
n - number of letters (numbers) in the alphabet\n
m - number of rotors, followed by their definitions W0,...,Wm-1
  definition of rotor Wi - permutation of the alphabet
  number of letters which cause turnover, followed by these letters
l - number of reflectors
definitions of reflectors R0,...,Rl-1
  definition of reflector - permutation of the alfabet

A set of p tasks to perform:
each task consists of 2 parts: machine setup and a message to encrypt.
p - number of tasks
k - number of rotors in the machine
k pairs K0,...,Kk-1 - where Ki=(j, t), where j is an index of a copy of rotor Wj and t is its initial position
rotors are given in order from fastest to slowest
initial position of a rotor - it is set as if it was rotated (no actual rotations occur) prior to encoding
e.g. 1 - rotor is set as stated in permutation, 2 - it is shifted by one letter, etc.
r index of a reflector Rr
a sequence of numbers separated by whitespaces to encrypt, ending with the 0 character

Output:
encrypted sequences of numbers (without the 0 character)

# Example:
Input:
4
4
1 2 4 3
1 2  
3 2 1 4 
0
4 3 1 2
0
3 2 1 4
0
3
2 1 4 3
4 3 2 1
1 2 4 3

6
1 0 4 2
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0
1 0 4 0
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0
1 0 4 1
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0 
1 2 4 0
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0
1 3 4 0
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0
2 0 4 0 1 0
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0

Output:
1 1 1 3 2 4 2 2 4 3 4 1 3 2 3 4
2 3 2 3 1 4 1 4 4 1 4 1 3 2 3 2
3 4 3 4 4 3 4 3 1 2 1 2 2 1 2 1
2 3 2 3 1 4 1 4 4 1 4 1 3 2 3 2
4 4 4 4 3 3 3 3 2 2 2 2 1 1 1 1
2 2 4 2 3 4 1 4 4 4 2 4 1 2 3 2 2 2 4 2 3 4 1 4 4 4 2 4 1 2 3 2 
