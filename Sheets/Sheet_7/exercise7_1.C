#include "TF1.h"
#include "RooFit.h"
#include <math.h>
#include <iostream>

int Ndata = 500;

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
	//Data muss noch generiert werden
	/*
	RooRealVar t("t", "t", 0, 10);
	RooRealVar lambda("lambda", "lambda", 0.3);
	RooGenericPdf pdfA("pdfA", "pdfA", "exp(-t)*(1+lambda*sin(0.7*t)", RooArgSet(t, lambda));
	RooGenericPdf pdfB("pdfB", "pdfB", "exp(-t)*(1-lambda*sin(0.7*t)", RooArgSet(t, lambda));
	RooDataSet* datasetA = pdfA.generate(t, Ndata);
	RooDataSet* datasetB = pdfA.generate(t, Ndata);
	datasetA->Print("v");
	//double dataA = datasetA->get(0)->find("t")->GetVal();
	*/
	
	TF1* toBeIntA = new TF1("toBeIntA", ShannonA, 5., 15., Ndata);
	TF1* toBeIntB = new TF1("toBeIntB", ShannonB, 5., 15., Ndata);
	TF1* toBeIntC = new TF1("toBeIntC", ShannonC, 5., 15., Ndata);
	
	for(int i=0; i<Ndata; i++) {
		toBeIntA->SetParameter(i, dataA[i]);
		toBeIntB->SetParameter(i, dataB[i]);
	}
	
	for(int j=0; j<Ndata/2; j++) {
		toBeIntC->SetParameter(j, dataA[j]);
		toBeIntC->SetParameter(j+Ndata/2, dataB[j]);	
	}

	double uncerA = 1./sqrt(toBeIntA->Integral(-TMath::infinity(), TMath::infinity())); 
	double uncerB = 1./sqrt(toBeIntB->Integral(-TMath::infinity(), TMath::infinity())); 
	double uncerC = 1./sqrt(toBeIntC->Integral(-TMath::infinity(), TMath::infinity())); 
	
	
	std::cout << "Uncertainty a: " << uncerA << std::endl;
	std::cout << "Uncertainty b: " << uncerB << std::endl;
	std::cout << "Uncertainty c: " << uncerC << std::endl;
}
