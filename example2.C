#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include "TRandom.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TStyle.h"

#define N 100
#define vertex 4
#define walkers 10000
using namespace std;

//IL PROGRAMMA L'ANDAMENTO DEL RANDOM WALK PER NETWORK A 4 NODI

 //le due componenti dei punti sono p e t

static int angolo1=0,angolo2=0,zoom=0,X=0,Y=0;
static double puntiT[vertex][N]; 
static double puntiP[vertex][N];
double dPuntiP[vertex][N];
double dPuntiSum[N]={0};
static int conteggio=0,incremento=0;
double adj[vertex][vertex];
double grado[vertex]={0};
double L[vertex][vertex];
double T[vertex][vertex];
        


void RANDOM_WALK(double *p,double *p0, double t) 
//RANDOM-WALK
{
 int conta;
 double index;
 double h=1;
 //=t/(double)N;
 
 //while(h>1) {h/=10;}
 
 for(int j=0 ; j<vertex; j++)
 {
  conta=0;
  for(int i=0 ; i<N; i++) { puntiT[j][i]=(h*conta), ++conta;}
  if(conta!=N) cout<<"warning"<<endl;
 }

 for(int t=0 ; t<N ; t++)
  { //RANDOM-WALK

     for(int i=0; i<vertex; i++)
     {  
        p[i]=0;
     	for(int j=0; j<vertex; j++)
        {
         p[i]+=(adj[i][j]/grado[j])*p0[j];
        }
        
     }
      
      for(int i=0; i<vertex; ++i) {puntiP[i][t]=p0[i];p0[i]=p[i];}
    

  }//RANDOM-WALK
  
}

int main()
{  

       double p0[vertex]={0};
       double p[vertex]={0};
       double pstaz[vertex]={0};
       double t,m=0;
       char c;
       p0[0]=0.5*walkers,p0[1]=0.25*walkers,p0[2]=0.15*walkers, p0[3]=0.1*walkers;
       
       
       double theta,prob;
    
       cout<<"Realizzo un Network da "<<vertex<<" nodi."<<endl<<"Inserisci la probabilità: ";

       
      //define the adjacency matrix
      adj[0][0]=adj[1][1]=adj[2][2]=adj[3][3]=0;
      adj[0][1]=adj[1][0]=adj[0][3]=adj[3][0]=0;
      adj[0][2]=adj[2][0]=adj[1][2]=adj[2][1]=1;
      adj[3][1]=adj[1][3]=adj[3][2]=adj[2][3]=1;
      //define the degree
      grado[0]=1,grado[1]=2,grado[2]=3,grado[3]=2;

      
      //Print the adjacency matrix.	
       cout<<"\nThe adicency matrix of the graph is: ";
       for(int i=0; i<vertex; i++)
       { 
               cout<<endl;
               for(int j=0; j<vertex; j++)
               cout<<adj[i][j]<<",";
       }
       cout<<endl<<endl<<endl;
       //Print the diagonal degree matrix.	
       cout<<"\nThe diagonal degrees matrix of the graph is: ";
       for(int i=0; i<vertex; i++)
       { 
               cout<<endl;
               for(int j=0; j<vertex; j++)
               {if(i==j) cout<<grado[j]<<","; else cout<<0<<",";}
       }

       //Define the stochastic matrix
       cout<<"\nPrint the stochastic matrix:"<<endl;
       for(int i=0;i<vertex;i++) 
       {
                cout<<endl;
       		for(int j=0;j<vertex;j++)
                {
       		T[i][j]=adj[i][j]/grado[j];
                cout<<T[i][j]<<",";
                }
                
       }

       //Define the laplacian matrix
       cout<<"\nPrint the laplacian matrix: "<<endl;
       for(int i=0;i<vertex;i++) 
       {
                cout<<endl;
       		for(int j=0;j<vertex;j++)
       		{ 
        		if(i==j) L[i][j]=1-T[i][j];
        		else L[i][j]=-T[i][j];
                        cout<<L[i][j]<<",";
       		}
       }

       RANDOM_WALK(p,p0,t); 
    
     for(int i=0; i<vertex; i++) m+=grado[i];
     for(int i=0; i<vertex; i++) pstaz[i]=grado[i]/m;


     for(int i=0; i<vertex; i++)
     for(int j=0; j<N; j++) 
     {
      dPuntiP[i][j]=puntiP[i][j]-pstaz[i];
      if(dPuntiP[i][j]<0) dPuntiP[i][j]=-dPuntiP[i][j];
     }
     
     
     for(int k=0; k<N; k++)
     for(int t=0; t<vertex; t++) dPuntiSum[k]+=dPuntiP[t][k];

      TGraph *hParticle[vertex];
      TMultiGraph *mg = new TMultiGraph();
      for(int i=0;i<vertex;i++) 
      {
       hParticle[i]=new TGraph (N,puntiT[i],puntiP[i]);
       hParticle[i]->SetLineWidth(2);
       hParticle[i]->SetLineStyle(1);
       hParticle[i]->SetMarkerStyle(8);
  
       mg->Add(hParticle[i]);
      }
      hParticle[0]->SetLineColor(kRed);
      hParticle[1]->SetLineColor(kViolet);
      hParticle[2]->SetLineColor(kBlue);
      hParticle[3]->SetLineColor(kGreen+1);
      hParticle[0]->SetMarkerColor(kRed);
      hParticle[1]->SetMarkerColor(kViolet);
      hParticle[2]->SetMarkerColor(kBlue);
      hParticle[3]->SetMarkerColor(kGreen+1);
      mg->SetTitle("Frazione di walkers sui nodi del network");
      mg->GetYaxis()->SetTitleOffset(1.2);
      mg->GetXaxis()->SetTitleSize(0.04);
      mg->GetYaxis()->SetTitleSize(0.04);
      mg->GetXaxis()->SetTitle("tempo");
      mg->GetYaxis()->SetTitle("popolazione sul nodo");
      mg->Draw("APL");
      
      /*gROOT->SetStyle("Plain");
      gStyle->SetOptStat(111110);
      gStyle->SetOptFit(111);
      TF1 *f1 = new TF1("exponential","expo",0,16);
      f1->SetLineColor(kRed);
      f1->SetParameter(1,-0.771);

      TGraph *hRelax1 =new TGraph (N,puntiT[0],dPuntiSum);
      hRelax1->SetTitle("differenza della frazione di popolazione rispetto lo stato stazionario");
      hRelax1->GetYaxis()->SetTitleOffset(1.2);
      hRelax1->GetXaxis()->SetTitleSize(0.04);
      hRelax1->GetYaxis()->SetTitleSize(0.04);
      hRelax1->GetXaxis()->SetTitle("tempo");
      hRelax1->GetYaxis()->SetTitle("delta P");
      hRelax1->SetLineColor(kBlack);
      hRelax1->SetLineWidth(2);
      hRelax1->SetLineStyle(1);
      hRelax1->Fit(f1,"","",4,16);
      hRelax1->Draw("AC");*/

     
      

   
   
}



