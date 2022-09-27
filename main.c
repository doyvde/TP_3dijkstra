#include <stdio.h>
#include <stdlib.h>

#define NB_SOM_MAX 10 //nombre de sommets maximum
#define INFINITY 9999
#define MAX 10

///source : https://openclassrooms.com/forum/sujet/implementation-algorithme-de-dijkstra
///source : https://www.programiz.com/dsa/dijkstra-algorithm

//liste chainée de couples (sommet, poids)
typedef struct maillon{
    struct maillon *suiv;
    int nom;
    int poids;
} MAILLON, *LISTE;

//graph structure
typedef struct graphe{
    int nbSommets;
    LISTE Adj[NB_SOM_MAX]; //liste d'adjacence
} GRAPHE;

//insere (som_b,poids) en tete dans la liste d’adjacence Adj[som_a]
void insere(int som_a, int som_b, int poids, LISTE Adj[]){
    LISTE prem= malloc(sizeof(LISTE));
    prem->nom = som_b;
    prem->poids = poids;
    prem->suiv = Adj[som_a];
    Adj[som_a] = prem;
}

//initialisation de la table d’adjacence : toutes les listes chainées sont vides
void initAdjGraphe(GRAPHE *G){
    int i;
    for(i = 0; i< G->nbSommets; i++){
        G->Adj[i] = NULL;
    }
}

//pour charger un graphe a partir d’un fichier
void litGraphe(const char *adr, GRAPHE *G ,int matrice[MAX][MAX]){
    FILE *f;
    int s,sa,sb,pds,nbArcs,i,j,temp;
     for(i=0;i<MAX;i++)
     {
         for(j=0;j<MAX;j++)
         {
            matrice[i][j]=0;
         }
     }

    f=fopen(adr,"r");

    if (f == NULL){
        printf("File is missing!");
        exit(1);
    }

    fscanf(f,"%d",&(G->nbSommets));
    temp=G->nbSommets;
    initAdjGraphe(G);
    while(G->nbSommets){
        fscanf(f,"%d",&s);
        G->nbSommets--;
    }
    G->nbSommets=temp;
    fscanf(f,"%d",&nbArcs);
    while(nbArcs){
        fscanf(f,"%d %d %d",&sa,&sb,&pds);
        matrice[sa][sb]=pds;
        matrice[sb][sa]=pds;
        insere(sa,sb,pds, G->Adj);
        nbArcs--;
    }
    fclose(f);
}

// affichage d’un graphe : le nombre de sommets, puischaque arc pondéré : (sommet_1, sommet_2, poids)
void afficheGraphe(GRAPHE G){
    int j;
    printf("Nb sommets: %d\n", G.nbSommets);

    for(j = 0; j < G.nbSommets; j++){
        MAILLON* tmp = G.Adj[j];
        while(tmp != NULL){
            printf(" (%d, %d, %d)\n",j, tmp->nom, tmp->poids);
            tmp = tmp->suiv;
        }
    }
}

// Dijkstra's Algorithm in C
void Dijkstra(int Graph[MAX][MAX], int n, int start,int fin) {
  int cost[MAX][MAX], distance[MAX], pred[MAX];
  int visited[MAX], count, mindistance, nextnode, i, j;

  // Creating cost matrix
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (Graph[i][j] == 0)
        cost[i][j] = INFINITY;
      else
        cost[i][j] = Graph[i][j];

  for (i = 0; i < n; i++) {
    distance[i] = cost[start][i];
    pred[i] = start;
    visited[i] = 0;
  }

  distance[start] = 0;
  visited[start] = 1;
  count = 1;

  while (count < n - 1) {
    mindistance = INFINITY;

    for (i = 0; i < n; i++)
      if (distance[i] < mindistance && !visited[i]) {
        mindistance = distance[i];
        nextnode = i;

      }

    visited[nextnode] = 1;

    for (i = 0; i < n; i++)
      if (!visited[i])
        {

        if (mindistance + cost[nextnode][i] < distance[i]) {
          distance[i] = mindistance + cost[nextnode][i];

          pred[i] = nextnode;



        }
        }
    count++;

  }

  // Printing the distance
  /*for (i = 0; i < n; i++)
    if (i != start) {*/
            printf("\nEntre les sommets %d et %d, le plus court chemin est ",fin, start);
            j=fin;
            printf("%d",fin);
            while (pred[j]!= start )
            {
               printf("->%d",pred[j]);
               j=pred[j];
            }
            printf("->%d",start);
            printf(" de longeur %d. \n",distance[fin]);

      //printf("\n entre %d et %d la longeur est de %d",start, fin, distance[fin]);
    //}
}

//main
int main(){
    GRAPHE G;// declaration du graphe
    int matrice[MAX][MAX];//declaratio de la matrice

    litGraphe("graphe.txt", &G,matrice);// lecture du fichier et creation du graphe sous morme matricielle et de liste
    afficheGraphe(G);//affichage des donnes du graphe

    int n=G.nbSommets;//initialisation du monbre de sommet car necessaire dans le Dijkstra
    int start,fin;//initialisation des variable pour le somment de depart et d'arriver

    printf("Entrez le numero du sommet de depart : \n");//info user
    scanf("%d",&start);//recuperation de la donnée
    fflush(stdin);//clean buffer
    while ((start < 0) || (start > 8))// blindage
    {
        printf("ERREUR! %d Ce n'est pas un nombre valide.\n",start );//info user
        printf("Entrez le numero du sommet depart :  \n");//info user
        scanf("%d", &start);////recuperation de la donnée
        fflush(stdin);//clean buffer
    }
    fflush(stdin);//clean buffer
    printf("Entrez le numero du sommet d'arrive : \n");//info user
    scanf("%d",&fin);//recuperation de la donnée
    while ((fin < 0) || (fin > 8) || (fin==start))//blindage
    {
        printf("ERREUR! %d Ce n'est pas un nombre valide.\n",fin );//info user
        printf("Entrez le numero du sommet d'arrive :  \n");//info user
        scanf("%d", &fin);//recuperation de la donnée
        fflush(stdin);// clean buffer
    }

    Dijkstra(matrice, n, fin,start);// apelle de la fonction de Dijkstra

    return 0;
}
