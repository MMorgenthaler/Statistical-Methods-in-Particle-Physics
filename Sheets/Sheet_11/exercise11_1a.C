#include <iostream>

#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TMath.h"
#include "TString.h"

double Poisson(unsigned int & mean, unsigned int & n);
void GetValue(unsigned int & start, unsigned int & end, double & max_prob, TString & option);


void exercise11_1a(){
	// Parameters
	unsigned int start = 1;
	unsigned int end = 12;
	double max_prob = 0.9;
	TString above = "above";
	TString below = "below";
	TString equal = "equal";

	GetValue(start, end, max_prob, above);
	GetValue(start, end, max_prob, below);
	GetValue(start, end, max_prob, equal);

	exit(1);

	return;
}


double Poisson(unsigned int & mean, unsigned int & n){
	return TMath::Exp(-static_cast<double>(mean)) * TMath::Power(static_cast<double>(mean), static_cast<double>(n)) / static_cast<double>(TMath::Factorial(n));
}

void GetValue(unsigned int & start, unsigned int & end, double & max_prob, TString & option){
	std::cout << "For the case \'" + option + "\' you get the following results" << std::endl;

	if(option == "above"){
		unsigned int n = 0;
		double prob = 0.0;

		for(unsigned int i = start; i <= end; i++){
			while(prob < max_prob){
				prob += Poisson(i, n);
				n++;
			}
			std::cout << "mean = " << i << "\t" << "n = " << n << std::endl;
			prob = 0.0;
			n = 0;
		}
	}

	else if(option == "below"){
		unsigned int n = 0;
		double prob = 0.0;

		for(unsigned int i = start; i <= end; i++){
			while(prob < (1.0 - max_prob)){
				prob += Poisson(i, n);
				n++;
			}
			std::cout << "mean = " << i << "\t" << "n = " << n << std::endl;
			prob = 0.0;
			n = 0;
		}
	}

	else if(option == "equal"){
		unsigned int n = 0;
		unsigned int m = 0;
		double prob = 0.0;
		double value = (1.0 - max_prob) / 2.0;

		for(unsigned int i = start; i <= end; i++){
			while(prob < max_prob + value){
				prob += Poisson(i, n);
				n++;
			}
			prob = 0.0;
			while(prob < 1.0 - max_prob - value){
				prob += Poisson(i, m);
				m++;
			}
			prob = 0.0;

			std::cout << "mean = " << i << "\t" << "n' = " << m << "\t" << "n = " << n << std::endl;
			
			n = 0;
			m = 0;
		}
	}
	return;
}
