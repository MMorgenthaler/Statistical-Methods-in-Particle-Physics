#include "TH1D.h"
#include "TCanvas.h"
#include "TMinuit.h"
#include "TMath.h"
#include "TF1.h"
#include "TImage.h"
#include "TLegend.h"
#include "TRandom3.h"

#include <iostream>
#include <vector>
using namespace std;

vector<double> dataGenerator (int nData) {
	vector<double> data;
	TRandom3* rndm = new TRandom3();
	for(unsigned i=0; i<nData; i++) data.push_back(rndm->Exp(1.));
	
	return data;
}

double NLL(vector<double> x, double *param){
	double tau  = param[0];
	double l = 0;
	int nData = 100;

	for(unsigned i = 0; i < nData; i++){
		l -= TMath::Log(tau)+x[i]/tau; 
	}
	// minus sign because of NLL
	return -l;
}

void fcn(int & npar, double * gin, double & f, double * par, int iflag){
	f = NLL(dataGenerator(100), par);
	return;
}

static std::vector<double> fitParam(){
	TMinuit minuit;
	minuit.SetFCN(fcn);
	minuit.SetErrorDef(0.5);
	minuit.DefineParameter(0, "tau", 1., 0.001, 0.01, 3);
	minuit.Migrad();
	minuit.Print();
	
	double tau_fit, tau_fit_error;
	minuit.GetParameter(0, tau_fit, tau_fit_error);

	cout << "Part b)" << endl;
	std::cout << "Tau = "  << tau_fit << std::endl;

	std::vector<double> result;
	result.push_back(tau_fit);
	result.push_back(tau_fit_error);

	return result;
}

// Definition of decay law
double Decay(double* x, double* param){
	double tau = param[0];
	double f = exp(-x[0]/tau)/tau;
	return f;
}

void exercise6_2() {
	TH1D* h = new TH1D("histo", "histo", 30, 0, 3);
	TCanvas* c = new TCanvas("c", "c");
	int nData = 100;
	vector<double> data = dataGenerator(nData);
	std::vector<double> fit_values = fitParam();
	
	// Draw Histogram
	for(unsigned i = 0; i < nData; i++){
		h->Fill(data[i]);
	}
	h->SetTitle("Distribution of measurements");
	h->SetXTitle("Value [/]");
	h->SetYTitle("Counts [/]");
	h->SetFillColor(kGreen);
	h->SetStats(false);
	h->Draw();

	// Draw gaussian with fixed sigma
	TF1* decay = new TF1("f", Decay, 0.001, 3, 1);
	decay->SetParameter(0, fit_values[0]);
	decay->SetLineColor(1);
	decay->Draw("same");

	// Draw legend
	TLegend * legend = new TLegend(0.6, 0.75, 0.9, 0.9);
	legend->SetHeader("Legend", "C");
	legend->AddEntry(h, "data", "f");
	legend->AddEntry(decay, "decay law", "l");
	legend->Draw("same");

	// Save figure
	TImage* img = TImage::Create();
	img->FromPad(c);
	img->WriteImage("exercise6_2.png");
}
