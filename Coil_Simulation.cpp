#include<iostream>
using namespace std;
#include <cmath>
#include <limits>



class Coil {
private: 
double Capacitance;
double Inductance;
double Resistance;
int nTurns;
double amps; 
double frequency;

public:
    // Data members
Coil(double c, double l, double r, int turns, double i, double f){
    Capacitance = c;
    Inductance = l;
    Resistance = r; 
    nTurns = turns; 
    amps = i; 
    frequency = f;
}
double Xc(){
    double pi = 3.141592653589793;
    return (1 / (2 * pi * frequency * Capacitance));
}
double Xl(){
    double pi = 3.141592653589793;
    return (2 * pi * frequency * Inductance);
}
double z(){
    double capacativeReactance = Xc();
    double inductiveReactance = Xl();
    return sqrt(pow(Resistance,2) + pow(inductiveReactance - capacativeReactance, 2));
}
double Bfield_strength(){
    double pi = 3.141592653589793;
    double mu0 = 4 * pi * .0000001;
    double impedance = z();
    return (mu0 * nTurns * amps) / (2 * impedance);
}

    // Function to update the frequency
    void updateFrequency(double newFreq) {
        frequency = newFreq;
        
    }

};


int main() {
    double freq;
    // Physical Parameters 
    // double Frequency = 2500000;
    double Capacitance = 0;
    double Inductance = 0.;
    double Resistance = 0;
    int nTurns = 0;
    double amps = 0;

    // Sweep Parameters 
    double startFrequency = 5000.0;
    double const endFrequency = 25000000000000;
    double increment = 1.00;
    double lowestImpedance = std::numeric_limits<double>::infinity();
    double greatestTesla = std::numeric_limits<double>::infinity();
    double frequencyWithLowestImpedance = 0.0;
    double frequencyWithHighestTesla = 0.0;
    double magstrength; 


double Inductive_Reactance, Capacitive_Reactance, Impedance, Tesla;

Coil coil1(Capacitance, Inductance, Resistance, nTurns, amps, freq);
for(freq = startFrequency; freq < endFrequency; freq += increment){
    coil1.updateFrequency(freq);
    double impedanceValue = coil1.z(); 
    double tesla = coil1.Bfield_strength();
        if (impedanceValue < lowestImpedance) {
            lowestImpedance = impedanceValue;
            frequencyWithLowestImpedance = freq;
            magstrength = tesla;
        }

        // Check if the current values exceed the previous ones
        if (impedanceValue > lowestImpedance || tesla > greatestTesla) {
            break;  // Stop the sweep if the values exceed previous ones
        }
    
}  

cout << coil1.Bfield_strength(); 
cout << "" << endl; 
cout << fixed << "The total impedance is " << lowestImpedance << " ohms at frequency " << frequencyWithLowestImpedance << " Hz." << endl; 
cout << "" << endl;
cout << fixed << "The magnetic field strength of the coil is " << magstrength << " Tesla at frequency "  << frequencyWithLowestImpedance << " Hz." << endl; 
cout << "" << endl; 



    return 0;
}







