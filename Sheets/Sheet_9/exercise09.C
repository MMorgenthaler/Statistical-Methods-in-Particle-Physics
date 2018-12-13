#include "exercise09.h"

#include "TFile.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TMath.h"
#include "TImage.h"
#include "TLegend.h"
#include <math.h>
#include <iostream>
using namespace std;

/*
given information:
	prediction: particle with m = 751 GeV
				decay particle -> photon photon
				30 signal events per 100 bkg events
				
	signal: 	Gaussian with std = 30 GeV
	background: exponential with slope a = -10^-3 GeV^-1
*/

vector<double> TestStatQ (vector<vector<double>> data) {
	vector<double> Q (amount_MC, 1.);
	double LH1, LH0;
	
	for(int i=0; i<amount_MC; i++) {
		for(auto x:data[i]) { 
			LH1 = normalizationH1*(gauss_height*exp(-0.5*pow((x-mean)/sigma,2)) + exp(0.+a*x));
			LH0 = normalizationH0*exp(0.+a*x);
			Q[i] *= LH1/LH0;
		}
	}
	return Q;
};

void ScaleAndNormCalc() {
	// calculate the signal height relative to bkg to gain 30 signal evts for 100 bkg events
	TF1* sig_pdf = new TF1 ("Signal_pdf", "gaus(0)", mLow, mHigh);
	sig_pdf->SetParameters(1., mean, sigma);
	TF1* bkg_pdf = new TF1 ("Signal_pdf", "expo(0)", mLow, mHigh);
	bkg_pdf->SetParameters(0., a);
	gauss_height = (30./130.)*(bkg_pdf->Integral(mLow, mHigh))/(sig_pdf->Integral(mLow, mHigh));
	
	normalizationH0 = 1./bkg_pdf->Integral(mLow,mHigh);
	
	// define combined pdf and calculate normalization
	TF1* H1_pdf = new TF1 ("H1_pdf", "gaus(0) + expo(3)", mLow, mHigh);
	// gaus(0) substitutes [0]*exp(-0.5*((x-[1])/[2])**2) 
	// expo(3) substitutes exp([3]+[4]*x)
	H1_pdf->SetParameters(gauss_height, mean, sigma, 0., a); 
	normalizationH1 = 1./H1_pdf->Integral(mLow,mHigh);
}

vector<double> H1_MC_generator () {
	vector<double> H1_MC;
	
	// define combined pdf
	TF1* H1_pdf = new TF1 ("H1_pdf", "gaus(0) + expo(3)", mLow, mHigh);
	// gaus(0) substitutes [0]*exp(-0.5*((x-[1])/[2])**2) 
	// expo(3) substitutes exp([3]+[4]*x)
	H1_pdf->SetParameters(gauss_height, mean, sigma, 0., a); 
	// generate data
	for(int i=0; i<evts; i++) H1_MC.push_back(H1_pdf->GetRandom());
	
	return H1_MC;
}

vector<double> H0_MC_generator () {
	vector<double> H0_MC;
	
	TF1* H0_pdf = new TF1 ("H0_pdf", "exp([0]+[1]*x)", mLow, mHigh); 
	// expo(0) substitutes exp([0]+[1]*x)
	H0_pdf->SetParameters(0., a); 
	for(int i=0; i<evts; i++) H0_MC.push_back(H0_pdf->GetRandom());
	
	return H0_MC;
}

void plot_b (vector<double> H0_MC, vector<double> H1_MC) {
	TCanvas* cb = new TCanvas("cb","cb");
	TH1D* H0 = new TH1D("H0", "example MC simulations", bins, mLow, mHigh);
	TH1D* H1 = new TH1D("H1", "example MC simulations", bins, mLow, mHigh);
	
	for(auto m0:H0_MC) H0->Fill(m0);
	for(auto m1:H1_MC) H1->Fill(m1);
	
	H1->SetXTitle("m [GeV]");
	H1->SetFillColor(38);
	H1->SetStats(false);
	H1->Draw();

	H0->SetFillColor(46); 
	H0->SetFillStyle(3004); 
	H0->SetLineColor(2);
	H0->SetLineWidth(2);
	H0->Draw("same");
	
	// Draw legend
	TLegend * legend = new TLegend(0.11, 0.75, 0.39, 0.9);
	legend->SetHeader("Legend", "C");
	legend->AddEntry(H0, "bkg only", "f");
	legend->AddEntry(H1, "bkg + signal", "f");
	legend->Draw("same");

	// Save figure
	TImage* img = TImage::Create();
 	img->FromPad(cb);
  	img->WriteImage("exercise09_b.png");
  	delete img;
}

void plot_c (vector<double> H0_Qs, vector<double> H1_Qs) {
	TCanvas* cc = new TCanvas("cc","cc");
	TH1D* QH0 = new TH1D("QH0", "test statistics Q for MC simulations", bins, -9300., -8600.);
	TH1D* QH1 = new TH1D("QH1", "test statistics Q for MC simulations", bins, -9300., -8600.);
	
	for(auto Q0:H0_Qs) QH0->Fill(Q0);
	for(auto Q1:H1_Qs) QH1->Fill(Q1);
	
	QH1->SetXTitle("test statistic Q [/]");
	QH1->SetFillColor(38);
	QH1->SetStats(false);
	QH1->Draw();

	QH0->SetFillColor(46); 
	QH0->SetFillStyle(3004); 
	QH0->SetLineColor(2);
	QH0->SetLineWidth(2);
	QH0->Draw("same");
	
	// Draw legend
	TLegend* legend = new TLegend(0.11, 0.75, 0.39, 0.9);
	legend->SetHeader("Legend", "C");
	legend->AddEntry(QH0, "bkg only", "f");
	legend->AddEntry(QH1, "bkg + signal", "f");
	legend->Draw("same");

	// Save figure
	TImage* img = TImage::Create();
 	img->FromPad(cc);
  	img->WriteImage("exercise09_c.png");
  	delete img;
}


void exercise09 () {
	ScaleAndNormCalc();
	vector<vector<double>> H1_MCs; 
	vector<vector<double>> H0_MCs; 
	for(int i=0; i<amount_MC; i++) H1_MCs.push_back(H1_MC_generator());
	for(int i=0; i<amount_MC; i++) H0_MCs.push_back(H0_MC_generator());
	plot_b(H0_MCs[0], H1_MCs[0]);
	vector<double> QH1 = TestStatQ(H1_MCs);
	vector<double> QH0 = TestStatQ(H0_MCs);
	plot_c(QH0, QH1);
}
