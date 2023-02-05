#include "CLI11.hpp"  // CLI11 command line interface stuff (V2.3.1). See https://github.com/CLIUtils/CLI11
#include <iostream>
#include <fstream>
#include <random>
#include <string>

typedef std::mt19937 RandomNumberGenerator;

std::string Region(double x1, double x2, double dxmin){

// Compute pre-smearing region identifying string.

    std::string region;
    if(x1 >= 1.0-dxmin && x2 >= 1.0-dxmin){
        region = "PEAK";
    }
    else if(x1 < 1.0-dxmin && x2 >= 1.0-dxmin){
        region = "ARM1";                        // Maybe call ARME?
    }
    else if(x1 >= 1.0-dxmin && x2 < 1.0-dxmin){
        region = "ARM2";                        // Maybe call ARMP?
    }    
    else{
        region = "BODY";
    }
      
    return region;
}

void Smear(std::string inFile, std::string outFile, unsigned long int seed, double dxmin, 
           double ebeam, double dmu1, double dmu2, double sigma1, double sigma2){
          
    const double EPS = 5.961e-8;     
           
    RandomNumberGenerator geng(seed);
    std::normal_distribution<double> gaussian(0.0, 1.0);  // Make sure this is standardized

    std::ifstream fin;
    fin.open(inFile);

    std::ofstream fout;
    fout.open(outFile);
    fout.precision(10);
    
    double E1, E2, x1, x2, x1p, x2p;
  
    int nevs = 0;  
 // Read in energies from Guinea-PIG files. These are 32-bit floating point 
 // numbers written out with the least significant digit being 1 keV.
    while (fin >> E1 >> E2){
        nevs++;
        x1 = E1/ebeam;
        x2 = E2/ebeam;
 // Round 32-bit FP numbers that differ from 1 by less than 32-bit machine precision to 1.0       
        if(x1 < 1.0 && x1 > 1.0 - EPS) x1 = 1.0;
        if(x2 < 1.0 && x2 > 1.0 - EPS) x2 = 1.0;        
        
 // Use pre-smearing scaled energies to identify "region".
        std::string region = Region(x1, x2, dxmin);
        
 // Smear electron and positron energies       
        x1p = x1 + sigma1*gaussian(geng);
        x2p = x2 + sigma2*gaussian(geng);
        
        fout << region << " " << ebeam*x1p << " " << ebeam*x2p << std::endl;       
    }
        
    fin.close();
    fout.close();
    
    std::cout << nevs << " Events processed " << std::endl;
           
}

int main(int argc, char **argv) {

    CLI::App app{"Smear beam energies read from GP file"};
    
    unsigned long int seed = 12345;
    app.add_option("-s,--seed", seed, "Seed for random number generator");
    
    double dxmin = 2.0e-6;
    app.add_option("-d,--dxmin", dxmin, "Cutoff parameter");
    
    double ebeam = 125.0;
    app.add_option("-e,--ebeam", ebeam, "Beam energy (GeV)");    

    double dmu1 = 0.0;
    app.add_option("--dmu1", dmu1, "Electron energy scale deviation (ppm)"); 
    
    double dmu2 = 0.0;
    app.add_option("--dmu2", dmu2, "Positron energy scale deviation (ppm)");  

    double sigma1 = 0.190e-2;
    app.add_option("--sigma1", sigma1, "Electron beam energy spread fraction"); 
    
    double sigma2 = 0.152e-2;
    app.add_option("--sigma2", sigma2, "Positron beam energy spread fraction");
    
    std::string inputFilename = "GP-4X5X.ee";
    app.add_option("-i,--inputfile", inputFilename, "Input file"); 
    
    std::string outputFilename = "GP-4X5X-V3.eedat";
    app.add_option("-o,--outputfile", outputFilename, "Output file");         

    CLI11_PARSE(app, argc, argv);

    std::cout << "seed       " << seed << std::endl;
    std::cout << "dxmin      " << dxmin << std::endl;
    std::cout << "ebeam      " << ebeam << std::endl;
    std::cout << "dmu1       " << dmu1 << std::endl;
    std::cout << "dmu2       " << dmu2 << std::endl;     
    std::cout << "sigma1     " << sigma1 << std::endl;
    std::cout << "sigma2     " << sigma2 << std::endl;
    std::cout << "inputfile  " << inputFilename << std::endl;
    std::cout << "outputfile " << outputFilename << std::endl;        
 
    Smear(inputFilename, outputFilename, seed, dxmin, ebeam, dmu1, dmu2, sigma1, sigma2);
       
    return 0;
    
}
