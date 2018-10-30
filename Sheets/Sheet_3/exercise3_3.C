#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
  double p, beta, e, m;
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
      ss >> p >> beta >> e >> m;
      hP->Fill(p);
      hBeta->Fill(beta);
      hE->Fill(e);
      hM->Fill(m);
      hPBeta->Fill(p,beta);
      hPE->Fill(p,e);
      hPM->Fill(p,m);
      hBetaE->Fill(beta,e);
      hBetaM->Fill(beta,m);
      hEM->Fill(e,m);
     
      p_mean += p;
      beta_mean += beta;
      e_mean += e;
      m_mean += m;
    }
  }
  else cout << "Unable to open data " << endl;
 
  p_mean /= hP->GetEntries();
  beta_mean /= hBeta->GetEntries();
  e_mean /= hE->GetEntries();
  m_mean /= hM->GetEntries();

  data.close(); 
 
  data.open ("exercise_3_3.txt");
  if (data.is_open())
  {
    while (getline(data, line))
    {
      stringstream ss(line);
      ss >> p >> beta >> e >> m;
     
      p_var += (p-p_mean)*(p-p_mean);
      beta_var += (beta-beta_mean)*(beta-beta_mean);
      e_var += (e-e_mean)*(e-e_mean);
      m_var += (m-m_mean)*(m-m_mean);
    }
  }
  else cout << "Unable to open data " << endl;
  p_var /= hP->GetEntries();
  beta_var /= hBeta->GetEntries();
  e_var /= hE->GetEntries();
  m_var /= hM->GetEntries();

  data.close();

  cout << "mean of momentum p: " << p_mean << " [MeV]" << endl
       << "variance of momentum p: " << p_var << " [MeV]" << endl << endl
       << "mean of beta: " << beta_mean << endl
       << "variance of beta: " << beta_var << endl << endl
       << "mean of energy E: " << e_mean << " [MeV]" << endl
       << "variance of energy E: " << e_var << " [MeV]" << endl << endl
       << "mean of mass M: " << m_mean << " [MeV]" << endl
       << "variance of mass M: " << m_var << " [MeV]" << endl << endl;       

  c1->cd(1);
  hP->SetXTitle("p [MeV]");
  hP->SetYTitle("counts [/]");
  hP->Draw();

  c1->cd(2);
  hBeta->SetXTitle("Beta [/]");
  hBeta->SetYTitle("counts [/]");
  hBeta->Draw();

  c1->cd(3);
  hE->SetXTitle("E [MeV]");
  hE->SetYTitle("counts [/]");
  hE->Draw();

  c1->cd(4);
  hM->SetXTitle("m [MeV]");
  hM->SetYTitle("counts [/]");
  hM->Draw();

  c2->cd(1);
  hPBeta->SetXTitle("p [MeV]");
  hPBeta->SetYTitle("Beta [/]");
  hPBeta->Draw("COLZ");

  c2->cd(2);
  hPE->SetXTitle("p [MeV]");
  hPE->SetYTitle("E [MeV]");
  hPE->Draw("COLZ");

  c2->cd(3);
  hPM->SetXTitle("p [MeV]");
  hPM->SetYTitle("m [MeV]");
  hPM->Draw("COLZ");

  c2->cd(4);
  hBetaE->SetXTitle("Beta [/]");
  hBetaE->SetYTitle("E [MeV]");
  hBetaE->Draw("COLZ");

  c2->cd(5);
  hBetaM->SetXTitle("Beta [/]");
  hBetaM->SetYTitle("m [MeV]");
  hBetaM->Draw("COLZ");

  c2->cd(6);
  hEM->SetXTitle("E [MeV]");
  hEM->SetYTitle("m [MeV]");
  hEM->Draw("COLZ");
/*
  //save as png
  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("exercise3_3_1D.png");
  TImage *img2 = TImage::Create();
  img2->FromPad(c2);
  img2->WriteImage("exercise3_3_2D.png");
*/
  return;
}
