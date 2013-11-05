#ifndef ATOM_H 
#define ATOM_H

#include<vector>

#include "Vec.h"

class Atom{
private:
	Vec position;
	Vec velocity;
	Vec prev_position;
	Vec next_position;
	Vec next_velocity;
	int cell_number;
	int number_of_neighbours;
	float cutoff;
	float bulk_length_x;
	float bulk_length_y;
	float bulk_length_z;
	float sigma;
		

public:
	//Constructor
	Atom (Vec,float,float,float,float,float); 
	~Atom ();

	//Getters
	Vec get_velocity();
	Vec get_position();
	int get_cell_number();

	//Setters
	void set_velocity(Vec);
	void set_position(Vec);
	void set_cell_number(int);
	void set_cutoff(float);

	//Other functions
	Vec calculate_force(std::vector<Atom*>);
	float calculate_potential(Atom*);
	Vec distance_vector(Atom*); // Take care of periodic boundry conditions? done
	void next_time_step(); //Alter everything in the atom to get to the next time step.
	void update_atom();	
};

#endif