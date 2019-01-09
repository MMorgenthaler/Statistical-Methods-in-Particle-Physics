#include "TRandom3.h"
#include "TH1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TImage.h"
#include <math.h>
#include <iostream>
using namespace std;

double exercise11_2() {
		double meanB = 1.8, alpha = 0.05, nobs = 5;
		double meanS_max, pChi;
		
		pChi = 1-alpha*TMath::Prob(2*meanB, 2*(nobs+1));
		meanS_max = 0.5*TMath::ChisquareQuantile(pChi, 2*(nobs+1))-meanB;
		cout << "exercise 11.2" << endl;
		cout << "  meanS_max = " << meanS_max << " for n_obs = 5" << endl << endl;
		
		return meanS_max;
}

void exercise11_3(double meanS_max) {
	int nobs = 5, n;
	double meanB = 1.8, nMC = 10000; counter = 0;
	TRandom* eventGenerator = new TRandom();
	TH1D* histo = new TH1D("histo","",26,-0.5,25.5);
	TCanvas* cc = new TCanvas("cc","cc");
	
	for(int i=0; i<nMC; i++) {
		n = eventGenerator->Poisson(meanB+meanS_max);
		histo->Fill(n);
		if(n<=nobs) counter++;
	}
	
	cout << "exercise 11.3" << endl;
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

void exercise11_2_and_3() {
	double meanS_max = exercise11_2();
	exercise11_3(meanS_max);
}
