#include <iostream>

#include "TRandom3.h"
#include "TF1.h"
#include "TMath.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TString.h"
#include "TLatex.h"

void exercise09_2(){
  TRandom3 * rndm = new TRandom3();
  rndm->SetSeed(822826282124240);

  // create functions for background + signal and background only data
  TF1 * f_bkg = new TF1("f_bkg", "[0] * TMath::Exp([1] * x)", 200, 1500);
  double A_bkg = 0.00167897;
  double a = -1.0e-3; // GeV⁻¹
  f_bkg->SetParameters(A_bkg, a);

  TF1 * f_sig = new TF1("f_sig", "[0] * TMath::Exp(-0.5 * (TMath::Power((x - [2]) / (TMath::Sqrt(2) * [1]), 2)))", 200, 1500);
  double A_sig = 0.03131;
  double sig = 30.0; // FWHM in GeV
  double mu = 751.0; // in GeV
  f_sig->SetParameters(A_sig, sig, mu);

  TF1 * f_comb = new TF1("f_comb", "[0] * 10.0 / 13.0 * TMath::Exp([1] * x) + [2] * 3.0 / 13.0 * TMath::Exp(-0.5 * (TMath::Power((x - [3]) / (TMath::Sqrt(2) * [4]), 2)))", 200, 1500);
  double A_comb = 0.03126;
  f_comb->SetParameters(A_bkg, a, A_sig,mu, sig);


  // generate values
  unsigned long M = 1e3;
  unsigned long N = 1e5;

  // random variables to be stored in
  double ** arr_bkg = new double * [M];
  double ** arr_comb = new double * [M];
  for(unsigned i = 0; i < M; i++){
    arr_bkg[i] = new double[N];
    arr_comb[i] = new double[N];
  }

  double frac = 10.0 / 13.0;

  // calculate Lambda
  double Lambda1[M], Lambda2[M];

  for(unsigned i = 0; i < M; i++){
    Lambda1[i] = 1.0;
    Lambda2[i] = 1.0;
  }

  double test1 = 1.0, test2 = 1.0; // used for testing

  std::cout << "-- Progress" << std::endl;
  for(unsigned long i = 0; i < M; i++){
    for(unsigned long j = 0; j < N; j++){
      arr_bkg[i][j] = f_bkg->GetRandom();
      arr_comb[i][j] = f_comb->GetRandom();
      // Lambda for s+b hypothesis
      Lambda1[i] *= f_comb->Eval(arr_comb[i][j]) / f_bkg->Eval(arr_bkg[i][j]);
      test1 *= f_comb->Eval(arr_comb[i][j]);
      test2 *= f_bkg->Eval(arr_comb[i][j]);
    }
    Lambda2[i] = test1 / test2;
    std::cout << Lambda1[i] << "  " << Lambda2[i] << std::endl;
    test1 = 1.0;
    test2 = 1.0;
  }


  TH1D * hist_bkg = new TH1D("hist_bkg_only", "Background only data", 200, 200, 1500);
  hist_bkg->SetFillColor(kBlue);
  hist_bkg->SetFillStyle(3005);
  TH1D * hist_comb = new TH1D("hist_comb", "Background and signal data", 200, 200, 1500);
  hist_comb->SetFillColor(kOrange);

  for(unsigned long i = 0; i < N; i++){
    hist_bkg->Fill(arr_bkg[0][i]);
    hist_comb->Fill(arr_comb[0][i]);
  }

  TCanvas * canvas = new TCanvas("canvas", "canvas", 10, 10, 900, 600);
  hist_comb->Draw();
  hist_bkg->Draw("same");
  canvas->SaveAs("exercise09_MCdata.png");
}
