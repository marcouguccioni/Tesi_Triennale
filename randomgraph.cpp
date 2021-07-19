#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

 
using namespace std;

//PROGRAMMA SIMULA GRADO DI ERDOS G(n,m)
 
// A function to generate random graph.
void GenerateRandGraphs( int n_link, int n_edge)
{
	int i, j, edge[n_edge][2], count;
        bool adj[n_link][n_link];
        for(i=0;i<n_link;i++) for(j=0;j<n_link;j++) adj[i][j]=false;
	i = 0;
	// Build a connection between two random vertex.
	while(i < n_edge)
	{
		edge[i][0] = rand()%n_link+1;
		edge[i][1] = rand()%n_link+1;
 
		if(edge[i][0] == edge[i][1])
			continue;
		else
		{
			for(j = 0; j < i; j++)
			{
				if((edge[i][0] == edge[j][0] && edge[i][1] == edge[j][1]) || (edge[i][0] == edge[j][1] && edge[i][1] == edge[j][0]))
					i--;
			}
		}
		i++;
	}
 
	// Print the random graph.
	cout<<"\nThe generated random random graph is: ";
	for(i = 0; i < n_link; i++)
	{
		count = 0;
		cout<<"\n\t"<<i+1<<"-> { ";
		for(j = 0; j < n_edge; j++)
		{
			if(edge[j][0] == i+1)
			{       adj[i][edge[j][1]-1]=true;
				cout<<edge[j][1]<<"   ";
				count++;
			}
			else if(edge[j][1] == i+1)
			{       adj[i][edge[j][0]-1]=true;
				cout<<edge[j][0]<<"   ";
				count++;
			}
			else if(j == n_edge-1 && count == 0)
				cout<<"Isolated Vertex!";
		}
		cout<<" }";
	}

       //Print the adjacency matrix.	
       cout<<"\nThe adicency matrix of the graph is: ";
       for(i=0; i<n_link; i++)
       { 
               cout<<endl;
               for(j=0; j<n_link; j++)
               cout<<adj[i][j]<<",";
       }
       
      
}

 
 
int main()
{
	int n,m;
 
	cout<<"Random graph generation: ";
 
	// Take the input of the vertex and edges.
	cout<<"\nEnter the number of vertexes the graph have: ";
	cin>>n;
	cout<<"\nEnter the number of edges the graph have: ";
	cin>>m;
 
	// A function to generate a random undirected graph with e edges and v vertexes.
	GenerateRandGraphs(n, m);
}
