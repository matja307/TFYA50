#ifndef CELL_LIST_H
#define CELL_LIST_H


#include <vector>

#include "cell.h"

class Cell_list{
private:
	float cutoff;
	float cell_length;

	std::vector<Cell*> list_of_cells;
	void clear_cells();
	void create_cell();

public:

	Cell_list(float cutoff); //Creates all cells 
	~Cell_list();
	void add_atoms_to_cells(std::vector<Atom*>);
	std::vector<Atom*> get_neighbours(Atom* atom); //Returns vector of atoms in nearest cells, with respect to paramteter atom.
};

#endif