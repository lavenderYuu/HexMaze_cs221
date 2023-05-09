#include "HexCell.h"

#include <cmath>

HexCell::HexCell(int Q, int R) {
    q = Q;
    r = R;
    this->path_dist_from_start = 0;
    //add
    for(int i = 0; i<6; i++) {
        neighbours[i] = NULL;
        links[i] = NULL;
    }

}

void HexCell::link(HexCell* cell) {

    // HexCell* current = cell;
    if(is_linked(cell)) 
        return;

    
    if(cell && (distance(cell) == 1)) {
        int side = get_neighbour_side(cell);
        if(side == -1) return;
        links[side] = cell;
        cell->link(this);
    }
}

int HexCell::get_neighbour_side(const HexCell* cell) const {
    int cQ = cell -> q;
    int cR =  cell -> r;
    int i = 0;

    if(q == cQ & r-1==cR)
        return 0;

    if(q+1 == cQ & r-1==cR)
        return 1;

    if(q+1 == cQ & r==cR)
        return 2;
    
    if(q == cQ & r+1==cR)
        return 3;
    
    if(q-1 == cQ & r+1==cR)
        return 4;
    
    if(q-1 == cQ & r==cR)
        return 5;

    return -1;
}

bool HexCell::is_linked(const HexCell* cell) const {
    
    if (!cell) {
        return false;
    }
    
    for(int i = 0; i<6; i++) {
        if(links[i] == cell) {
            return true;
        }
    }

    return false;
}

int HexCell::distance(const HexCell* cell) const {
    
    if(!cell) {
        return -1;
    }

    int cQ = cell -> q;
    int cR = cell -> r;
    int rDis = abs(r-cR);
    int qDis = abs(q-cQ);
    int qAr = abs(q-cQ) + abs(r-cR);

    if(q == cQ) 
        return rDis;

    if(r == cR) 
        return qDis;
    

    if((cR+cQ) == (r+q)) 
        return rDis;
    
    return (abs(q-cQ+r-cR) + rDis + qDis)/2;
}

bool HexCell::is_edge() const {
    
    for(int i = 0; i< 6; i++) {
        if(!neighbours[i]) {
            return true;
        }
    }

    return false;
}