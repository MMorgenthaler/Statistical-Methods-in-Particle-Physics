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

int nBins; //forgive me father for I have sinned 

vector<double> dataGenerator (int nData) {
	vector<double> data;
	TRandom3* rndm = new TRandom3();
	for(unsigned i=0; i<nData; i++) data.push_back(rndm->Exp(1.));
	
	return data;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double unbin_NLL(vector<double> x, double *param){
	double tau  = param[0];
	double l = 0;
	int nData = 100;

	for(unsigned i = 0; i < nData; i++){
		l -= TMath::Log(tau)+x[i]/tau; 
	}
	// minus sign because of NLL
	return -l;
}

void fcn_unbinned(int & npar, double * gin, double & f, double * par, int iflag){
	f = unbin_NLL(dataGenerator(100), par);
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double bin_ext_NLL(vector<double> x, double *param){
	double l = 0;
	int nData = x.size();
	double upper = 4;
	double lower = 0;
	//nBins = 8;//(upper-lower)*2;
	vector<double> nu;
	vector<double> bin;
	TH1D* h = new TH1D("histo", "histo", nBins, lower, upper);
	for (unsigned i=1; i<=nData; i++) h->Fill(x[i]);
	for (unsigned i=1; i<=nBins; i++) {
		nu.push_back(nData*h->Integral(h->GetBinLowEdge(i), h->GetBinLowEdge(i+1)));
		bin.push_back(h->GetBinContent(i));
	}

	for(unsigned j=0; j<nBins; j++){
		l += bin[j]*TMath::Log(nu[j]) - nu[j];
	}
	
	delete h;
	// minus sign because of NLL
	return -l;
}

void fcn_binned(int & npar, double * gin, double & f, double * par, int iflag){
	f = bin_ext_NLL(dataGenerator(100), par);
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static vector<double> fitParam(bool binned, int bins=1){
	nBins = bins;
	TMinuit minuit;
	if (binned) minuit.SetFCN(fcn_binned);
	else minuit.SetFCN(fcn_unbinned);
	minuit.DefineParameter(0, "tau", 1., 0.001, 0.01, 3);
	minuit.SetErrorDef(0.5);
	minuit.Migrad();
	minuit.Print();
	
	double tau_fit, tau_fit_error;
	minuit.GetParameter(0, tau_fit, tau_fit_error);

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
	double tau_unbin = fitParam(false)[0];
	double tau_8_bin = fitParam(true, 8)[0];
	double tau_1_bin = fitParam(true, 1)[0];
	double tau_1000_bin = fitParam(true, 1000)[0];
	
	cout << "part b)" << endl
		  << " tau_unbinned: " << tau_unbin << endl << endl;
	  
	cout << "part c)" << endl;
	cout << " tau_binned for delta t = 0.5s: " << tau_8_bin << endl;
	
	cout << "part d)" << endl;
	cout << " tau_binned for delta t -> inf: " << tau_1_bin << endl;
	cout << " tau_binned for delta t -> 0: " << tau_1000_bin << endl;
}
