#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TImage.h"
#include "TRandom3.h"
#include "TLegend.h"
#include <math.h>
#include <iostream>
using namespace std;

void exercise4_3() {
  long int seed =  29998559671349;
  long int entries = 10000;
  vector<double> k2(2); 
  vector<double> k10(10); 
  vector<double> k30(30);
  TCanvas* c1 = new TCanvas("c1", "c1"); 
  TH1D* hRndm2  = new TH1D ("hRndm2", "", 100, -0.5, 3);
  TH1D* hRndm10 = new TH1D ("hRndm10", "", 100, -0.5, 3);
  TH1D* hRndm30 = new TH1D ("hRndm30", "", 100, -0.5, 3);
  
  TRandom3 *rand3 = new TRandom3(seed);
  for(int i=0; i < entries; i++) {
    for(int j=0; j<k2.size(); j++) k2[j] = rand3->Exp(1.);
    for(int j=0; j<k10.size(); j++) k10[j] = rand3->Exp(1.);
    for(int j=0; j<k30.size(); j++) k30[j] = rand3->Exp(1.);
    
    hRndm2 ->Fill(TMath::Mean(k2.begin(),  k2.end()));
    hRndm10->Fill(TMath::Mean(k10.begin(), k10.end()));
    hRndm30->Fill(TMath::Mean(k30.begin(), k30.end()));
  } 
  
  hRndm30-> SetFillColor(kOrange+10);
  hRndm30-> SetLineColor(kOrange+10);
  hRndm30-> SetFillStyle(3345);
  hRndm30-> SetStats(0);
  hRndm30-> SetXTitle("mean [/]");
  hRndm30-> SetYTitle("counts [/]");
  hRndm30-> SetTitle("Central limit theorem");
  hRndm30-> Draw();
  
  hRndm10-> SetFillColor(kViolet+10);
  hRndm10-> SetLineColor(kViolet+10);
  hRndm10-> SetFillStyle(3354);
  hRndm10-> Draw("same");
  
  hRndm2-> SetFillColor(kGreen+1);
  hRndm2-> SetLineColor(kGreen+1);
  hRndm2-> SetFillStyle(3395);
  hRndm2-> Draw("same");
  
  auto legend = new TLegend(0.55,0.7, 0.9,0.9);
  legend->AddEntry("hRndm2","mean of 2 rndm numbers","f");
  legend->AddEntry("hRndm10","mean of 10 rndm numbers","f");
  legend->AddEntry("hRndm30","mean of 30 rndm numbers","f");
  legend->Draw();
  
  //save as png
  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("exercise4_3.png");
}
