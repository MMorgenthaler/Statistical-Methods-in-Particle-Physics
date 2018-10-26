// Import libraries

#include "TFile.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TString.h"
#include "TLatex.h"
#include "TImage.h"
#include "TLegend.h"

#include <iostream>

static void Histogram(){
	// Get input file 

	TString input_file_name = "exercise_02_3.root";
	TString input_histogram_name = "pi_pi_hist;1";

	TFile * input_file = new TFile(input_file_name, "read");
	TH2D * input_histogram = (TH2D *) input_file->Get(input_histogram_name);
	TCanvas * canvas = new TCanvas("Canvas", "Histogram", 0, 0, 1600, 900);
	canvas->Divide(2,2);
	
	// Plot original histogram
	input_histogram->SetTitle("2D histogram of energy distribution of #pi^{+} and #pi^{-}");
	input_histogram->GetXaxis()->SetTitle("Energy of #pi^{+}");
	input_histogram->GetYaxis()->SetTitle("Energy of #pi^{-}");
	canvas->cd(1);
	input_histogram->Draw("COL");
	
	// Get x projection and plot it
	TH1D * projection_x = input_histogram->ProjectionX("Projection X", 1, -1);
	projection_x->SetTitle("X projection of 2D histogram");
	projection_x->GetXaxis()->SetTitle("Energy in [MeV]");
	projection_x->GetYaxis()->SetTitle("Number of entries");
	
	canvas->cd(2);
	projection_x->Draw();

	// Get y projection and plot it
	TH1D * projection_y = input_histogram->ProjectionY("Projection Y", 1, -1);
	projection_y->SetTitle("Y projection of 2D histogram");
	projection_y->GetXaxis()->SetTitle("Energy in [MeV]");
	projection_y->GetYaxis()->SetTitle("Number of entries");

	canvas->cd(3);
	projection_y->Draw();

	// Save figure
	TImage * image = TImage::Create();
	image->FromPad(canvas);
	image->WriteImage("canvas.png");

	// New canvas for slices
	TCanvas * canvas2 = new TCanvas("Canvas2", "Histogram", 0, 0, 1600, 900);
	canvas2->Divide(2, 2);

	// First slicing and plotting
	int xbin = 50;
	TH1D * slice_1 = input_histogram->ProjectionX("Slice at bin 50", xbin, xbin);
	slice_1->SetTitle("Y projection of 2D histogram");
	slice_1->GetXaxis()->SetTitle("Energy in [MeV]");
	slice_1->GetYaxis()->SetTitle("Number of entries");
	slice_1->SetFillColor(kGreen);

	canvas2->cd(1);
	slice_1->Draw();

	// Second slicing and plotting
	xbin = 70;
	TH1D * slice_2 = input_histogram->ProjectionX("Slice at bin 70", xbin, xbin);
	slice_2->SetTitle("Y projection of 2D histogram");
	slice_2->GetXaxis()->SetTitle("Energy in [MeV]");
	slice_2->GetYaxis()->SetTitle("Number of entries");
	slice_2->SetFillColor(kRed);

	canvas2->cd(2);
	slice_2->Draw();

	// Plot both slices in one histogram and add a legend
	canvas2->cd(3);
	TLegend * legend = new TLegend(0.1, 0.7, 0.3, 0.9);
	legend->SetHeader("Legend");
  legend->AddEntry(slice_1,"bin number 50","f");
  legend->AddEntry(slice_2,"bin number 70","f");

	slice_1->Draw();
	slice_2->Draw("same");
	legend->Draw("same");


	// Save figure
	TImage * image2 = TImage::Create();
	image2->FromPad(canvas2);
	image2->WriteImage("canvas2.png");

	// delete dynamic objects
	input_file->Close();
	delete input_file;
	delete canvas;
	delete canvas2;
	delete legend;

	return;
}


void exercise2_3(){

	Histogram();
	return;
}