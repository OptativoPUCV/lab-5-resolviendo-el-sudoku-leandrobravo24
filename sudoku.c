#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){

       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int row[9][10]={0};
  int col[9][10]={0};
  int box[9][10]={0};
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      if(n->sudo[i][j]!=0){
        int k=n->sudo[i][j];
        if(row[i][k] || col[j][k] || box[(i/3)*3+j/3][k])
          return 0;
        row[i][k]=1;
        col[j][k]=1;
        box[(i/3)*3+j/3][k]=1;
      }
    }
  }
  return 1;
}

List* get_adj_nodes(Node* n){
  List* list = createList();
  for(size_t i=0;i<9;i++){
    for(size_t j=0;j<9;j++){
      if(n->sudo[i][j]==0){
        for(size_t k=1;k<=9;k++){
          Node* new = copy(n);
          new->sudo[i][j]=k;
          if(is_valid(new)){
            pushBack(list, new);
          }else{
            free(new);
          }
        }
        return list;
      }
    }
  }
  return list;
}

int is_final(Node* n){
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      if(n->sudo[i][j]==0)
        return 0;
    }
  }
  return 1;
} 

/*5.Implemente la función Node* DFS(Node* n, int* cont). Esta función realiza una búsqueda en profundidad a partir del nodo n. El algoritmo es el siguiente:

1. Cree un stack S (pila) e inserte el nodo.
2. Mientras el stack S no se encuentre vacío:

   a) Saque y elimine el primer nodo de S.
   
   b) Verifique si corresponde a un estado final, si es así retorne el nodo.
   
   c) Obtenga la lista de nodos adyacentes al nodo.
   
   d) Agregue los nodos de la lista (uno por uno) al stack S.
   
   e) Libere la memoria usada por el nodo.
   
3. Si terminó de recorre el grafo sin encontrar una solución, retorne NULL.

Almacene en la variable cont, la cantidad de iteraciones que realiza el algoritmo.*/

Node* DFS(Node* initial, int* cont){
  Stack* stack = createStack();
  push(stack, initial);
  while(!is_empty(stack)){
    Node* current = top(stack);
    pop(stack);
    (*cont)++;
    
    if(is_final(current)){
      return current;
    }
    
    List* adj_nodes = get_adj_nodes(current);
    for(Node* node = first(adj_nodes); node != NULL; node = next(adj_nodes)){
      push(stack, node);
    }
    
    clean(adj_nodes);
    free(current);
  }
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}
*/