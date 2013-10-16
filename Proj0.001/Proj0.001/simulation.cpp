#include "simulation.h"
#include "cell_list.h"

void Simulation::run_simulation(){
	//Loop through next_time_step


}
Simulation::Simulation (int number_of_atoms,int time_step,int steps,float temperature,float cutoff,float mass,float sigma,float epsilon,float lattice_constant,std::string crystal_structure,bool thermostat){
	// Create a simulation object. Initialize cell_list, list of atoms.
	create_list_of_atoms();
	create_cell_list();
	
}
Simulation::~Simulation (){

}
void Simulation::create_list_of_atoms(){
	//Create all atoms in this class? Convert from fcc to atom positions.

}
void Simulation::next_time_step(){
	//Alter everything in the simulation to get to the next time step.



}
void Simulation::regulate_thermostat(){
	//Regulate the kinetic energy so that the temperature remains "constant"


}
void save(){
	//Save ??? to a .txt file with some structure.

}
	
void create_cell_list(){
	cell_list = new Cell_list(0.5);
		
		//Cell_list(cutoff);


}