## Modular decomposition
### Algorithms
[Factorizing Permutation](http://web.archive.org/web/20150619185404/http://www.liafa.jussieu.fr/~fm/publications/dmtcs.ps)

[Decomposition tree](http://web.archive.org/web/20150619185404/http://www.liafa.jussieu.fr/~fm/publications/swat04.pdf)

### Implementation by [Fabien de Montgolfier](https://www.irif.fr/users/fm/index)
It was publicly avaiable on his homepage, but now it can be found only on [web archive](http://web.archive.org/web/20150619185404/http://www.liafa.jussieu.fr/~fm/algos/index.html).
Here's the description (in French):

Décomposition modulaire des graphes non-orientés

Vous trouverez ici une implémentation, en langage C, de l'algorithme de décomposition modulaire de Capelle - Habib - Montgolfier - Paul par permutation factorisante. Il est très rapide  ; vous verrez que les graphes de plusieurs millions d'arêtes ne lui font pas peur... pourvu qu'ils tiennent en mémoire vive ! L'algorithme est construit autour d'une unique fonction, decomposition_modulaire. Elle prend en entrée un graphe, codé sous forme de liste d'adjacence, et retourne un pointeur sur la racine de l'arbre de décomposition modulaire du graphe. On peut donc très facilement l'interfacer dans un programme. Un main() d'exemple, décomposition d'un graphe aléatoire G(n,p), est fourni.

Le programme est propre : il n'utilise que malloc comme appel systeme, et libere toutes ses mémoires de travail.
Le mode d'utilisation exact est décrit dans dm.h

L'algorithme est en deux temps : calcul d'une permutation factorisante, puis de l'arbre de décomposition.
