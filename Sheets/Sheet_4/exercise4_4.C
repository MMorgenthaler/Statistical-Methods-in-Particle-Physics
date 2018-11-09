#include "TH1D.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TImage.h"
#include "TLatex.h"

#include <iostream>

using namespace TMath;

void exercise4_4(){
	Double_t a = 0.02;
	Double_t l = 0.10; // r-h in sketch

	TRandom3 * Rand = new TRandom3();
	Rand->SetSeed(398672928729327);

	Int_t ntot = 1000000;
	Int_t accepted = 0;

	TH1D * hist = new TH1D("Distribution of #theta", "Distribution of #theta", 200, 0.0, Pi());

	for(Int_t i = 0; i < ntot; i++){
		Double_t a_phi = Tan(Rand->Uniform(0, 2 * Pi())) * l;
		Double_t a_theta = Tan(Rand->Uniform(0, Pi())) * l;
		hist->Fill(Rand->Uniform(0, Pi()));

		if((Power(a_phi, 2) + Power(a_theta, 2)) <= Power(a, 2)){
			accepted += 1;
		}
	}

	TCanvas * canvas = new TCanvas("canvas", "canvas", 10, 10, 900, 600);

	hist->Draw();

	TImage * img = TImage::Create();
  img->FromPad(canvas);
  img->WriteImage("exercise4_4_hist.png");

	Double_t p = static_cast<double> (accepted) / static_cast<double> (ntot) * 100.0;
	std::cout << "The probability of a photon to hit the detector is approximately " << p << " %." << std::endl;

	exit(1);

	return ;
}