#include <TH1F.h>
#include <iostream>
#include <fstream>
#include <TCanvas.h>
#include <TApplication.h>
#include <TGraph.h>
#include <vector>

void CreateHistogram(std::string filename){
int nbinsx=100;
double startx = 0.;
double endx = 250.;
TApplication *fApp = new TApplication("Test", NULL, NULL);
TCanvas *c = new TCanvas("TestCanvas", "Energy Histogram", 800, 600);
c->Divide(3,2);
c->cd(1);
TH1F *energyHist = new TH1F("EnergyHistogram","EnergyHistogram",nbinsx,startx,endx);
std::ifstream infile(filename);
std::vector<double> x, y;

//For initial diversion histogram
startx = 0.;
endx = 10.;
nbinsx = 100;
TH1F *diversionHist = new TH1F("Initial Diversino Histogram","Initial Diversino Histogram",nbinsx,startx,endx);

double energy=0., xval=0., yval=0., initialDiversionAngle, initialRad;
while(!infile.eof()){
   infile >> energy >> xval >> yval >> initialDiversionAngle >> initialRad;
   energyHist->Fill(energy);
   diversionHist->Fill(initialDiversionAngle*1000.);
   x.push_back(xval);
   y.push_back(yval);
}
std::cout<<"Energy Histogram read done..." << std::endl;
energyHist->Draw();



//Making graph
c->cd(2);
TGraph *gr = new TGraph(x.size(),&x[0],&y[0]);
gr->SetTitle("Electron Beam Cone Base");
gr->GetXaxis()->SetTitle("X Coordinate");
gr->GetYaxis()->SetTitle("Y Coordinate");
gr->Draw("AP");


//Making histogram for initial diversion
c->cd(3);
diversionHist->Draw();

//Plotting final exit locations
x.clear();y.clear();
std::ifstream exitfile("exitPoints.txt");
double exX(0.),exY(0.),exDiv(0.),exRad(0.);
while(!exitfile.eof()){
  exitfile >> exX >> exY >> exDiv >> exRad;
  x.push_back(exX);
  y.push_back(exY);
}
std::cout<<"ExitPoints.txt reading done...... Size of Exit points : " << x.size() << std::endl;
c->cd(4);
TGraph *grExit = new TGraph(x.size(),&x[0],&y[0]);
grExit->SetTitle("Exit Hit Points");
grExit->GetXaxis()->SetTitle("X Coordinate");
grExit->GetYaxis()->SetTitle("Y Coordinate");
grExit->Draw("AP");
exitfile.close();


std::vector<double> x1,y1;
std::ifstream finalExitfile("finalexitPoints.txt");
double exX1(0.),exY1(0.),exDiv1(0.),exRad1(0.),z(0.);

while(!finalExitfile.eof()){
  finalExitfile >> exX1 >> exY1 >> z >> exDiv1 >> exRad1;
  x1.push_back(exX1);
  y1.push_back(exY1);
} 

std::cout<<"FinalExitPoints.txt reading done...... Size of Final Exit points : " << x1.size() << std::endl;

finalExitfile.close();
c->cd(5);
{
TGraph *grExit = new TGraph(x1.size(),&x1[0],&y1[0]);
grExit->SetTitle("Final Exit Hit Points");
grExit->GetXaxis()->SetTitle("X Coordinate");
grExit->GetYaxis()->SetTitle("Y Coordinate");
grExit->Draw("AP");
}

fApp->Run();

}


