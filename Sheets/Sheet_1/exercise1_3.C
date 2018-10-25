#import <iostream>
#import "TH1F.h"

void exercise1_3() {
  int bins = 10
  double min = 0.
  double max = 10.
  TH1F* histo = new TH1F("histogram", bins, min, max);
  
  for(int i=1; i <= bins; ++i) histo->SetBinContent(i, i);
  
  TF1* fun = new TF1("function","[0]+x*[1]",0,10);
  fun->SetParameter(0,0.0);
  fun->SetParameter(1,1.0);
  
  TCanvas *c1 = new TCanvas("c1", "c1");
  fun->Draw("Same");
  histo->Draw("Same");
}
