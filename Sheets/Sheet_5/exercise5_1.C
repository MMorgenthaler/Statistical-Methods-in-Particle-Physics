#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom3.h"
#include "TImage.h"
#include <math.h>
#include <iostream>
using namespace std;

Double_t LogLikelihood_betafixed(Double_t *val, Double_t *par) {
	double alpha = val[0];
	double beta = 30.;
	int Ndata = 1024;
	
	double lL = 0; 
	for (int i=0; i<Ndata; i++) {
		lL += log((1/TMath::Pi()) * beta / (pow((par[i]-alpha),2) + pow(beta, 2)));
	}
	return lL;
};

Double_t LogLikelihood(Double_t *val, Double_t *par) {
	double alpha = val[0];
	double beta = val[1];
	int Ndata = 1024;
	
	double lL = 0; 
	for (int i=0; i<Ndata; i++) {
		lL += log((1/TMath::Pi()) * beta / (pow((par[i]-alpha),2) + pow(beta, 2)));
	}
	return lL;
};

void exercise5_1() {
	int Ndata = 1024;
	int bins = 100;
	double pi = TMath::Pi();
	double alpha = 10;
	double beta = 30;
	double alpha_est_1, alpha_est_2, beta_est;
	TRandom3* rndm = new TRandom3();
	vector<double> theta;
	vector<double> x_k;
	for(int i=0; i<Ndata; i++) {
		theta.push_back(rndm->Uniform(-0.5*pi, 0.5*pi)); 
		x_k.push_back(alpha + beta*tan(theta[i]));
	}

	TCanvas* c1 = new TCanvas("c1", "c1");
	c1->Divide(1,2);
	TF1* logLikelihood_betafixed = new TF1("logLikelihood_betafixed", LogLikelihood_betafixed, 5., 15., Ndata);
	TF2* logLikelihood = new TF2("logLikelihood", LogLikelihood, 5., 15., 25., 35., Ndata);
	for(int i=0; i<Ndata; i++) {
		logLikelihood_betafixed->SetParameter(i, x_k[i]);
		logLikelihood->SetParameter(i, x_k[i]);
	}
	
	c1->cd(1);
	logLikelihood_betafixed->Draw();
	alpha_est_1 = logLikelihood_betafixed->GetMaximumX();
        logLikelihood_betafixed->GetHistogram()->GetXaxis()->SetTitle("alpha");
        c1->Modified();
	cout << "part a)" << endl;
	cout << "  estimated alpha: " << alpha_est_1 << endl << endl;
	
	c1->cd(2);
	logLikelihood->Draw("SURF2");
	//logLikelihood->Draw("CONT1 SAME");
	logLikelihood->GetMaximumXY(alpha_est_2, beta_est);
	logLikelihood->GetHistogram()->GetXaxis()->SetTitle("alpha");
	logLikelihood->GetHistogram()->GetYaxis()->SetTitle("beta");
	cout << "part b)" << endl;
	cout << "  estimated alpha: " << alpha_est_2 << endl;
	cout << "  estimated beta: " << beta_est << endl;
	
	//save as png
	gSystem->ProcessEvents();
	TImage *img1 = TImage::Create();
	img1->FromPad(c1);
	img1->WriteImage("exercise5_1.png");
}
