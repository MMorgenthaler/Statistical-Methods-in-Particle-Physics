#include "TF1.h"
#include "RooFit.h"
#include <math.h>
#include <iostream>

int Ndata = 500;

Double_t pdfA(Double_t *val, Double_t *par) {
	return exp(-val[0])*(1+0.3*sin(0.7*val[0]));
};

Double_t pdfB(Double_t *val, Double_t *par) {
	return exp(-val[0])*(1-0.3*sin(0.7*val[0]));
};

Double_t ShannonA(Double_t *val, Double_t *par) {
	double lambda = val[0];
	double lLdev = 0; 
	
	for (int i=0; i<Ndata; i++) {
		lLdev += pow(sin(0.7*par[i])/(1+lambda*sin(0.7*par[i])), 2);
	}
	return lambda*lLdev;
};

Double_t ShannonB(Double_t *val, Double_t *par) {
	double lambda = val[0];
	double lLdev = 0; 
	
	for (int i=0; i<Ndata; i++) {
		lLdev += pow(sin(0.7*par[i])/(1-lambda*sin(0.7*par[i])), 2);
	}
	return lambda*lLdev;
};

Double_t ShannonC(Double_t *val, Double_t *par) {
	double lambda = val[0];
	double lLdev = 0; 
	
	for (int i=0; i<Ndata/2; i++) {
		lLdev += pow(sin(0.7*par[i])/(1+lambda*sin(0.7*par[i])), 2);
		lLdev += pow(sin(0.7*par[i+Ndata/2])/(1-lambda*sin(0.7*par[i+Ndata/2])), 2);
	}
	return lambda*lLdev;
};


void exercise7_1() {
	double inf = std::numeric_limits<double>::infinity();
	
	TF1* toBeIntA = new TF1("toBeIntA", ShannonA, 0., 10., Ndata);
	TF1* toBeIntB = new TF1("toBeIntB", ShannonB, 0., 10., Ndata);
	TF1* toBeIntC = new TF1("toBeIntC", ShannonC, 0., 10., Ndata);
	
	TF1* fA = new TF1("fA",pdfA,0.,10.);
	TF1* fB = new TF1("fB",pdfB,0.,10.);
	
	double dataA[Ndata], dataB[Ndata];
	
	for(int i=0; i<Ndata; i++) {
		dataA[i] = fA->GetRandom();
		toBeIntA->SetParameter(i, dataA[i]);
		
		dataB[i] = fB->GetRandom();
		toBeIntB->SetParameter(i, dataB[i]);
	}

	for(int j=0; j<Ndata/2; j++) {
		toBeIntC->SetParameter(j, dataA[j]);
		toBeIntC->SetParameter(j+Ndata/2, dataB[j]);	
	}

	double uncerA = 1./sqrt(toBeIntA->Integral(0., 1000)); 
	double uncerB = 1./sqrt(toBeIntB->Integral(0., 1000)); 
	double uncerC = 1./sqrt(toBeIntC->Integral(0., 1000)); 
	
	
	std::cout << "Uncertainty a: " << uncerA << std::endl;
	std::cout << "Uncertainty b: " << uncerB << std::endl;
	std::cout << "Uncertainty c: " << uncerC << std::endl;
}
