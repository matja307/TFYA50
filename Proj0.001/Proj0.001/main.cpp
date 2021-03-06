#include "simulation.h"
//#include "simulation2.h"
#include <iostream>
#include "vec.h"
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "GraphicsTestProject.h"
/*
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
*/
using namespace std;
	//initialvalues for get_input_file()
	string atom;
	string structure;
	float sigma;
	float epsilon;
	float mass;
	float lattice;
	string file = "data.txt";

void get_input_file(string intresting,string file){
istringstream iss;
string line;
ifstream in(file);
while(getline(in,line)){
	istringstream iss(line);
	iss>>atom>>sigma>>epsilon>>structure>>mass>>lattice;
	if(atom==intresting){
	break;
		}
	}
in.close();
}


int main(int argc, char** argv){
    
/*
Parameters:
	int unit_cells_x				: Number of unit cells in x-direction
	int unit_cells_y				: Number of unit cells in y-direction
	int unit_cells_z				: Number of unit cells in x-direction
	float time_step					: Length of one time step
	int steps						: number of time steps for the simulation
    float temperature				: Simulation temperature
    float cutoff					: Cutoff distance for potential calculations
    float mass						: Mass of an atom
    float sigma						: Material constant sigma LJ-potential
    float epsilon					: Material constan epsilon
    float lattice_constant			: Lattice constant
    std::string crystal_structure	: Name of chrystal structure (scc, fcc, hcp, bcc...)
    bool thermostat					: If a thermostat is employed
	bool old_sim					: Start from an old simulation?
 */

	//initializegraphics
	float a = 0.2f; // Watch out for double warning!
	
	int input_x;
	int input_y;
	int input_z;
	float input_time_step;
	int input_steps;
	float input_temperature = a;
	float input_cutoff;
	float input_mass = a;
	float input_sigma = a;
	float input_epsilon = a;
	float input_lattice_constant = a;
	string input_crystal_structure = "fcc";
	string input_material;
	bool input_thermostat = false;
	bool input_equilibrium = false;
	bool pbc_z = false;
	float thermostat_update_freq = 0;
	float input_lattice_scaling = 1;
	bool old_sim;
	bool save_atom_positions = false;
	
	cout << "Do you want to start from an old simulation? (Yes = 1/No = 0)" <<endl;
	cin >> old_sim;
	// cout << "Input filename.txt where old simulation can be found" <<endl;
	// cin >> old_sim_filename:
	
	if(!old_sim){
		cout << "Input the number of unit cells in x,y and z direction:" <<endl;
		cin >> input_x;
		cin >> input_y;
		cin >> input_z;
		cout << "Choose (Yes = 1/No = 0) for periodic boundry condition in z"<<endl;
		cin >> pbc_z;
		cout << "Input the wanted time step size:" << endl; 
		cin >> input_time_step;
		cout << "Input the wanted number of steps:" << endl;
		cin >> input_steps;
		cout << "Input wanted material:" << endl;
		cin >> input_material;
		get_input_file(input_material,file);
		cout << "Start temperature (K):" << endl;
		cin >> input_temperature;
		cout << "Scaling of lattice constant " << endl;
		cin >> input_lattice_scaling;
		cout << "Input cutoff multiples of lattice_constant:" <<endl;
		cin >> input_cutoff;
		input_cutoff = input_cutoff*lattice;
		cout << "Simulate with thermostat? (Yes = 1/No = 0)" << endl;
		cin >> input_thermostat;
		if(input_thermostat) {
			cout << "Update frequency for thermostat " << endl;
			cin >> thermostat_update_freq;
		}
		cout << "Do you want to save atom positions? (Yes = 1/No = 0)" << endl;
		cin >> save_atom_positions;
	}
	else{
		ifstream in("endofsimulation.txt");
		int line_number = 0;
		string line;
		getline(in,line);

		istringstream iss(line);
		iss>>input_x >> input_y >> input_z >> input_time_step >> input_steps >> input_temperature >> input_cutoff >> 
			input_mass >> input_sigma >> input_epsilon >> input_lattice_constant >> input_crystal_structure >> 
			input_thermostat >>  input_equilibrium >>  pbc_z >>  thermostat_update_freq >>  save_atom_positions;
	
		in.close();
	}

	cout << endl << "------------" << endl;
	cout << "- RUNNING -" << endl;
	cout << "------------" << endl << endl;
	
	if(!old_sim){
		input_sigma = sigma; //[�]
		input_epsilon = epsilon; //[eV]
		input_crystal_structure = structure;
		input_mass = mass; //[eV/c^2]=[eV][�]^2[fs]^-2
		input_lattice_constant=lattice*input_lattice_scaling;
	}

	cout << "Sigma: "<< input_sigma << endl;
	cout << "Epsilon: "<< input_epsilon<<endl;
	cout << "Structure: "<< input_crystal_structure<<endl;
	cout << "Mass: "<< input_mass<<endl;
	cout << "Lattice: "<< input_lattice_constant<<endl;

	clock_t t1 = clock();
	//Create first simulation world
	Simulation* simulation = new Simulation(input_x,input_y,input_z,input_time_step,input_steps,input_temperature, input_cutoff, 
											input_mass, input_sigma, input_epsilon, input_lattice_constant,input_crystal_structure,
											input_thermostat, input_equilibrium, pbc_z, thermostat_update_freq, old_sim, save_atom_positions);
	cout << "Running simulation..." << endl << endl;
	
	simulation->run_simulation();

	clock_t t2 = clock();
	//Run back to back simulation
	//Always with most recent simulation as it is now
	//btb = back to back

	bool back_to_back = true;
	cout << "Do you wish to run a new simulation back to back? (Yes = 1/No = 0)" << endl;
	cin >> back_to_back;
	if(!back_to_back){
		simulation->end_of_simulation();
	}

	float time = 0;
	while (back_to_back){
		cout << "System in equilibrium? (Yes = 1/No = 0)" << endl;
		cin >> input_equilibrium;
		cout << "Input the wanted number of steps:" << endl;
		cin >> input_steps;
		cout << "Starting new simulation back to back with previous!" << endl;
		clock_t t3 = clock();
		//Create new simulation
		Simulation* btb_simulation = new Simulation(simulation, input_steps, input_equilibrium);
		simulation = btb_simulation;
		cout << "Running simulation..." << endl << endl;
		simulation->run_simulation();
		clock_t t4 = clock();

		//Ask again to runt new btb simulation
		cout << "Do you wish to run a new simulation back to back? (Yes = 1/No = 0)" << endl;
		cin >> back_to_back;
		
		time += t4 - t3;
		if(!back_to_back){
			btb_simulation->end_of_simulation();
		}
	}

	cout << "Running time " << (t2 - t1) + time << endl;
	system("pause");
	//simulation->~Simulation (); Inte riktigt testad...
	
	return 0;
}



