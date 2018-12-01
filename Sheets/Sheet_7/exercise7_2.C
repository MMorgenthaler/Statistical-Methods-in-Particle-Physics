#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <TLegend.h>
#include <TMinuit.h>
#include <TMath.h>
#include <TF1.h>
#include <TH1D.h>

Int_t n[5000], val = 0;
Double_t x[5000][10], z[5000][10];

Double_t Gamma(Double_t & v){
  Double_t c = 2.99; // 10⁻⁸ m s⁻¹
  v /= 1e8; // 10⁻⁸ m s⁻¹
  return 1.0 / TMath::Sqrt(1 - TMath::Power((v / c), 2));
}

Double_t Movement(Double_t & x_, Double_t * par){
  Double_t v_ = par[0]; // Kg m s⁻¹
  Double_t O_ = par[1]; // Offset from zero
  Double_t q_ = 1.602e-19; // C
  Double_t B_ = 0.1; // T
  Double_t me_ = 9.11e-31; // Kg
  Double_t c = 2.99e8; // m s⁻¹
  return TMath::Sqrt(TMath::Power(me_ * v_ * Gamma(v_)/ (c * B_ * q_), 2) - TMath::Power(x_, 2)) - O_;
}

void fcn(Int_t & npar, Double_t * gin, Double_t & f, Double_t * par, Int_t iflag)
{
  Double_t chi2 = 0.0;
  Double_t delta = 0.0;
  Double_t sigma_x = 0.0;
  Double_t sigma_z = 0.0002;

  for(unsigned i = 0; i < 10; i++){
    delta = (x[val][i] - Movement(z[val][i], par)) / sigma_z;
    chi2 += TMath::Power(delta, 2);
  }
  f = chi2;
}

void exercise7_2(){
  // Open file and save input of tree
  TFile * ifile = new TFile("exercise07.root", "read");
  TTree * itree = (TTree *) ifile->Get("hits");

  unsigned M = 10; // number of z val in tree
  unsigned long N = itree->GetEntries();

  Int_t n_ = 0;
  TBranch * b_n_;
  itree->SetBranchAddress("n", & n_, & b_n_);
  Double_t x_[M]; // in meter
  TBranch * b_x_;
  itree->SetBranchAddress("x", & x_, & b_x_);
  Double_t z_[M]; // in meter
  TBranch * b_z_;
  itree->SetBranchAddress("z", & z_, & b_z_);

  for(unsigned i = 0; i < N; i++){
    itree->GetEntry(i);
    n[i] = n_;
    for(unsigned j = 0; j < M; j++){
      x[i][j] = x_[j];
      z[i][j] = z_[j];
    }
  }

  // Plot first five tracks
  TCanvas * canvas = new TCanvas("canvas", "canvas", 10, 10, 900, 600);
  TMultiGraph * multigraph = new TMultiGraph();
  TLegend * legend = new TLegend(0.15, 0.2, 0.33, 0.4);
  TGraph * g[5];

  legend->SetHeader("Legend", "C");

  for(unsigned i = 0; i < 5; i++){
    g[i] = new TGraph(M, z[i], x[i]);
    g[i]->SetLineColor(i + 40);
    TString name = "track no. " + std::to_string(i+1);
    legend->AddEntry(g[i], name, "l");
    multigraph->Add(g[i], "lp*");
  }
  multigraph->Draw("a");
  multigraph->SetTitle("First five tracks");
  multigraph->GetXaxis()->SetTitle("z value in [m]");
  multigraph->GetYaxis()->SetTitle("x value in [m]");
  legend->Draw("same");
  canvas->SaveAs("./tracks.png");

  // Uncertainties for x and z direction.
  double sigma_x = 0.0;
  double sigma_z = 0.0002;

  // Fitting the model to the data
  TMinuit minuit;
  // suppress ouput printing
  minuit.SetPrintLevel(-1);

  // save momentum, kin energy values and their errors in array
  Double_t velo_[N];

  for(val; val < N; val++){
    minuit.SetFCN(fcn);
    minuit.SetErrorDef(0.5);
    minuit.DefineParameter(0, "Momentum", 1e19, 0.001, 0, 0);
    minuit.DefineParameter(1, "Offset", -0.02, 0.001, 0, 0);
    minuit.Migrad();

    Double_t velocity, velocity_err;
    minuit.GetParameter(0, velocity, velocity_err);

    velo_[val] = velocity;
  }
  std::cout << velo_[0] << std::endl;

  exit(1);
  return;
}
