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

#define N 1500
#define vertex 4
using namespace std;

//IL PROGRAMMA SIMULA LA MASTER EQUATION PER NETWORK A 4 NODI

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
        


void MASTER_EQUATION(double *p,double *p0, double t) 
//MASTER EQUATION
{
 int conta;
 double index;
 double f0[vertex];
 double Y[vertex];
 double f1[vertex];
 double Z[vertex];
 double f2[vertex];
 double W[vertex];
 double f3[vertex];
 double h=0.01;
 //=t/(double)N;
 
 while(h>1) {h/=10;}
 
 for(int j=0 ; j<vertex; j++)
 {
  conta=0;
  for(int i=0 ; i<N; i++) { puntiT[j][i]=(h*conta), ++conta;}
  if(conta!=N) cout<<"warning"<<endl;
 }

 for(int j=0 ; j<N ; ++j)
  { //RUNGE-KUTTA

     //Master Equation calcolata in p0
     for(int i=0 ; i<vertex ; i++) 
     {
     f0[i]=0;
     for(int k=0 ; k<vertex ; k++)
     f0[i]-=L[i][k]*p0[k];
     }
     

    //campo ausiliario Y
     for(int i=0 ; i<vertex ; ++i) Y[i]=p0[i]+(h/2)*f0[i]; 
     
    //master equation calcolata in Y
     for(int i=0; i<vertex ; i++)
     {
     f1[i]=0;
     for(int k=0; k<vertex ; k++)     
     f1[i]-=L[i][k]*Y[k];
     }

    //campo ausiliario Z
     for(int i=0 ; i<vertex ; ++i) Z[i]=p0[i]+(h/2)*f1[i];

    //master equation calcolata in Z
     for(int i=0; i<vertex ; i++)
     {
     f2[i]=0;
     for(int k=0; k<vertex ; k++)     
     f2[i]-=L[i][k]*Z[k];
     }
     
    //campo ausiliario W
     for(int i=0 ; i<vertex ; ++i) W[i]=p0[i]+h*f2[i];

    //master equation calcolata in W
     for(int i=0; i<vertex ; i++)
     {
     f3[i]=0;
     for(int k=0; k<vertex ; k++)     
     f3[i]-=L[i][k]*W[k];
     }
     
    //ALGORITMO DI RUNGE KUTTA
     for(int i=0 ; i<vertex ; ++i) 
       p[i]=p0[i]+(h/6)*(f0[i]+2*f1[i]+2*f2[i]+f3[i]);
     
    
   /*cout<<setprecision(5)<<fixed<<setw(11)<<p0[0]
    <<setw(11)<<p0[1]
    <<setw(11)<<p0[2]<<endl;*/

  
      for(int i=0; i<vertex; ++i) {puntiP[i][j]=p0[i];p0[i]=p[i];}
    

  }//fine ciclo runge-kutta
  
}

int main()
{  

       double p0[vertex]={0};
       double p[vertex]={0};
       double pstaz[vertex]={0};
       double t,m=0;
       char c;
       p0[0]=0.5,p0[1]=0.25,p0[2]=0.15, p0[3]=0.1;
       
       
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

       MASTER_EQUATION(p,p0,t); 
    
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

      /*TGraph *hParticle[vertex];
      TMultiGraph *mg = new TMultiGraph();
      for(int i=0;i<vertex;i++) 
      {
       hParticle[i]=new TGraph (N,puntiT[i],puntiP[i]);
       hParticle[i]->SetLineWidth(2);
       hParticle[i]->SetLineStyle(1);
  
       mg->Add(hParticle[i]);
      }
      hParticle[0]->SetLineColor(kRed);
      hParticle[1]->SetLineColor(kViolet);
      hParticle[2]->SetLineColor(kBlue);
      hParticle[3]->SetLineColor(kGreen+1);
      mg->SetTitle("Frazione di walkers sui nodi del network");
      mg->GetYaxis()->SetTitleOffset(1.2);
      mg->GetXaxis()->SetTitleSize(0.04);
      mg->GetYaxis()->SetTitleSize(0.04);
      mg->GetXaxis()->SetTitle("tempo");
      mg->GetYaxis()->SetTitle("popolazione sul nodo");
      mg->Draw("AC");*/
      
      gROOT->SetStyle("Plain");
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
      hRelax1->Draw("AC");

     
      

   
   
}



