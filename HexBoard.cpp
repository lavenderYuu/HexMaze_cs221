#include "HexBoard.h"

#include <iostream>

#include "queue.h"
#include "stack.h"

HexBoard::HexBoard(int radius) {
    this -> radius = radius;
    // int longest_path_dist = 0;
    this->longest_path_dist = 0;
    create_board();
    configure_cells();
}

void HexBoard::create_board() {
    /**
     * @todo Your code here!
     */
    HexCell start =  HexCell(0,0);
    // cells[{0,0}] = start;

    int size = radius -1;

    for(int q = -size; q <= size; q++) {
        for(int r = -size; r <= size; r++) {
            HexCell* new_cell = new HexCell(q,r);
            if(start.distance(new_cell) <= size){
                cells[{q,r}] = new_cell;
             }else{
                delete new_cell;
             }
        }
    }
}

void HexBoard::configure_cells() {

for (auto kv : cells) {               
    pair<int, int> coord = kv.first;
    int q = coord.first;
    int r = coord.second;

    HexCell* cell = kv.second;
    

    if (cells.find({q, r-1} )!= cells.end())
        cell -> neighbours[0] = cells[{q, r-1}];
    if (cells.find({q, r+1}) != cells.end())
        cell -> neighbours[3] = cells[{q, r+1}];

    if (cells.find({q+1, r-1}) != cells.end())
        cell -> neighbours[1] = cells[{q+1, r-1}];
    if (cells.find({q+1, r}) != cells.end())
        cell -> neighbours[2] = cells[{q+1, r}];

    if (cells.find({q-1, r+1}) != cells.end())
        cell -> neighbours[4] = cells[{q-1, r+1}];
    if (cells.find({q-1, r}) != cells.end())
        cell -> neighbours[5] = cells[{q-1, r}];
    //if not exist will return null?
}



}

void HexBoard::generate_maze(pair<int, int> start_coord, double branch_prob) {
    /**
     * @todo Your code here!
     */
    Stack<HexCell*> cell_stack; //do we need to initialize the stack
    map<pair<int, int>, bool> visited;

    int longestToEdge = 0;
    // int longest_path_dist = 0;
    this->start_coord = start_coord;

    cell_stack.push(cells[start_coord]);
    visited[start_coord] = true;

    while (!cell_stack.isEmpty())
    {
       HexCell* curr_cell = cell_stack.peek(); 
       HexCell* neigh_cell = chooseNeighbour(curr_cell, visited, branch_prob);

       if(neigh_cell) {
        curr_cell->link(neigh_cell);
        visited[{neigh_cell->q, neigh_cell->r}] = true;
        
        neigh_cell->path_dist_from_start = curr_cell->path_dist_from_start +1;

        if(neigh_cell->path_dist_from_start > longest_path_dist) {
            this->longest_path_dist = neigh_cell->path_dist_from_start;
        }

        // longestToEdge++;
        //Update the end coordinate only if its path distance to start is strictly greater
        if(neigh_cell->path_dist_from_start > longestToEdge && neigh_cell->is_edge()) {
            end_coord = {neigh_cell->q, neigh_cell->r};
            longestToEdge = neigh_cell->path_dist_from_start;
        }

        cell_stack.push(neigh_cell);
       } else {
        cell_stack.pop();
       }
    }
        


}

void HexBoard::solve_maze() {
    /**
     * @todo Your code here!
     */
    pair<int,int> linked_neib;
    vector<pair<int, int>> neibs=get_neigh_coords(start_coord);
    HexCell* nowcell=cells[end_coord];
    solution.push_back(end_coord);
    
    HexCell* startcell=cells[start_coord];
    int dist=nowcell->path_dist_from_start;
    while (dist>0)
    {   dist--;
        for(int i=0;i<6;i++){
        HexCell* toCheck=nowcell->neighbours[i];
        if(toCheck && nowcell->is_linked(toCheck)&&toCheck->path_dist_from_start==dist)
        {   nowcell=toCheck;
            linked_neib=pair<int,int>{toCheck->q,toCheck->r};
            solution.insert(solution.begin(),linked_neib);
            break;
        }
      }
    }
}


