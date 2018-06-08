#include "MyPrimaryGeneratorAction.h"

#include "G4Box.hh"
#include "G4Electron.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4Proton.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <fstream>
#include <cmath>
MyPrimaryGeneratorAction::MyPrimaryGeneratorAction() {
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);
  fParticleGun->SetParticleDefinition(G4Electron::ElectronDefinition());

  
  fParticleGun->SetParticleEnergy(50. * keV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0. ));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
}
MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction() { delete fParticleGun; }

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event *event) {
   //fParticleGun->SetParticlePosition(G4ThreeVector(-50 * cm, 0., -120 * cm));
   //fParticleGun->GeneratePrimaryVertex(event);
  //std::ofstream outfile("energy.txt",std::ios::app);
//Source He 
// double mu=150*MeV;
 // double sigma=30*MeV;
 // G4double uGauss = G4RandGauss::shoot(mu,sigma);  
//Source Ar
 G4double uGauss = G4UniformRand()*60;
std::ofstream outfile("entryPoints.txt",std::ios::app);
  //Generating random direction
  G4double theta = G4UniformRand()*360;
//Source He  
double r = 0.05*cm;
//Source Ar
 // double r = 1*cm;
  r *= G4UniformRand();
  double x = r*std::cos(theta*M_PI/180.);
  double y = r*std::sin(theta*M_PI/180.);
  double z = 0;

  G4ThreeVector conePoint(x,y,z);
  

  fParticleGun->SetParticleEnergy(uGauss*MeV);

  G4ThreeVector gunPosition(0., 0., -10*cm);

  G4ThreeVector dir = conePoint - gunPosition;
  dir = dir.unit();
  fParticleGun->SetParticlePosition(G4ThreeVector(gunPosition));
  fParticleGun->SetParticleMomentumDirection(dir);

   double diversionAngle = dir.angle(G4ThreeVector(0.,0.,1.));
   //outfile << uGauss << "initial x " << x << "initial y " << y << "initial divergence " << diversionAngle <<" "<< " rin "<<std::sqrt(x*x+y*y) << std::endl;
   outfile << uGauss << " " << x << " " << y << " " << diversionAngle <<" "<< std::sqrt(x*x+y*y) << std::endl;
   outfile.close();

   //outfile.close();
  
  fParticleGun->GeneratePrimaryVertex(event);
  
  
}
