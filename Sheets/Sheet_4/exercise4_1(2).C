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
   

void exercise4_1() {
  long int nmb = 20;
  long int big_nmb = 10000;
  vector<long int> seeds (nmb);
  vector<double> random;
  for(int i=0; i<nmb ; i++) seeds[i] = 234509143 + i; 
  
  for(int i=0; i<nmb; i++) {
    random = BBS(seeds[i], nmb);
    cout << "20th random number of seed " << seeds[i] << " :" << random[nmb-1] << endl;
  }
  
  TH1D* hRndm = new TH1D ("hRndm", "histogram of 10000 numbers of the same seed", 100, 0, 1);
  TCanvas* c1 = new TCanvas("c1", "c1"); 
  random = BBS(seeds[0], big_nmb);
  for(auto i:random) hRndm->Fill(i);
  hRndm->SetXTitle("random number [/]");
  hRndm->SetYTitle("counts [/]");
  hRndm->Draw();
  
  //save as png
  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("exercise4_1.png");
}
  
 
