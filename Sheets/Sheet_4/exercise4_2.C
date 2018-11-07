#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TImage.h"
#include <math.h>
#include <iostream>
using namespace std;

vector<double> BBS (long int seed, long int size) {
  long int prm1 = 33617; 
  long int prm2 = 5011;
  long int M = prm1*prm2;
  vector<double> random (size+1);
  random[0] = seed;
  
  for(int i=0; i< size; i++) random[i+1] = (long int)pow(random[i],2) % M; //seed + size values
  random.erase (random.begin()); // deletes seed as he wouldn't be in the intervall [0,1] for all cases
  for(int j=0; j< size; j++) random[j] /= M; // normalization
  
  return random;
};  

void exercise4_2() {
  long int nmb = 10000;
  long int seed =  29998559671349;
  double rndm;
  vector<double> rndm_uni, rndm_exp; 
  rndm_uni = BBS(seed, nmb);
  TRandom3* rand3 = new TRandom3(seed);
  TH1D* hBBS = new TH1D("hBBS", "histogram of BBS numbers", 100, 0, 10);
  TH1D* hRand3 = new TH1D("hRand3", "histogram of Random3 numbers", 100, 0, 10);
  TCanvas* c1 = new TCanvas("c1", "c1"); 
  
  for(auto i:rndm_uni) {
    hBBS->Fill(-TMath::Log(i));
    hRand3->Fill(rand3->Exp(1.));
  }
  
  hBBS-> SetFillColor(kOrange+10);
  hBBS-> SetLineColor(kOrange+10);
  hBBS-> SetFillStyle(3345);
  hBBS-> SetStats(0);
  hBBS-> SetXTitle("random number [/]");
  hBBS-> SetYTitle("counts [/]");
  hBBS-> SetTitle("Comparison of non-uniformly distributed random numbers");
  hBBS-> Draw("same");
  
  hRand3-> SetFillColor(kViolet+10);
  hRand3-> SetLineColor(kViolet+10);
  hRand3-> SetFillStyle(3354);
  hRand3-> Draw("same");
  
  auto legend = new TLegend(0.55,0.8, 0.9,0.9);
  legend->AddEntry("hBBS","transformed numbers","f");
  legend->AddEntry("hRand3","TRandom3 numbers","f");
  legend->Draw();
  
  //save as png
  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("exercise4_2.png");
}
