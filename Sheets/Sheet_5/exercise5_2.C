#include "data_05.h"

#include "TH1D.h"
#include "TCanvas.h"
#include "TMinuit.h"
#include "TMath.h"
#include "TF1.h"
#include "TImage.h"
#include "TLegend.h"

#include <iostream>
#include <vector>

// Code for fixed sigma
double NLL_fixed(double * x, double * param){
	double mu  = param[0];
	double sig = 0.15;
	double l = 0;

	for(unsigned i = 0; i < numDataPoints; i++){
		l -= TMath::Log(2 * TMath::Pi() * TMath::Power(sig, 2)) + (TMath::Power(x[i] - mu, 2) / (2 * TMath::Power(sig, 2)));
	}
	// minus sign because of NLL
	return -l;
}

void fcn_fixed(int & npar, double * gin, double & f, double * par, int iflag){
	f = NLL_fixed(dataPoints, par);
	return;
}

static std::vector<double> fixed(){
	TMinuit minuit;
	minuit.SetFCN(fcn_fixed);
	minuit.SetErrorDef(0.5);
	minuit.DefineParameter(0, "mu", 40.0, 0.001, 38, 42);
	minuit.Migrad();
	minuit.Print();
	
	double mu_fit, mu_fit_error;
	minuit.GetParameter(0, mu_fit, mu_fit_error);

	std::cout << "----------" << std::endl;
	std::cout << "Beta fixed" << std::endl;
	std::cout << "Mu = "  << mu_fit << std::endl;
	std::cout << "Sig = " << 0.15 << std::endl << std::endl;

	std::vector<double> result;
	result.push_back(mu_fit);
	result.push_back(mu_fit_error);

	return result;
}

// Code for unfixed sigma
double NLL_unfixed(double * x, double * param){
	double mu  = param[0];
	double sig = param[1];
	double l = 0;

	for(unsigned i = 0; i < numDataPoints; i++){
		l -= TMath::Log(2 * TMath::Pi() * TMath::Power(sig, 2)) + (TMath::Power(x[i] - mu, 2) / (2 * TMath::Power(sig, 2)));
	}
	// minus sign because of NLL
	return -l;
}

void fcn_unfixed(int & npar, double * gin, double & f, double * par, int iflag){
	f = NLL_unfixed(dataPoints, par);
	return;
}

static std::vector<double> unfixed(){
	TMinuit minuit;
	minuit.SetFCN(fcn_unfixed);
	minuit.SetErrorDef(0.5);
	minuit.DefineParameter(0, "mu", 40.0, 0.001, 38, 42);
	minuit.DefineParameter(1, "sig", 0.2, 0.001, 0.0, 0.4);
	minuit.Migrad();
	minuit.Print();
	
	double mu_fit, mu_fit_error, sig_fit, sig_fit_error;
	minuit.GetParameter(0, mu_fit, mu_fit_error);
	minuit.GetParameter(1, sig_fit, sig_fit_error);

	std::cout << "----------" << std::endl;
	std::cout << std::endl << "Beta unfixed" << std::endl;
	std::cout << "Mu = "  << mu_fit << std::endl;
	std::cout << "Sig = " << sig_fit << std::endl << std::endl;

	std::vector<double> result;
	result.push_back(mu_fit);
	result.push_back(mu_fit_error);
	result.push_back(sig_fit);
	result.push_back(sig_fit_error);

	return result;
}

// Definition of gaussian function
double Gaussian(double * x, double * param){
	// param[0] = A
	// param[1] = mu
	// param[2] = sig

	double f = param[0] / (param[2] * TMath::Sqrt(2 * TMath::Pi())) * TMath::Exp(- TMath::Power(x[0] - param[1], 2) / (2 * TMath::Power(param[2], 2)));	
	return f;
}

// Function Plotting the results
static void Plotting(std::vector<double> fixed, std::vector<double> unfixed){
	TH1D * hist = new TH1D("hist", "hist", 40, 39.5, 40.3);
	TCanvas * canvas = new TCanvas("canvas", "canvas", 10, 10, 900, 600);

	// Draw Histogram
	for(unsigned i = 0; i < numDataPoints; i++){
		hist->Fill(dataPoints[i]);
	}
	hist->SetTitle("Distribution of measurements");
	hist->SetXTitle("Value");
	hist->SetYTitle("Number of points");
	hist->SetFillColor(kGreen);
	hist->Draw();

	// Draw gaussian with fixed sigma
	double sig = 0.15;
	TF1 * function_fixed = new TF1("f", Gaussian, 39, 41, 3);
	function_fixed->SetParameters(hist->GetMaximum(), fixed.at(0), sig);
	function_fixed->SetLineColor(1);
	function_fixed->Draw("same");

	// Draw gaussian with variable sigma
	TF1 * function_unfixed = new TF1("f", Gaussian, 39, 41, 3);
	function_unfixed->SetParameters(hist->GetMaximum(), unfixed.at(0), unfixed.at(2));
	function_unfixed->Draw("same");

	// Draw legend
	TLegend * legend = new TLegend(0.11, 0.75, 0.39, 0.9);
	legend->SetHeader("Legend", "C");
	legend->AddEntry(hist, "Distribution of data", "f");
	legend->AddEntry(function_fixed, "Fixed #beta", "l");
	legend->AddEntry(function_unfixed, "Unixed #beta", "l");
	legend->Draw("same");

	// Save figure
	TImage * img = TImage::Create();
        img->FromPad(canvas);
        img->WriteImage("exercise5_2.png");

	return;
}

// Main function
void exercise5_2(){
	Plotting(fixed(), unfixed());
        exit(1);
	return;
}
