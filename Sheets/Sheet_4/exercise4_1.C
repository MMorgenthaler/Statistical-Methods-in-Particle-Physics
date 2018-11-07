#import "TRandom3.h"
#import "TH1D.h"
#import "TCanvas.h"
#import "TImage.h"

#import <iostream>
#import <vector>

std::vector<double> BBS(long p, long q, long seed, unsigned total){
	long M = p*q;
	std::vector<long> random;
	std::vector<double> random2;
	
	long n1 = (seed * seed) % M;
	random.push_back(n1);
	random2.push_back(static_cast<double>(n1/M));

	for(unsigned i = 1; i < total; i++){
		random.push_back((random.at(i-1) * random.at(i-1)) % M);
		random2.push_back(static_cast<double>(random.at(i) / static_cast<double>(M)));
	}

	return random2;
}

void exercise4_1(){

	long seed = 234509143;
	long p = 33617;
	long q = 5011;
	unsigned total_seeds = 20;
	unsigned total_numbers = 10000;

	std::vector<long> seeds;
	std::vector<std::vector<double>> random_numbers;
	std::vector<double> many = BBS(p, q, seed, total_numbers);

	for(unsigned i = 0; i < total_seeds; i++){
		seeds.push_back(seed + i);
		std::vector<double> result = BBS(p, q, seeds.at(i), total_seeds);
		random_numbers.push_back(result);
		std::cout << " --- Random number " << i << " \t is " << (random_numbers.at(i)).back() << std::endl;
	}
	
	TH1D * hist = new TH1D("Random number distributions", "Random number distributions", 200, 0, 1);
	for(unsigned i = 0; i < total_numbers; i++){
		hist->Fill(many.at(i));
	}
	
	TCanvas * canvas = new TCanvas("canvas", "canvas", 10, 10, 900, 600);
	hist->GetXaxis()->SetTitle("Value between 0 and 1");
	hist->GetYaxis()->SetTitle("Amount of random numbers");
	hist->Draw();

	TImage * image = TImage::Create();
	image->FromPad(canvas);
	image->WriteImage("canvas.png");

	return;
}
