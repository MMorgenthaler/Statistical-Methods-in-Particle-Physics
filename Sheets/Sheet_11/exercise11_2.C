#include "TMath.h"
#include <math.h>
#include <iostream>
using namespace std;

void exercise11_2() {
		double meanB = 1.8, alpha = 0.05, nobs = 5;
		double meanS_max, pChi;
		
		pChi = 1-alpha*TMath::Prob(2*meanB, 2*(nobs+1));
		meanS_max = 0.5*TMath::ChisquareQuantile(pChi, 2*(nobs+1))-meanB;
		cout << "meanS_max = " << meanS_max << " for n_obs = 5" << endl;
}
