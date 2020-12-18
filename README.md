## Modular decomposition
Forked from https://github.com/antonovvk/decmod

I've added a dirty piece code to read a graph from a text file and a Makefile.

type "Make" to compile the C code.

"./dm edgelist.txt".

- "edgelist.txt" should contain the graph: one edge on each line separated by a space (i.e. 2 unsigned).
- Will print some infos about the modular decomposition


What does it give on some real world graphs?:

On Youtube: http://snap.stanford.edu/data/com-Youtube.html

```
time ./dm ../DATA/Youtube/net.txt
Reading edgelist from file ../DATA/Youtube/net.txt
Number of nodes: 1157828
Number of edges: 2987624
Building the adjacency list
Statistiques sur l'arbre de decomposition:
La racine est Parrallele
Niveau 1: 1 modules (S-P-Pr= 0 - 0 - 1) et 1 feuilles
Niveau 2: 68629 modules (S-P-Pr= 2522 - 65943 - 164) et 936490 feuilles
Niveau 3: 1348 modules (S-P-Pr= 1214 - 44 - 90) et 218438 feuilles
Niveau 4: 54 modules (S-P-Pr= 6 - 47 - 1) et 2782 feuilles
Niveau 5: 3 modules (S-P-Pr= 3 - 0 - 0) et 110 feuilles
Niveau 6: 0 modules (S-P-Pr= 0 - 0 - 0) et 7 feuilles

real	0m12,394s
user	0m11,686s
sys	0m0,647s
```



On LiveJournal: http://snap.stanford.edu/data/com-LiveJournal.html

```
time ./dm ../DATA/LiveJournal/net.txt 
Reading edgelist from file ../DATA/LiveJournal/net.txt
Number of nodes: 4036538
Number of edges: 34681189
Building the adjacency list
Statistiques sur l'arbre de decomposition:
La racine est Parrallele
Niveau 1: 1 modules (S-P-Pr= 0 - 0 - 1) et 2 feuilles
Niveau 2: 132514 modules (S-P-Pr= 20434 - 110993 - 1087) et 3704505 feuilles
Niveau 3: 5459 modules (S-P-Pr= 4513 - 242 - 704) et 318444 feuilles
Niveau 4: 439 modules (S-P-Pr= 227 - 166 - 46) et 12337 feuilles
Niveau 5: 38 modules (S-P-Pr= 23 - 4 - 11) et 1133 feuilles
Niveau 6: 7 modules (S-P-Pr= 4 - 3 - 0) et 95 feuilles
Niveau 7: 1 modules (S-P-Pr= 1 - 0 - 0) et 17 feuilles
Niveau 8: 0 modules (S-P-Pr= 0 - 0 - 0) et 5 feuilles


real	2m40,243s
user	2m34,102s
sys	0m6,031s

```



