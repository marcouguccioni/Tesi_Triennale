
//IL PROGRAMMA REALIZZA GLI HISTOGRAMMI PER I RANDOM WALK

void makeHistogram(std::string fileName){
	using namespace std;
	ifstream ifs(fileName.c_str());
	int pi;
	TCanvas* c=new TCanvas("c","c",600,600);
	TH1D* hist=new TH1D("hist",fileName.c_str(),100,0+0.5,100+0.5);
	while(ifs.is_open() && !ifs.eof()){
		ifs >> pi;
		hist->Fill(pi);
	}
        
        TF1 *expq=new TF1("expq","[0]*(TMath::Exp([1]*(x-[3]))+TMath::Exp([2]*(x)))",0,100);
   	expq->SetParameter(0,10000000);
   	expq->SetParameter(1,0.02222);
	expq->SetParameter(2,-0.02);
	expq->SetParameter(3,100);
	
 
        //hist->Fit(poiss,"R");
        hist->Fit("expq");
	hist->Draw();
	std::string pngFileName=fileName+".png";
	std::string pdfFileName=fileName+".pdf";
	c->SaveAs(pngFileName.c_str());
	c->SaveAs(pdfFileName.c_str());
	ifs.close();
}
