#include "TRandom3.h"
#include "TH1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TImage.h"
#include <math.h>
#include <iostream>
using namespace std;

void exercise11_3() {
	int nobs = 5, n;
	double meanB = 1.8, meanS = 8.73096, nMC = 10000; counter = 0;
	TRandom* eventGenerator = new TRandom();
	TH1D* histo = new TH1D("histo","",26,-0.5,25.5);
	TCanvas* cc = new TCanvas("cc","cc");
	
	for(int i=0; i<nMC; i++) {
		n = eventGenerator->Poisson(meanB+meanS);
		histo->Fill(n);
		if(n<=nobs) counter++;
	}
	cout << " The fraction of experiments resulting in an amount of events equal or less in comparison to n_obs = 5 is " << counter/nMC << endl; 
	
	histo->SetTitle("Distribution of events for the toy MC experiments");
	histo->SetStats(false);
	histo->SetXTitle("simulated amount of events n");
	histo->Draw();
	
	// Save figure
	TImage* img = TImage::Create();
 	img->FromPad(cc);
  	img->WriteImage("exercise11_3.png");
  	delete img;
}
