//-----------------------------------------------------------------------------
//
// GraphTest.c
// 
// This is a fancy test Test that calculates the Radius and Diameter of 
// the graph defined on lines 41-49, along with its Central and Peripheral 
// vertices.  The definitions of these terms at:
// 
//    http://en.wikipedia.org/wiki/Distance_(graph_theory)
// 
// Place this file in a directory with copies of your List.c, List.h, Graph.c, 
// Graph.h and an appropriate Makefile, then compile and run. The output 
// is contained in the file GraphTestOut.
// 
// This program does not exercise all functions in your Graph ADT, but it 
// does a pretty good job of testing BFS().  If your output differs from 
// the above, you have a logical problem in either your Graph or List ADT.
// 
// Remember you are required to submit a file named GraphTest.c with pa4 that
// exercises your Graph functions.  Do not submit this file.
//
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"


int main(int argc, char* argv[]){
   int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      //printf("edge %d -> %d added\n", i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
      //printf("edge %d -> %d added\n", i, i+7);
   }
   //printf("all loop edges added\n");
   addEdge(G, 9, 31);
   //printf("edge 9-31 added\n");
   addEdge(G, 17, 13);
   //printf("edge 17-13 added\n");
   addEdge(G, 14, 33);
   //printf("edge 13-33 added\n");

   // Print adjacency list representation of G
   printGraph(stdout, G);
   //printf("Done with print graph\n");
   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      //printf("Finihsed BFS with root of %d\n", s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);
   printf("Freed G\n");
   Graph new = newGraph(3);
   addEdge(new, 1, 2);
   addArc(new, 1, 3);
   BFS(new, 1);
   getParent(new, 1);
   getSize(new);
   addArc(new, 3, 1);
   BFS(new, 1);
   getParent(new, 1);
   getOrder(new);
   getSource(new);
   List L = newList();
   getPath(L, new, 2);
   freeGraph(&new);
   freeList(&L);
   printf("Freed new\n");

   return 0;
}