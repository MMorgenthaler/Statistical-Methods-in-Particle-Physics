#import <iostream>
#import "TMath.h"
using namespace std;

double exercise1_2(double nmb1=0., double nmb2=0., double nmb3=0.) {
  cout << "Enter 3 numbers" << endl;
  cout << "Enter first number: ";
  cin >> nmb1;
  cout << "Enter second number: ";
  cin >> nmb2;
  cout << "Enter third number: ";
  cin >> nmb3;

  vector<double> nmbrs = {nmb1, nmb2, nmb3};
  double mean = TMath::Mean(3, &nmbrs[0]);
  double median = TMath::Median(3, &nmbrs[0]);
  cout << "Arithmetic mean: " << mean << endl;
  cout << "Median: " << median;

return nmb1 + nmb2 + nmb3;
};

