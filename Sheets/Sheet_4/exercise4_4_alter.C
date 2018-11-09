#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TImage.h"
#include "TRandom3.h"
#include "TLegend.h"
#include <math.h>
#include <iostream>
using namespace std;

void exercise4_4() {
	double evts = 1000000;
	double count=0;
	double dist = 0.1;
	double rad = 0.02;
	double ang = atan(rad/dist);
	double phi, theta;
	double pi = TMath::Pi();
	int bins = 100;
	TRandom3* rand3 = new TRandom3();
	TH2D* hAngle = new TH2D("hAngle", "Distribution of phi and theta", bins, -pi, pi, bins, -0.5*pi, 0.5*pi);
	TH1D* hTheta = new TH1D("hTheta", "Distribution of theta", bins, -0.5*pi, 0.5*pi);
	TCanvas* c1 = new TCanvas("c1", "c1");
	TCanvas* c2 = new TCanvas("c2", "c2");
	
	for(long int i=0; i<evts; i++) {
		phi = rand3->Rndm()*2.*pi-pi;         //-pi to pi
		theta = rand3->Rndm()*pi-0.5*pi;      //-0.5pi to 0.5pi
		
		
		if((phi < ang && phi > -ang) && 
		   (theta < ang && theta > -ang) &&
		   sqrt(tan(phi)*tan(phi) + tan(theta)*tan(theta)) < rad/dist) {
		   count++; 
		   hAngle->Fill(phi,theta);
		   hTheta->Fill(theta);
		}
	}		
	prob = count/evts;
	cout << "MC probability to hit detector: " << prob << endl;
	
	c1->cd();
	hAngle->SetXTitle("phi [rad]");
	hAngle->SetYTitle("theta [rad]");
	hAngle->SetStats(false);
	hAngle->Draw("COLZ");
	
	c2->cd();
	hTheta->SetXTitle("theta [rad]");
	hTheta->SetYTitle("counts [/]");
	hTheta->SetStats(false);
	hTheta->Draw();
	
	
}
