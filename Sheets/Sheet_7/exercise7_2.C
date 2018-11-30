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

Double_t Movement(Double_t * x, Double_t * par){
  Double_t x_ = x[0];
  Double_t p_ = par[0]
  Double_t q_ = par[1]; // value here
  Double_t B_ = par[2]; // value here
  return TMath::Sqrt(TMath::Power(p_ / (q_ * B_), 2) - TMath::Power(x_, 2));
}



void fcn(Int_t & npar, Double_t * gin, Double_t & f, Double_t * par, Int_t iflag)
{
  Double_t chi2 = 0.0;
  Double_t delta = 0.0;
  Double_t sigma_x = 0.0;
  Double_t sigma_z = 0.0002;

  Int_t n = 10;
/*
  for(unsigned i = 0; i < n; i++){
    delta = 1.0 / sigma_z *
  }


   const Int_t nbins = 5;
   Int_t i;

   //calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   for (i=0;i<nbins; i++) {
     delta  = (z[i]-func(x[i],y[i],par))/errorz[i];
     chisq += delta*delta;
   }
   f = chisq;
   */
}
void exercise7_2(){
  // Open file and save input of tree
  TFile * ifile = new TFile("exercise07.root", "read");
  TTree * itree = (TTree *) ifile->Get("hits");

  unsigned long N = itree->GetEntries();
  unsigned M = 10; // number of z val in tree


  Int_t n_ = 0;
  TBranch * b_n_;
  itree->SetBranchAddress("n", & n_, & b_n_);
  Double_t x_[M]; // in meter
  TBranch * b_x_;
  itree->SetBranchAddress("x", & x_, & b_x_);
  Double_t z_[M]; // in meter
  TBranch * b_z_;
  itree->SetBranchAddress("z", & z_, & b_z_);

  Int_t n[N];
  Double_t x[N][M], z[N][M];

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
  multigraph->GetXaxis()->SetTitle("z value");
  multigraph->GetYaxis()->SetTitle("x value");
  legend->Draw("same");
  canvas->SaveAs("./tracks.png");

  // Uncertainties for x and z direction.
  double sigma_x = 0.0;
  double sigma_z = 0.0002;


  exit(1);
  return;
}
