#ifndef MOVESIMPLIFY_H
#define MOVESIMPLIFY_H

#include <vector>
using std::vector;
#include <string>
using std::string;

#include "CubeModel.h"

class MoveSimplify
{
private:
    vector<string> solveMoves;
    CubeModel::MOVE convertToMove(string move);
public:
    MoveSimplify();
    vector<string> simplify(vector<string> input);
    vector<string> getSolveMoves();
    vector<CubeModel::MOVE> getSolveMovesCube(vector<string>);
    string getSolveMovesString();
};

#endif // MOVESIMPLIFY_H
