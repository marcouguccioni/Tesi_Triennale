#include<iostream>
#include<cstdlib>
#include<cmath>
#include<time.h>
#include<iomanip>
#include<fstream>
#include<vector>

#define n 50
#define N 2500
#define step 1000000
#define q 100

//IL PROGRAMMA SIMULA IL RANDOM WALK CON NODE CAPACITY CONSTRAINTS

using namespace std;

struct Node
{       
        Node(){};
        int GetNparticle() const {return fNparticle;}
  	int GetDegree() const {return fDegree;}
        void SetNearNodes()
        {       
                
                int j=0;
         	this->fP=new int[this->fDegree];
         	for(int i=0; i<n; i++)
         	{
                	if(this->fA[i]==1) this->fP[j]=i,j++;
         	}
                if(j!=this->fDegree) cout<<"warning"<<endl;
               
        }
       
        void InParticle() {fNparticle+=1;}
        void OutParticle(){fNparticle-=1;}
        void SetDegree(int degree){fDegree=degree;}
        void SetNparticle(int nparticle){fNparticle=nparticle;}
        void SetAdjacency(float *A){for(int i=0;i<n;i++) fA[i]=A[i];}
  	int fNparticle;
  	int fDegree;
        float fA[n];
        int* fP;
        
};

int main()
{


	srand(time(NULL));
        Node node[n];
        float A[n][n]; //Adjacency
        int k[n];     //degree
        int index;
        ofstream dati1("walk.txt");
        ofstream dati2("walk2.txt");
	ofstream dati3("walk3.txt");
	ofstream dati4("walk4.txt");
        ofstream dati5("walk5.txt");
	int sum,average;

	//GRADO 2-REGOLARE
      	/*//define the Aacency matrix
      	for(int i=0; i<n; i++)
        for(int j=0; j<n; j++) A[i][j]=0;
        for(int i=1; i<n; i++) A[i-1][i]=A[i][i-1]=1;
        A[99][0]=A[0][99]=1;
      	//define the degree
      	for(int i=0;i<n;i++) k[i]=2;*/

	 double theta,prob=0.2;
        cout<<"Realizzo un Network da "<<n<<" nodi."<<endl;
	for(int i=0;i<n;i++) 
        { 
         	for(int j=0;j<n;j++) 
         	{ 
           	theta=(double)rand()/(RAND_MAX);
           	if(theta<prob || theta==prob) {A[i][j]=A[j][i]=0;}
           	else {A[i][j]=A[j][i]=1;}
           	A[j][j]=0;
         	}
       }
       //Define the degree
       for(int i=0; i<n; i++)
       for(int j=0; j<n; j++)
       k[i]+=A[i][j];
        
      
        


        //set the Adjacency of the node
        for(int i=0;i<n;i++) node[i].SetAdjacency(A[i]);
	//Set the degree of the node
        for(int i=0;i<n;i++) node[i].SetDegree(k[i]);
        //Set the near node 
        for(int i=0; i<n; i++) node[i].SetNearNodes();
        //Set the the initial condition on node
        for(int i=0;i<n/2;i++) node[i].SetNparticle(10);
	for(int i=n/2;i<n;i++) node[i].SetNparticle(90);
        


       //RANDOM WALK
       for(int t=0; t<step; t++)
       {
	       int d=0;
	       do
	       d=rand()%n;
	       while(node[d].GetNparticle()==0);
               cout<<"\nNodo "<<d<<" ha "<<node[d].GetNparticle()
	       <<" particelle e ";
	       int z=0;
	       do
               { 
	       z++;
	       if(z==1000) {index=d; cout<<" salta il turno e "; break;}
	       int x=rand()%node[d].GetDegree();
	       index=node[d].fP[x];
               }
               while(node[index].GetNparticle()==q);
                node[d].OutParticle();
                node[index].InParticle();
                cout<<" da particelle al nodo "<<index;
                if(t>30)
                {
                	dati1<<node[0].GetNparticle()<<endl;
		        dati2<<node[25].GetNparticle()<<endl;
		        dati3<<node[50].GetNparticle()<<endl;
		        dati4<<node[75].GetNparticle()<<endl;
			dati5<<node[index].GetNparticle()<<endl;
		}
                
       }
       
       




}
        
