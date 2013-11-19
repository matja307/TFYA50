#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <map>
#include <list>
#include <string>
#include <iostream>
#include <fstream>

#include "atom.h"
#include "cell_list.h"
#include "cell_list.h"
#include "vec.h"

class Simulation{
private:
	//Variables
	std::vector<Atom*> list_of_atoms;
	int number_of_atoms;
	float time_step; //Given in femtoseconds
	int steps;
	float temperature;
	float pressure;
	float cutoff;
	bool thermostat;
	bool equilibrium;
	bool pbc_z;
	float initial_velocity_modulus;
	int unit_cells_x;
	int unit_cells_y;
	int unit_cells_z;
	float volume;
	float total_energy;
	map<int, vector<Vec>> atom_positions;
	map<string, vector<Vec>> last_state;

	//Boltzmann constant
	float k_b;
	//Planck's constant
	float hbar;



	//Material
	float mass;
	float sigma;
	float epsilon;
	float lattice_constant;
	std::string crystal_structure; //bcc,fcc,hcp

	Cell_list* cell_list; 

	//Methods
	void create_cell_list();
	int calculate_number_of_atoms();
	
	

public:
	//Methods
	void create_list_of_atoms(); //Create all atoms in this class? Convert from fcc to atom positions.
	bool check_input();
	void next_time_step(int current_time_step, bool second_to_last_time_step, bool next_to_last_time_step, bool last_time_step); //Alter everything in the simulation to get to the next time step.
	float calculate_specific_heat();
	float calculate_MSD(Atom*);
	void regulate_thermostat(); //Regulate the kinetic energy so that the temperature remains "constant"
	void update_atoms_btb(); //If back to back simulation, update atoms to be in correct state
	void update_last_state(Atom*, bool, bool, bool); //Save data for btb simulation
	map<string, vector<Vec>> run_simulation(); //Loop through next_time_step and return last state
	void save(); //Save ??? to a .txt file with some structure.
	void update_atoms(); // Run through list_of_atoms and .update_atom
	void scc_structure();
	void scc_structure_x(int,int);
	void scc_corrector();
	void fcc_structure();
	void fcc_structure_x(int,int);
	void fcc_corrector();
	void bcc_structure();
	void bcc_structure_x(int,int);
	void bcc_corrector();
	std::vector<Atom*> get_list_of_atoms();
	int get_number_of_atoms();

	//Constructors
	//std::ofstream fs2;
	Simulation (int unit_cells_x,
		int unit_cells_y, // unit_cells is a material parameter.
		int unit_cells_z,
		float time_step,
		int steps,
		float temperature,
		float cutoff,
		float mass,
		float sigma,
		float epsilon,
		float lattice_constant,
		std::string crystal_structure,
		bool thermostat,
		bool equilibrium,
		map<string, vector<Vec>> new_last_state,
		bool pbc_z);
	Simulation(Simulation* old_simulation); //Take off where we left off-constructor

	//Destructor
	~Simulation();

	//Getters
	float get_time_step();
	int get_steps();
	float get_temperature();
	float get_cutoff();
	bool get_thermostat();
	bool get_pbc_z();
	float get_initial_velocity_modulus();
	int get_unit_cells_x();
	int get_unit_cells_y();
	int get_unit_cells_z();
	float get_total_energy();
	float get_mass();
	float get_sigma();
	float get_epsilon();
	float get_lattice_constant();
	std::string get_crystal_structure();
	Cell_list* get_cell_list(); 
	
	// abort simulation button?
	// handle end of simulation?
};
#endif
