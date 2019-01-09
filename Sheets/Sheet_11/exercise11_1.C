#include <math.h>
#include <iostream>
using namespace std;

void ProbAboveN(int mean=1) {
	int n = 0;
	double prob=0;
	
	while(prob<=0.9) {
		prob += TMath::PoissonI(n,mean);
		n++;
	}	
	cout << n << " or more events to have at most 10% probability to observe more for mean = " << mean <<endl;
}

void ProbBelowN(int mean=1) {
	int n = 0;
	double prob=0;
	
	while(prob<=0.1) {
		prob += TMath::PoissonI(n,mean);
		n++;
	}	
	cout << n-1 << " or less events to have at most 10% probability to observe less for mean = " << mean << endl;
}

void ProbCentralN(int mean=1) {
	int nLow = 0;
	int nHigh= 0;
	double probBelow=0;
	double probAbove=0;
	
	while(probBelow<=0.05) {
		probBelow += TMath::PoissonI(nLow,mean);
		nLow++;
	}	
	while(probAbove<=0.95) {
		probAbove += TMath::PoissonI(nHigh,mean);
		nHigh++;
	}	
	
	cout << nLow-1 << " or less and "  << nHigh << " or more events for a 10% probability central interval for mean = " << mean << endl;
}

void UpperCL(int n=0) {
	int mean = 1;
	double prob=0;
	
	while(prob<=0.1) {
		prob += TMath::PoissonI(n,mean);
		//cout << prob << endl;
		mean++;
	}	
	cout << "A mean of " << mean-1 << " or more is inside the upper 90% CL limit for " << n << " events" << endl;
}

void LowerCL(int n=0) {
	int mean = 1;
	double prob=0;
	
	while(prob<=0.9) {
		prob += TMath::PoissonI(n,mean);
		mean++;
	}	
	cout << "A mean of " << mean << " or less is inside the lower 90% CL limit for " << n << " events" << endl;
}

void CentralCL(int n=0) {
	int meanLow = 1;
	int meanHigh= 1;
	double probBelow=0;
	double probAbove=0;

	while(probBelow<=0.05) {
		probBelow += TMath::PoissonI(n,meanLow);
		meanLow++;
	}	
	while(probAbove<=0.95) {
		probAbove += TMath::PoissonI(n,meanHigh);
		meanHigh++;
	}	
	
	cout << "A mean of " << meanLow-1 << " or less and "  << meanHigh << " or more  for a 90% central CL for " << n << " events" << endl;
}

void exercise11_1() {
	cout << "Part a1)" << endl;
	for(int i=1; i<=12; i++) ProbAboveN(i);
	
	cout << endl << "Part a2)" << endl;
	for(int i=1; i<=12; i++) ProbBelowN(i);
	
	cout << endl << "Part a3)" << endl;
	for(int i=1; i<=12; i++) ProbCentralN(i);
	
	cout << endl << "Part b1)" << endl;
	for(int i=0; i<=12; i++) UpperCL(i);
	
	//cout << endl << "Part b2)" << endl;
	//for(int i=0; i<=12; i++) LowerCL(i);
	
	//cout << endl << "Part b3)" << endl;
	//for(int i=0; i<=12; i++) CentralCL(i);
}
