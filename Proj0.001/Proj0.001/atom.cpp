#include "atom.h"
#include "vec.h"

using namespace std;

/*---------------------
CONSTRUCTOR
Parameters: Vec starting_position
Sets starting position
----------------------*/
Atom::Atom(Vec starting_position, float start_cutoff, float unit_cells_x, float unit_cells_y, float unit_cells_z, float sigma){

	position = starting_position;
	cutoff=start_cutoff;
	bulk_length_x = unit_cells_x*sigma;
	bulk_length_y = unit_cells_y*sigma;
	bulk_length_z = unit_cells_z*sigma;
}

/*--------------------
DESTRUCTOR
Does nothing
---------------------*/
Atom::~Atom(){}

/*----------------------
FUNCTION: calculate_force
Paramteters: vector<Atom*>
Returns: Vec (force vector)
-
Calculates force on the atom
from all neighbouring atoms 
within cutoff.
----------------------*/
Vec Atom::calculate_force(vector<Atom*> neighbouring_atoms){ //Untested!!!!!!

    /*
	Vec tmp_force (0,0,0);
	for(int i=1; i<=neighbouring_atoms.size();i++)
	{
	float r2=(distance_vector(neighbouring_atoms[i]).length());
	r2=pow(r2,-2);
	float r6=pow(r2,3);
	tmp_force+=-1*48*r2*r6*(1*r2-0.5)*distance_vector(neighbouring_atoms[i]).normalize();
	}
	return tmp_force;
     */
    return Vec(0,0,0);
}
	

/*----------------------
FUNCTION: calculate_potential
Parameters: vector<Atom*>
Returns: float (scalar potential)
-
Calculates (LJ) potential on 
the atom, from all neighbouring
atoms within cutoff.
----------------------*/
float Atom::calculate_potential(vector<Atom*> neighbouring_atoms){

	return 0.5;
}
	
