#include <iostream>

#include "TF1.h"
#include "TMath.h"
#include "Math/WrappedTF1.h"
#include "Math/GaussIntegrator.h"

void GetVal(unsigned int & start, unsigned int & end, double & cl_max, double & res, TString & option);

void exercise11_1b(){
	unsigned int start = 0;
	unsigned int end = 12;
	double cl_max = 0.9;
	double res = 0.001;
	TString upper = "upper";
	TString lower = "lower";
	TString central = "central";


	GetVal(start, end, cl_max, res, upper);
	GetVal(start, end, cl_max, res, lower);
	GetVal(start, end, cl_max, res, central);

	return;
}

void GetVal(unsigned int & start, unsigned int & end, double & cl_max, double & res, TString & option){
	std::cout << "The " + option + " limit of nu is given below." << std::endl;
	TF1 * Poisson = new TF1("Poisson", "TMath::Exp(-x) * TMath::Power(x, [0]) / TMath::Factorial([0])", 0, 1e6);

	if(option == "upper"){
		double x = 0.0;	
		for(unsigned int i = start; i <= end; i++){
			Poisson->SetParameter(0, i);
			while(Poisson->Integral(0, x) < cl_max){
				x += res;
			}
			std::cout << "n = " << i << "\t" << "x = " << x << std::endl;
			x = 0.0;
		}
	}


	else if(option == "lower"){
		double x = 0.0;	
		for(unsigned int i = start; i <= end; i++){
			Poisson->SetParameter(0, i);
			while(Poisson->Integral(0, x) < 1.0 - cl_max){
				x += res;
			}
			std::cout << "n = " << i << "\t" << "x' = " << x << std::endl;
			x = 0.0;
		}
	}


	else if(option == "central"){
		double x = 0.0;
		double y = 0.0;
		double value = (1.0 - cl_max) / 2.0;
		for(unsigned int i = start; i <= end; i++){
			Poisson->SetParameter(0, i);
			while(Poisson->Integral(0, y) < 1.0 - cl_max - value){
				y += res;
			}
			while(Poisson->Integral(0, x) < cl_max + value){
				x += res;
			}
			std::cout << "n = " << i << "\t" << "x' = " << y << "\t" << "x = " << x << std::endl;
			y = 0.0;
			x = 0.0;
		}
	}


	return;
}