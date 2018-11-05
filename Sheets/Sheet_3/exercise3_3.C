#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "TFile.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TString.h"
#include "TLatex.h"
#include "TImage.h"
#include "TLegend.h"

using namespace std;

void exercise3_3() {
  ifstream data; // data file to read
  string line; // string used to read the file
  vector<double> p, beta, e, m;
  double p_temp, beta_temp, e_temp, m_temp;
  double bins = 100;
  double p_low = 265;
  double p_high = 305;
  double beta_low = 0.87;
  double beta_high = 0.93;
  double e_low = 295;
  double e_high = 345;
  double m_low = 115;
  double m_high = 165;
  double p_mean, p_var, beta_mean, beta_var, e_mean, e_var, m_mean, m_var;
  double pBeta_cov, pE_cov, pM_cov, betaE_cov, betaM_cov, eM_cov;
  double pBeta_cor, pE_cor, pM_cor, betaE_cor, betaM_cor, eM_cor;
  // data to be read
  data.open ("exercise_3_3.txt");
	
  TCanvas* c1 = new TCanvas("c1","c1");
  c1->Divide(2,2);
  TCanvas* c2 = new TCanvas("c2","c2");
  c2->Divide(3,2);

  TH1D* hP = new TH1D("hP", "histogram of momentum", bins, p_low, p_high);
  TH1D* hBeta = new TH1D("hBeta", "histogram of beta", bins, beta_low,  beta_high);
  TH1D* hE = new TH1D("hE", "histogram of energy", bins, e_low, e_high);
  TH1D* hM = new TH1D("hM", "histogram of mass", bins, m_low, m_high);

  TH2D* hPBeta = new TH2D("hPBeta", "momentum versus beta", bins, p_low, p_high, bins, beta_low, beta_high);
  TH2D* hPE = new TH2D("hPE", "momentum versus energy ", bins, p_low, p_high, bins, e_low, e_high);
  TH2D* hPM = new TH2D("hPM", "momentum versus mass", bins, p_low, p_high, bins, m_low, m_high);
  TH2D* hBetaE = new TH2D("hBetaE", "beta versus energy", bins, beta_low, beta_high, bins, e_low, e_high);  
  TH2D* hBetaM = new TH2D("hBetaM", "beta versus mass", bins, beta_low, beta_high, bins, m_low, m_high);    
  TH2D* hEM = new TH2D("hEM", "energy versus mass", bins, e_low, e_high, bins, m_low, m_high);    
  

  if (data.is_open())
  {
    while (getline(data, line))
    {
      stringstream ss(line);
      ss >> p_temp >> beta_temp >> e_temp >> m_temp;
      p.push_back(p_temp);      
      beta.push_back(beta_temp);      
      e.push_back(e_temp);      
      m.push_back(m_temp);      

      hP->Fill(p_temp);
      hBeta->Fill(beta_temp);
      hE->Fill(e_temp);
      hM->Fill(m_temp);
      hPBeta->Fill(p_temp,beta_temp);
      hPE->Fill(p_temp,e_temp);
      hPM->Fill(p_temp,m_temp);
      hBetaE->Fill(beta_temp,e_temp);
      hBetaM->Fill(beta_temp,m_temp);
      hEM->Fill(e_temp,m_temp);
     
      p_mean += p_temp;
      beta_mean += beta_temp;
      e_mean += e_temp;
      m_mean += m_temp;
    }
  }
  else cout << "Unable to open data " << endl;
  data.close(); 
  
  // erase first line (string)
  p.erase(p.begin());
  beta.erase(beta.begin());
  e.erase(e.begin());
  m.erase(m.begin());
  
  double nevt = hP->GetEntries() -1.;
  
  p_mean /= nevt;
  beta_mean /= nevt;
  e_mean /= nevt;
  m_mean /= nevt;
  
  for(int i=1; i< nevt; i++) { 
    p_var += (p[i]-p_mean)*(p[i]-p_mean);
    beta_var += (beta[i]-beta_mean)*(beta[i]-beta_mean);
    e_var += (e[i]-e_mean)*(e[i]-e_mean);
    m_var += (m[i]-m_mean)*(m[i]-m_mean);
    pBeta_cov += (p[i]-p_mean)*(beta[i]-beta_mean);
    pE_cov += (p[i]-p_mean)*(e[i]-e_mean);
    pM_cov += (p[i]-p_mean)*(m[i]-m_mean);
    betaE_cov += (beta[i]-beta_mean)*(e[i]-e_mean);
    betaM_cov += (beta[i]-beta_mean)*(m[i]-m_mean);
    eM_cov += (e[i]-e_mean)*(m[i]-m_mean);
  }
  p_var /= nevt;
  beta_var /= nevt;
  e_var /= nevt;
  m_var /= nevt;
  pBeta_cov /= nevt;
  pE_cov /= nevt;
  pM_cov /= nevt;
  betaE_cov /= nevt;
  betaM_cov /= nevt;
  eM_cov /= nevt;

  cout << "Part a)" << endl;
  cout << "  mean of momentum p: " << p_mean << " [MeV]" << endl
       << "  mean of momentum p (TH1): " << hP->GetMean() << " [MeV]" << endl
       << "  variance of momentum p: " << p_var << " [MeV²]" << endl
       << "  variance of momentum p (TH1): " << pow(hP->GetRMS(),2) << " [MeV²]" << endl << endl
       
       << "  mean of beta: " << beta_mean << endl
       << "  mean of beta (TH1): " << hBeta->GetMean() << endl
       << "  variance of beta: " << beta_var << endl
       << "  variance of beta (TH1): " << pow(hBeta->GetRMS(),2) << endl << endl
       
       << "  mean of energy E: " << e_mean << " [MeV]" << endl
       << "  mean of energy E (TH1): " << hE->GetMean() << " [MeV]" << endl
       << "  variance of energy E: " << e_var << " [MeV²]" << endl
       << "  variance of energy E (TH1): " << pow(hE->GetRMS(),2) << " [MeV²]" << endl << endl
       
       << "  mean of mass M: " << m_mean << " [MeV]" << endl
       << "  mean of mass M (TH1): " << hM->GetMean() << " [MeV]" << endl
       << "  variance of mass M: " << m_var << " [MeV²]" << endl
       << "  variance of mass M (TH1): " << pow(hM->GetRMS(),2) << " [MeV²]" << endl << endl 
           
       << "  covariance of p and beta: " << pBeta_cov << " [MeV]" << endl    
       << "  covariance of p and beta (TH2): " << hPBeta->GetCovariance() << " [MeV]" << endl << endl
           
       << "  covariance of p and E: " << pE_cov << " [MeV²]" << endl
       << "  covariance of p and E (TH2): " << hPE->GetCovariance() << " [MeV²]" << endl << endl
        
       << "  covariance of p and m: " << pM_cov << " [MeV²]" << endl 
       << "  covariance of p and m (TH2): " << hPM->GetCovariance() << " [MeV²]" << endl << endl
       
       << "  covariance of beta and E: " << betaE_cov << " [MeV]" << endl 
       << "  covariance of beta and E (TH2): " << hBetaE->GetCovariance() << " [MeV]" << endl << endl
       
       << "  covariance of beta and m: " << betaM_cov << " [MeV]" << endl 
       << "  covariance of beta and m (TH2): " << hBetaM->GetCovariance() << " [MeV]" << endl << endl
       
       << "  covariance of E and m: " << eM_cov << " [MeV²]" << endl
       << "  covariance of E and m (TH2): " << hEM->GetCovariance() << " [MeV²]" << endl << endl; 

  pBeta_cor = pBeta_cov/sqrt(p_var*beta_var);
  pE_cor = pE_cov/sqrt(p_var*e_var);
  pM_cor = pM_cov/sqrt(p_var*m_var);
  betaE_cor = betaE_cov/sqrt(beta_var*e_var);
  betaM_cor = betaM_cov/sqrt(beta_var*m_var);
  eM_cor = eM_cov/sqrt(e_var*m_var);

  cout << "Part b)" << endl;
  cout << "  correlation of p and beta: " << pBeta_cor << endl
       << "  correlation of p and beta (TH2): " << hPBeta->GetCorrelationFactor() << endl << endl
       
       << "  correlation of p and E: " << pE_cor << endl
       << "  correlation of p and E (TH2): " << hPE->GetCorrelationFactor() << endl << endl
       
       << "  correlation of p and m: " << pM_cor << endl
       << "  correlation of p and m (TH2): " << hPM->GetCorrelationFactor() << endl << endl
       
       << "  correlation of beta and E: " << betaE_cor << endl
       << "  correlation of beta and E (TH2): " << hBetaE->GetCorrelationFactor() << endl << endl
       
       << "  correlation of beta and m: " << betaM_cor << endl
       << "  correlation of beta and m (TH2): " << hBetaM->GetCorrelationFactor() << endl << endl
       
       << "  correlation of E and m: " << eM_cor << endl
       << "  correlation of E and m (TH2): " << hEM->GetCorrelationFactor() << endl << endl;

  // not sure about this part d
  double eM_cov2;  
  for(int i=1; i< nevt; i++) {
    for(int j=1; i< nevt; i++) {
      eM_cov2 += ((p[i]*(1-beta[i])/beta[i]) - (p[j]*(1-beta[j])/beta[j])) * (p[i]/beta[i] - p[j]/beta[j]);
    }
  } 

  eM_cov2 /= 2*nevt*nevt;

  cout << "Part c)" << endl;
  cout << "  covariance of m and E calculated with p and beta: " 
       << eM_cov2 << endl << endl;  

  c1->cd(1);
  hP->SetXTitle("p [MeV]");
  hP->SetYTitle("counts [/]");
  hP->DrawCopy();

  c1->cd(2);
  hBeta->SetXTitle("Beta [/]");
  hBeta->SetYTitle("counts [/]");
  hBeta->DrawCopy();

  c1->cd(3);
  hE->SetXTitle("E [MeV]");
  hE->SetYTitle("counts [/]");
  hE->DrawCopy();

  c1->cd(4);
  hM->SetXTitle("m [MeV]");
  hM->SetYTitle("counts [/]");
  hM->DrawCopy();

  c2->cd(1);
  hPBeta->SetXTitle("p [MeV]");
  hPBeta->SetYTitle("Beta [/]");
  hPBeta->DrawCopy("COLZ");

  c2->cd(2);
  hPE->SetXTitle("p [MeV]");
  hPE->SetYTitle("E [MeV]");
  hPE->DrawCopy("COLZ");

  c2->cd(3);
  hPM->SetXTitle("p [MeV]");
  hPM->SetYTitle("m [MeV]");
  hPM->DrawCopy("COLZ");

  c2->cd(4);
  hBetaE->SetXTitle("Beta [/]");
  hBetaE->SetYTitle("E [MeV]");
  hBetaE->DrawCopy("COLZ");

  c2->cd(5);
  hBetaM->SetXTitle("Beta [/]");
  hBetaM->SetYTitle("m [MeV]");
  hBetaM->DrawCopy("COLZ");

  c2->cd(6);
  hEM->SetXTitle("E [MeV]");
  hEM->SetYTitle("m [MeV]");
  hEM->DrawCopy("COLZ");

  //save as png
  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("exercise3_3_1D.png");
  TImage *img2 = TImage::Create();
  img2->FromPad(c2);
  img2->WriteImage("exercise3_3_2D.png");

  hP->Delete();
  hBeta->Delete();
  hE->Delete();
  hM->Delete();
  hPBeta->Delete();
  hPE->Delete();
  hPM->Delete();
  hBetaE->Delete();
  hBetaM->Delete();
  hEM->Delete();
  
  return;
}
