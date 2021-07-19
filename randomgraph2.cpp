#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

 
using namespace std;
 
//PROGRAMMA SIMULA RANDOM GRAPH DI ERDOS G(n,p)

// A function to generate random graph.
void GenerateRandGraphs( int n_vertex, float prob)
{
	
        double theta;
        double adj[n_vertex][n_vertex];
        double grado[n_vertex]={0};
        double L[n_vertex][n_vertex];
        double T[n_vertex][n_vertex];
        double controllaT,controllaL;

        for(int i=0;i<n_vertex;i++) 
        { 
         for(int j=0;j<n_vertex;j++) 
         { 
           theta=(double)rand()/(RAND_MAX);
           if(theta<prob || theta==prob) {adj[i][j]=adj[j][i]=1;}
           else {adj[i][j]=adj[j][i]=0;}
           adj[j][j]=0;
         }
       }
       //Define the degree
       for(int i=0; i<n_vertex; i++)
       for(int j=0; j<n_vertex; j++)
       grado[i]+=adj[i][j];
       


       //Print the adjacency matrix.	
       cout<<"\nThe adicency matrix of the graph is: ";
       for(int i=0; i<n_vertex; i++)
       { 
               cout<<endl;
               for(int j=0; j<n_vertex; j++)
               cout<<adj[i][j]<<",";
       }
       cout<<endl<<endl<<endl;
       //Print the diagonal degree matrix.	
       cout<<"\nThe diagonal degrees matrix of the graph is: ";
       for(int i=0; i<n_vertex; i++)
       { 
               cout<<endl;
               for(int j=0; j<n_vertex; j++)
               {if(i==j) cout<<grado[j]<<","; else cout<<0<<",";}
       }

       //Define the stochastic matrix
       cout<<"\nPrint the stochastic matrix:"<<endl;
       for(int i=0;i<n_vertex;i++) 
       {
                cout<<endl;
       		for(int j=0;j<n_vertex;j++)
                {
                //T[i][j]=0;
                //for(int k=0;k<n_vertex;k++)
       		//T[i][j]+=(adj[i][k]*D[k][j]);
                T[i][j]=adj[i][j]/grado[j];
                cout<<T[i][j]<<",";
                }
                
       }

       //Define the laplacian matrix
       cout<<"\nPrint the laplacian matrix: "<<endl;
       for(int i=0;i<n_vertex;i++) 
       {
                cout<<endl;
       		for(int j=0;j<n_vertex;j++)
       		{ 
        		if(i==j) L[i][j]=1-T[i][j];
        		else L[i][j]=-T[i][j];
                        cout<<L[i][j]<<",";
       		}
       }
  
       //Check for the Stochastic and Laplacian Matrix Property
       for(int i=0;i<n_vertex;i++)
       {
       		controllaT=0, controllaL=0;
                for(int j=0;j<n_vertex;j++) controllaT+=T[j][i],controllaL+=L[j][i];
                if(controllaT!=1) cout<<"\nwarning! for T: "<<fixed<<controllaT<<endl;
                if(controllaL!=0) cout<<"\nwarning! for L: "<<fixed<<controllaL<<endl;
       }
       
}

 
 
int main()
{
	int n;
        float p;
 
	cout<<"Random graph generation: ";
 
	// Take the input of the vertex and edges.
	cout<<"\nEnter the number of vertexes the graph have: ";
	cin>>n;
	cout<<"\nEnter the probability to link two nodes: ";
	cin>>p;
 
	// A function to generate a random undirected graph with e edges and v vertexes.
	GenerateRandGraphs(n, p);
}
