#include<iostream>
#include<cstdlib>
#include<cmath>
#include<time.h>
#include<iomanip>
#include<fstream>
#include<vector>

#define n 50
#define N 1000
#define step 5000

using namespace std;

//PROGRAMMA SIMULA RANDOM WALK SENZA VINCOLI

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

struct Particle
{
	Particle(){};
        void SetIndex(int index){fIndex=index;} 
        int GetIndex() {return fIndex;}
        int fIndex;
};


int main()
{


	srand(time(NULL));
        Node node[n];
        Particle particle[N];
        float A[n][n]; //Adjacency
        int k[n];     //degree
        int index;
        ofstream dati1("walk.txt");
        ofstream dati2("walk2.txt");
	ofstream dati3("walk3.txt");
	ofstream dati4("walk4.txt");
	ofstream dati5("walk5.txt");

      	/*//define the Aacency matrix
      	A[0][0]=A[1][1]=A[2][2]=A[3][3]=0;
      	A[0][1]=A[1][0]=A[0][3]=A[3][0]=0;
      	A[0][2]=A[2][0]=A[1][2]=A[2][1]=1;
      	A[3][1]=A[1][3]=A[3][2]=A[2][3]=1;
      	//define the degree
      	k[0]=1,k[1]=2,k[2]=3,k[3]=2;*/
      
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
        /*node[0].SetNparticle(N/2);
        node[1].SetNparticle(N/4);
        node[2].SetNparticle(3*N/20);
        node[4].SetNparticle(N/10);*/
        for(int i=0;i<n;i++) node[i].SetNparticle(N/n);
        //Set the initial condition for each particle
        /*for(int i=0; i<N/2; i++) particle[i].SetNode(node[0]);
        for(int i=N/2; i<3*N/4; i++) particle[i].SetNode(node[1]);
        for(int i=3*N/4; i<18*N/20; i++) particle[i].SetNode(node[2]);
        for(int i=18*N/20; i<N; i++) particle[i].SetNode(node[3]);*/
        int z=0;
        for(int i=0;i<N;i++)
        {       
                if(i%50==0) z=0;
        	particle[i].SetIndex(z);
                z++;
        }


       //RANDOM WALK
       for(int i=0; i<N; i++)
       {
       cout<<"particella "<<i<<" parte dal nodo "   <<particle[i].GetIndex()<<endl;
       for(int t=0; t<step; t++)
       {
	       int x=rand()%node[particle[i].GetIndex()].GetDegree();
                node[particle[i].GetIndex()].OutParticle();
                index=node[particle[i].GetIndex()].fP[x];
                particle[i].SetIndex(index);
                node[index].InParticle();
                if(t>30)
                {
                	dati1<<node[0].GetNparticle()<<endl;
		        dati2<<node[20].GetNparticle()<<endl;
		        dati3<<node[35].GetNparticle()<<endl;
		        dati4<<node[49].GetNparticle()<<endl;
			dati5<<node[index].GetNparticle()<<endl;
		}
                
       }
       }
       




}
        
