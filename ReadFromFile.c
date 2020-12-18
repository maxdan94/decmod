/******************************************************

Copyright 2004, 2010 Fabien de Montgolfier
fm@liafa.jussieu.fr

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.


TO COMPILE:
gcc -c -o dm.o dm.c  
gcc -c -o main.o main.c
gcc -o dm main.o dm.o

TO EXECUTE:
./dm graph.txt > res.txt 


**********************************************************/



#include <time.h>
#include "dm_english.h"

#define NIV 20
#define NLINKS 10000000
 
//extern noeud *decomposition_modulaire(int *,int);
extern void printarbre(noeud *);
/* ppm est la part par million d'arretes voulues dans le graphe */

void compte(noeud *N, int level, int *C)
{
  fils *F;
  switch(N->type)
    {
    case SERIE: C[4*level]++; break;
    case PARALLELE: C[4*level+1]++; break;
    case PREMIER: C[4*level+2]++; break;
    case FEUILLE: C[4*level+3]++; break;
    }
  if(N->type!=FEUILLE)  
    for(F=N->fils;F!=NULL;F=F->suiv)
      compte(F->pointe, level+1, C);
}


//////////////////////

typedef struct {
	unsigned long s;
	unsigned long t;
} edge;

//edge list structure:
typedef struct {
	unsigned long n;//number of nodes
	unsigned long e;//number of edges
	edge *edges;//list of edges
	unsigned long *cd;//cumulative degree cd[0]=0 length=n+1
	unsigned long *adj;//concatenated lists of neighbors of all nodes
} adjlist;

//compute the maximum of three unsigned long
unsigned long max3(unsigned long a,unsigned long b,unsigned long c){
	a=(a>b) ? a : b;
	return (a>c) ? a : c;
}

//reading the edgelist from file
adjlist* readedgelist(char* input){
	unsigned long e1=NLINKS;
	FILE *file=fopen(input,"r");

	adjlist *g=malloc(sizeof(adjlist));
	g->n=0;
	g->e=0;
	g->edges=malloc(e1*sizeof(edge));//allocate some RAM to store edges

	while (fscanf(file,"%lu %lu", &(g->edges[g->e].s), &(g->edges[g->e].t))==2) {
		g->n=max3(g->n,g->edges[g->e].s,g->edges[g->e].t);
		if (++(g->e)==e1) {//increase allocated RAM if needed
			e1+=NLINKS;
			g->edges=realloc(g->edges,e1*sizeof(edge));
		}
	}
	fclose(file);

	g->n++;

	g->edges=realloc(g->edges,g->e*sizeof(edge));

	return g;
}

//building the adjacency matrix
void mkadjlist(adjlist* g){
	unsigned long i,u,v;
	unsigned long *d=calloc(g->n,sizeof(unsigned long));

	for (i=0;i<g->e;i++) {
		d[g->edges[i].s]++;
		d[g->edges[i].t]++;
	}

	g->cd=malloc((g->n+1)*sizeof(unsigned long));
	g->cd[0]=0;
	for (i=1;i<g->n+1;i++) {
		g->cd[i]=g->cd[i-1]+d[i-1];
		d[i-1]=0;
	}

	g->adj=malloc(2*g->e*sizeof(unsigned long));

	for (i=0;i<g->e;i++) {
		u=g->edges[i].s;
		v=g->edges[i].t;
		g->adj[ g->cd[u] + d[u]++ ]=v;
		g->adj[ g->cd[v] + d[v]++ ]=u;
	}

	free(d);
	//free(g->edges);
}


//freeing memory
void free_adjlist(adjlist *g){
	free(g->edges);
	free(g->cd);
	free(g->adj);
	free(g);
}
////////////////////////////////////////




void test(adjlist* g, int *C)
{
  /*genere un graphe aleatoire, l'affiche, le decompose*/
  graphe G;

  int i,j,u;
  adj *a;
  noeud *R;
  int n;

  srandom((unsigned)time(NULL));

  n=g->n;
  G.n=n;
  G.G=(adj **)malloc(n*sizeof(adj *));

  for(i=0;i<n;i++)
    G.G[i]=NULL;

  for(i=0; i<n; i++)
    {
      for(j=g->cd[i];j<g->cd[i+1];j++)
	{
            u=g->adj[j];
	    // ajoute j a l'adjacence de i
	    a=(adj *)malloc(sizeof(adj));
	    a->s=u;
	    a->suiv=G.G[i];
	    G.G[i]=a;
	    // et reciproquement
	    a=(adj *)malloc(sizeof(adj));
	    a->s=i;
	    a->suiv=G.G[u];
	    G.G[u]=a;
	  }
	}


  // appel de la fonction de decomposition
  R = decomposition_modulaire(G);

  compte(R,0,C);
  printf("Statistiques sur l'arbre de decomposition:\n");
  if(C[0])
    printf("La racine est Serie\n");
  else if(C[1])
    printf("La racine est Parrallele\n");
  else
    printf("La racine est Premier \n");
  for(i=1 ; i<NIV ; i++)
    {
      printf("Niveau %i: %i modules (S-P-Pr= %i - %i - %i) et %i feuilles\n",i,
       C[4*i]+C[4*i+1]+C[4*i+2], C[4*i], C[4*i+1], C[4*i+2],C[4*i+3]);  
      if(i<NIV-1 && C[4*i+4]+C[4*i+5]+C[4*i+6]+C[4*i+7]==0)
	break;
    }
  printf("\n");
}

int main(int narg, char **arg)
{
  int n;
  long ppm;
  int C[4*NIV];int i;


  printf("Reading edgelist from file %s\n",arg[1]);
  adjlist* g=readedgelist(arg[1]);

  printf("Number of nodes: %lu\n",g->n);
  printf("Number of edges: %lu\n",g->e);

  printf("Building the adjacency list\n");
  mkadjlist(g);

  for(i=0;i<4*NIV;i++) C[i]=0;

  test(g, C);

  free_adjlist(g);
  
  return 0;
}