/*----------------------
FUNCTION:distance_vector
Parameters: Atom*
Returns: Vec (vector between atoms)
-
Returns a Vec (vector) which is the 
cartesian vector between the atom
and the parameter atom.
----------------------*/
Vec Atom::distance_vector(Atom* other_atom){
	Vec tmp =other_atom->position;

	/* Check the x, y and z coordinate for both atoms */
	float x1 = position.getX();
	float x2 = tmp.getX();
	float y1 = position.getY();
	float y2 = tmp.getY();
	float z1 = position.getZ();
	float z2 = tmp.getZ();

	/* Check distance inside this periodic bulk structure*/
	Vec l1 = tmp - position;

	/* Check distance to atom in neighbouring periodic bulk structures, only checking the 7 closest */

	Vec l2;
	Vec l3;
	Vec l4;
	Vec l5;
	Vec l6;
	Vec l7;
	Vec l8;
	
	if(x1>=x2 && y1>=y2 && z1>=z2){
		/* Check x + bulk_length, y + bulk_length, z + bulk_length and all combinations */
		l2 = (tmp + Vec(bulk_length_x,0,0)) - position;
		l3 = (tmp + Vec(bulk_length_x,bulk_length_y,0)) - position;
		l4 = (tmp + Vec(bulk_length_x,0,bulk_length_z)) - position;
		l5 = (tmp + Vec(bulk_length_x,bulk_length_y,bulk_length_z)) - position;
		l6 = (tmp + Vec(0,bulk_length_y,0)) - position;
		l7 = (tmp + Vec(0,bulk_length_y,bulk_length_z)) - position;
		l8 = (tmp + Vec(0,0,bulk_length_z)) - position;
	}
	else if(x1>=x2 && y1>=y2 && z1<=z2){
		/* Check x + bulk_length, y + bulk_length, z - bulk_length and all combinations */
		l2 = (tmp + Vec(bulk_length_x,0,0)) - position;
		l3 = (tmp + Vec(bulk_length_x,bulk_length_y,0)) - position;
		l4 = (tmp + Vec(bulk_length_x,0,-bulk_length_z)) - position;
		l5 = (tmp + Vec(bulk_length_x,bulk_length_y,-bulk_length_z)) - position;
		l6 = (tmp + Vec(0,bulk_length_y,0)) - position;
		l7 = (tmp + Vec(0,bulk_length_y,-bulk_length_z)) - position;
		l8 = (tmp + Vec(0,0,-bulk_length_z)) - position;
	}
	else if(x1>=x2 && y1<=y2 && z1>=z2){
		/* Check x + bulk_length, y - bulk_length, z + bulk_length and all combinations */
		l2 = (tmp + Vec(bulk_length_x,0,0)) - position;
		l3 = (tmp + Vec(bulk_length_x,-bulk_length_y,0)) - position;
		l4 = (tmp + Vec(bulk_length_x,0,bulk_length_z)) - position;
		l5 = (tmp + Vec(bulk_length_x,-bulk_length_y,bulk_length_z)) - position;
		l6 = (tmp + Vec(0,-bulk_length_y,0)) - position;
		l7 = (tmp + Vec(0,-bulk_length_y,bulk_length_z)) - position;
		l8 = (tmp + Vec(0,0,bulk_length_z)) - position;

	}
	else if(x1>=x2 && y1<=y2 && z1<=z2){
		/* Check x + bulk_length, y - bulk_length, z - bulk_length and all combinations */
		l2 = (tmp + Vec(bulk_length_x,0,0)) - position;
		l3 = (tmp + Vec(bulk_length_x,-bulk_length_y,0)) - position;
		l4 = (tmp + Vec(bulk_length_x,0,-bulk_length_z)) - position;
		l5 = (tmp + Vec(bulk_length_x,-bulk_length_y,-bulk_length_z)) - position;
		l6 = (tmp + Vec(0,-bulk_length_y,0)) - position;
		l7 = (tmp + Vec(0,-bulk_length_y,-bulk_length_z)) - position;
		l8 = (tmp + Vec(0,0,-bulk_length_z)) - position;
	}
	else if(x1<=x2 && y1>=y2 && z1>=z2){
		/* Check x - bulk_length, y + bulk_length, z + bulk_length and all combinations */
		l2 = (tmp + Vec(-bulk_length_x,0,0)) - position;
		l3 = (tmp + Vec(-bulk_length_x,bulk_length_y,0)) - position;
		l4 = (tmp + Vec(-bulk_length_x,0,bulk_length_z)) - position;
		l5 = (tmp + Vec(-bulk_length_x,bulk_length_y,bulk_length_z)) - position;
		l6 = (tmp + Vec(0,bulk_length_y,0)) - position;
		l7 = (tmp + Vec(0,bulk_length_y,bulk_length_z)) - position;
		l8 = (tmp + Vec(0,0,bulk_length_z)) - position;
	}
	else if(x1<=x2 && y1<=y2 && z1>=z2){
		/* Check x - bulk_length, y - bulk_length, z + bulk_length and all combinations */
		l2 = (tmp + Vec(-bulk_length_x,0,0)) - position;
		l3 = (tmp + Vec(-bulk_length_x,-bulk_length_y,0)) - position;
		l4 = (tmp + Vec(-bulk_length_x,0,bulk_length_z)) - position;
		l5 = (tmp + Vec(-bulk_length_x,-bulk_length_y,bulk_length_z)) - position;
		l6 = (tmp + Vec(0,-bulk_length_y,0)) - position;
		l7 = (tmp + Vec(0,-bulk_length_y,bulk_length_z)) - position;
		l8 = (tmp + Vec(0,0,bulk_length_z)) - position;
	}
	else if(x1<=x2 && y1>=y2 && z1<=z2){
		/* Check x - bulk_length, y + bulk_length, z - bulk_length and all combinations */
		l2 = (tmp + Vec(-bulk_length_x,0,0)) - position;
		l3 = (tmp + Vec(-bulk_length_x,bulk_length_y,0)) - position;
		l4 = (tmp + Vec(-bulk_length_x,0,-bulk_length_z)) - position;
		l5 = (tmp + Vec(-bulk_length_x,bulk_length_y,-bulk_length_z)) - position;
		l6 = (tmp + Vec(0,bulk_length_y,0)) - position;
		l7 = (tmp + Vec(0,bulk_length_y,-bulk_length_z)) - position;
		l8 = (tmp + Vec(0,0,-bulk_length_z)) - position;
	}
	else{
		/* Check x - bulk_length, y - bulk_length, z - bulk_length and all combinations */
		l2 = (tmp - Vec(bulk_length_x,0,0)) - position;
		l3 = (tmp - Vec(bulk_length_x,bulk_length_y,0)) - position;
		l4 = (tmp - Vec(bulk_length_x,0,bulk_length_z)) - position;
		l5 = (tmp - Vec(bulk_length_x,bulk_length_y,bulk_length_z)) - position;
		l6 = (tmp - Vec(0,bulk_length_y,0)) - position;
		l7 = (tmp - Vec(0,bulk_length_y,bulk_length_z)) - position;
		l8 = (tmp - Vec(0,0,bulk_length_z)) - position;
	}


	/* Check which one of the 8 atoms that are closest*/
	float shortest_distance = l1.length();
	Vec shortest_vec = l1;

	if(l2.length() < shortest_distance){
		shortest_distance = l2.length();
		shortest_vec = l2;
	}
	if(l3.length() < shortest_distance){
		shortest_distance = l3.length();
		shortest_vec = l3;
	}
	if(l4.length() < shortest_distance){
		shortest_distance = l4.length();
		shortest_vec = l4;
	}
	if(l5.length() < shortest_distance){
		shortest_distance = l5.length();
		shortest_vec = l5;
	}
	if(l6.length() < shortest_distance){
		shortest_distance = l6.length();
		shortest_vec = l6;
	}
	if(l7.length() < shortest_distance){
		shortest_distance = l7.length();
		shortest_vec = l7;
	}
	if(l8.length() < shortest_distance){
		shortest_distance = l8.length();
		shortest_vec = l8;
	}

	// Returns the vector to the closest atom
	cout << "Kortaste" << shortest_vec << endl;
	return shortest_vec;
}

/*-------------------------
FUNCTION: next_time_step()
Parameters: None
Returns: Nothing
-
Calculates the atom paramters
for the next time step
--------------------------*/
void Atom::next_time_step(){}

/*--------------------------
FUNCTION: update_atom
Parameters: None
Returns: Nothing
-
Changes the atom paramters
from the state at time t to
time t+1.
--------------------------*/
void Atom::update_atom(){
position = next_position;
velocity = next_velocity;
// Change the cell number? Should there be a call for that?
}


// ------- GETTERS --------
Vec Atom::get_velocity(){
	
	return velocity;
}

Vec Atom::get_position(){

	return position;
}

int Atom::get_cell_number(){

	return cell_number;
}


// -------- SETTERS --------
void Atom::set_velocity(Vec newVelocity){}
	
void Atom::set_position(Vec newPosition){}

void Atom::set_cell_number(int){}

void Atom::set_cutoff(float){}




