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
  TF1 * f_bkg = new TF1("f_bkg", "[0] * TMath::Exp(- x * [1])", 200, 1500);
  double A_bkg_ = 0.00167897;
  double a_ = 1e-3; // GeV⁻¹
  f_bkg->SetParameters(A_bkg_, a_);

  TF1 * f_sig = new TF1("f_sig", "[0] / (TMath::Sqrt(2.0 * TMath::Pi()) * [1]) * TMath::Exp(-0.5 * (TMath::Power((x - [2]) / (TMath::Sqrt(2) * [1]), 2)))", 200, 1500);
  double frac_ = 0.3; // how often is signal generated? 30/100!
  double A_sig_ = 0.03131;
  double sig_ = 30.0 / 2.3548; // FWHM in GeV
  double mu_ = 751.0; // in GeV
  f_sig->SetParameters(A_sig_, sig_, mu_);

  // generate values
  unsigned long M_ = 1e3;
  unsigned long N_ = 1e5;

  double ** arr_bkg = new double * [M_];
  double ** arr_sig = new double * [M_];
  for(unsigned i = 0; i < M_; i++){
    arr_bkg[i] = new double[N_];
    arr_sig[i] = new double[N_];
  }

  std::cout << "-- Generate data..." << std::endl;
  for(unsigned long i = 0; i < M_; i++){
    for(unsigned long j = 0; j < N_; j++){
      arr_bkg[i][j] = f_bkg->GetRandom();
      if(j > frac_ * N_){
        arr_sig[i][j] = f_bkg->GetRandom();
      }
      else{
        arr_sig[i][j] = f_sig->GetRandom();
      }
    }
    if(i % 50 == 0) std::cout << static_cast<double> (i) / 10 << "%" << std::endl;
  }

  TH1D * hist_bkg = new TH1D("hist_bkg_only", "Background only data", 200, 200, 1500);
  hist_bkg->SetFillColor(kBlue);
  hist_bkg->SetFillStyle(3005);
  TH1D * hist_sig = new TH1D("hist_bkg_sig", "Background and signal data", 200, 200, 1500);
  hist_sig->SetFillColor(kOrange);

  for(unsigned long i = 0; i < N_; i++){
    hist_bkg->Fill(arr_bkg[0][i]);
    hist_sig->Fill(arr_sig[0][i]);
  }

  TCanvas * canvas = new TCanvas("canvas", "canvas", 10, 10, 900, 600);
  hist_sig->Draw();
  hist_bkg->Draw("same");
  canvas->SaveAs("exercise09_MCdata.png");

  //std::cout << f_bkg->Eval(200.0) << std::endl;

  // calculate Lambda
  double L_H0[M_], L_H1[M_], Lambda[M_];
  double val_H0 = 0.0, val_H1 = 0.0;
  for(unsigned i = 0; i < M_; i++){
    for(unsigned j = 0; j < N_; j++){
      val_H0 += TMath::Log(A_bkg_) - a_ * arr_bkg[i][j];
      val_H1 += TMath::Log(A_bkg_) - a_ * arr_bkg[i][j] + TMath::Log(A_sig_) - TMath::Power(arr_sig[i][j] - mu_, 2) / sig_;
    }
    L_H0[i] = val_H0;
    L_H1[i] = val_H1;
    val_H0 = 0.0;
    val_H1 = 0.0;

    Lambda[i] = L_H1[i] / L_H0[i];
    std::cout << Lambda[i] << std::endl;
  }

  // create histogram with Lambda
  TH1D * hist_lambda = new TH1D("hist_lambda", "Distribution of Lambda", 100, 1002, 1032); // 10115
  for(unsigned i = 0; i < M_; i++){
    hist_lambda->Fill(Lambda[i]);
  }
  TCanvas * canvas2 = new TCanvas("canvas2", "canvas2", 10, 10, 900, 600);
  hist_lambda->SetFillColor(kOrange);
  hist_lambda->SetTitle("Distribution of #Lambda");
  hist_lambda->SetXTitle("#Lambda value");
  hist_lambda->SetYTitle("Number of points");
  hist_lambda->Draw();
  canvas2->SaveAs("exercise09_Lambda.png");


  // clean memory
  for(unsigned i = 0; i < M_; i++){
    delete[] arr_bkg[i];
    delete[] arr_sig[i];
  }
  delete[] arr_bkg;
  delete[] arr_sig;
  delete hist_bkg;
  delete hist_sig;
  delete canvas;
  delete f_bkg;
  delete f_sig;
  delete rndm;

  exit(1);

  return;
}
