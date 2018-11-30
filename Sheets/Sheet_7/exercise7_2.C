#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <TLegend.h>

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
  TLegend * legend = new TLegend(0.15, 0.2, 0.53, 0.4);
  TGraph * g[5];

  legend->SetHeader("Legend", "C");

  for(unsigned i = 0; i < 5; i++){
    g[i] = new TGraph(M, x[i], z[i]);
    g[i]->SetLineColor(i + 40);
    TString name = "track no. " + std::to_string(i+1);
    legend->AddEntry(g[i], name, "l");
    multigraph->Add(g[i], "lp*");
  }
  multigraph->Draw("a");
  legend->Draw("same");
  canvas->SaveAs("./tracks.png");

  exit(1);
  return;
}
