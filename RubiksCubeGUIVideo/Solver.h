#ifndef SOLVER_H
#define SOLVER_H

#include "CubeModel.h"

#include <iostream>
using std::cout;
#include <QDebug>
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <map>
using std::map;
#include <queue>
using std::queue;
#include <algorithm>
using std::swap;

class Solver
{
private:
    typedef vector<int> vi;
    int applicableMoves[5] = {0, 262143, 259263, 74943, 74898};
    int affectedCubies[6][8] = {
        {  0,  1,  2,  3,  0,  1,  2,  3 },   // U
        {  4,  7,  6,  5,  4,  5,  6,  7 },   // D
        {  0,  9,  4,  8,  0,  3,  5,  4 },   // F
        {  2, 10,  6, 11,  2,  1,  7,  6 },   // B
        {  3, 11,  7,  9,  3,  2,  6,  5 },   // L
        {  1,  8,  5, 10,  1,  0,  4,  7 },   // R
    };
    int phase;
    vector<string> solveMoves;

    vi applyMove(int move, vi state);
    int inverse(int move);
    vi id(vi state);

public:
    Solver();
    vector<string> getSolveMoves() const { return solveMoves; }
    void solve(vector<string> const &input);
};

#endif // SOLVER_H
