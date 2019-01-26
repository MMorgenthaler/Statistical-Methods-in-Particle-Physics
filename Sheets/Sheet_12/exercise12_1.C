#include "TFile.h"
#include "TF1.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TMath.h"
#include "TImage.h"
#include "TLegend.h"
#include <math.h>
#include <iostream>
using namespace std;

void Step1(double alpha, float tau, double xmax) {
	TCanvas* c = new TCanvas("c", "c");
	c->Divide(3,3);	
	int counter = 1;
	
	while(tau <= 9) {
		c->cd(counter);
		
		TF1* f=new TF1("f", "1-TMath::Exp(-x/[0])",0,xmax);
		f->SetParameter(0,tau);
		string str_title = "#tau = " + to_string(tau) + " x 10^{-10}s";
		const char* title = str_title.c_str();
		f->SetTitle(title);
		f->GetHistogram()->SetXTitle("#tau_{0} [10^{-10}s]");
		f->GetHistogram()->SetYTitle("F_{#tau}(#tau_{0})");
		f->Draw();
		
		TLine *line = new TLine(-tau*log(1-alpha),alpha,xmax,alpha);
		line->SetLineWidth(2);
		line->Draw();
		
		counter++;
		tau += 0.3;
	}
	
	// Save figure
	TImage* img = TImage::Create();
 	img->FromPad(c);
  	img->WriteImage("exercise12_1a.png");
  	delete img;
}

void Step2(double alpha, float tau, double xmax) {
TCanvas* c2 = new TCanvas("c2", "c2");
	TF1* f=new TF1("f", "-x/log(1-[0])",0,xmax);
	f->SetParameter(0,alpha);
	f->SetTitle("Calculation of the upper limit #tau^{up}_{0}");
	f->GetHistogram()->SetXTitle("#tau_{0} [10^{-10}s]");
	f->GetHistogram()->SetYTitle("#tau [10^{-10}s]");
	f->Draw();
	
	while(tau <= 2.8) {
		TLine *line = new TLine(-tau*log(1-alpha),tau,xmax,tau);
		line->SetLineWidth(2);
		line->Draw();
		tau += 0.3;
	}	
	
	TLine *CLline = new TLine(0,-0.7/log(1-alpha),0.7,-0.7/log(1-alpha));
	CLline->SetLineWidth(2);
	CLline->SetLineColor(kGreen);
	CLline->Draw();
	
	TLine *obsline = new TLine(0.7,0,0.7,2.95);
	obsline->SetLineWidth(2);
	obsline->SetLineColor(kBlue);
	obsline->Draw();
	
	// Save figure
	TImage* img = TImage::Create();
 	img->FromPad(c2);
  	img->WriteImage("exercise12_1b.png");
  	delete img;
  	
  	cout << "The upper limit on the lifetime is tau >= " << -0.7/log(1-alpha) << " x 10^-10 s" << endl; 
}

void exercise12_1() { 
	double ttrue=0.7;
	double alpha = 1. - 0.68;
	double xmax1 = 5;
	double xmax2 = 1.1;
	float tau = 0.1;
	
	Step1(alpha,tau,xmax1);
	Step2(alpha,tau,xmax2);
	
}
