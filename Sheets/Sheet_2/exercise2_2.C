#include <iostream>
#include "TMath.h"
#include "TF1.h"
using namespace std;

double triangle(double *x, double *par){
  //par[0]=c, par[1]=a, par[2]=b
  if (par[1]<=x[0] && x[0]<par[0]) return 2.*(x[0]-par[1])/((par[2]-par[1])*(par[0]-par[1]));
  else if (par[0]<=x[0] && x[0]<par[2]) return 2.*(par[2]-x[0])/((par[2]-par[1])*(par[2]-par[0]));
  else return 0;
};

double triangleForMean(double *x, double *par){
  if (par[1]<=x[0] && x[0]<par[0]) return 2.*x[0]*(x[0]-par[1])/((par[2]-par[1])*(par[0]-par[1]));
  else if (par[0]<=x[0] && x[0]<par[2]) return 2.*x[0]*(par[2]-x[0])/((par[2]-par[1])*(par[2]-par[0]));
  else return 0;
};

double triangleForVar(double *x, double *par){
  if (par[1]<=x[0] && x[0]<par[0]) return (x[0]-par[3])*(x[0]-par[3])*2.*(x[0]-par[1])/((par[2]-par[1])*(par[0]-par[1]));
  else if (par[0]<=x[0] && x[0]<par[2]) return (x[0]-par[3])*(x[0]-par[3])*2.*(par[2]-x[0])/((par[2]-par[1])*(par[2]-par[0]));
  else return 0;
};


void exercise2_2(){
  // part a
  double a, b1, b2, c;
  double mean1, mode1, med1, var1;
  const Int_t nq = 1000;
  Double_t xq[nq];
  Double_t sq[nq];
  for (int i=0;i<nq;i++) sq[i] = double(i+1)/nq;
  
  a = -1.;
  b1 = -a;
  c = 0.;
    
  TF1* fct1 = new TF1("fct1",triangle,-10.,10.,3);
  fct1->SetParameters(c, a, b1);
  mode1 = fct1 -> GetMaximumX(a,b1);
  
  TH1F* hFct1 = new TH1F("histo of fct1","histo of fct1",nq,a,b1);
  hFct1 -> FillRandom("fct1", 1e8);
  hFct1 -> GetQuantiles(nq, xq, sq);
  for(int i=0; i<nq; i++) if(sq[i] == 0.5) med1 = xq[i];
  
  TF1* fct1Mean = new TF1("fct1",triangleForMean,-10.,10.,3);
  fct1Mean->SetParameters(c, a, b1);
  mean1 = fct1Mean -> Integral(a,b1);
  
  TF1* fct1Var = new TF1("fct1",triangleForVar,-10.,10.,4);
  fct1Var->SetParameters(c, a, b1, mean1);
  var1 = fct1Var-> Integral(a, b1);
  
  cout << "Part a)" << endl;
  cout << "  Mode: " << mode1 << endl;
  cout << "  Mean: " << mean1 << endl;
  cout << "  Median: " << med1 << endl;   
  cout << "  Variance: " << var1 << endl << endl;
  
  // part b
  double mean2, mode2, med2, var2;
  
  b2 = -0.5*a;

  TF1* fct2 = new TF1("fct2",triangle,-10.,10.,3);
  fct2->SetParameters(c, a, b2);
  mode2 = fct2 -> GetMaximumX(a,b2);
  
  TH1F* hFct2 = new TH1F("histo of fct2","histo of fct2",nq,a,b2);
  hFct2 -> FillRandom("fct2", 1e8);
  hFct2 -> GetQuantiles(nq, xq, sq);
  for(int i=0; i<nq; i++) if(sq[i] == 0.5) med2 = xq[i];
 
  TF1* fct2Mean = new TF1("fct1",triangleForMean,-10.,10.,3);
  fct2Mean->SetParameters(c, a, b2);
  mean2 = fct2Mean -> Integral(a,b2);
  
  TF1* fct2Var = new TF1("fct1",triangleForVar,-10.,10.,4);
  fct2Var->SetParameters(c, a, b2, mean2);
  var2 = fct2Var-> Integral(a, b2);

  cout << "Part b)" << endl;
  cout << "  Mode: " << mode2 << endl;
  cout << "  Mean: " << mean2 << endl;
  cout << "  Median: " << med2 << endl;   
  cout << "  Variance: " << var2 << endl << endl;
}







