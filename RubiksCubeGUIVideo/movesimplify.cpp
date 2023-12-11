#include "movesimplify.h"

MoveSimplify::MoveSimplify()
{

}

vector<string> MoveSimplify::simplify(vector<string> input)
{
    vector<string> simplifiedMoves;

    for (int i = 0; i < input.size(); i++) {
        if (input[i].size() == 2 && input[i][1] == ' ') {
            input[i] = input[i][0];
        }
        if ((i<input.size()-1) && (input[i][0] == input[i+1][0])) { // check to see if the same type (face) move is applied twice
            string faceToMove(1, input[i][0]);
            if (input[i] == input[i+1]) { //inputs are the same
                if (input[i].find('2')) {} // L2 L2, don't do anything
                else { // L L or L' L'
                    faceToMove.push_back('2');
                    simplifiedMoves.push_back(faceToMove);
                }
            }
            else if ((input[i].size() > 1)) { //first string is L' or L2
                if (input[i][1] == '2') { //
                    if (input[i+1] == faceToMove) { // L2 L
                        simplifiedMoves.push_back(faceToMove+'\'');
                    }
                    else { // L2 L'
                        simplifiedMoves.push_back(faceToMove);
                    }
                }
                else { // L'
                    if (input[i+1].size() == 1) {}// L'L, don't do anything
                    else { // L' L2
                        simplifiedMoves.push_back(faceToMove);
                    }
                }
            }
            else { // L
                if (input[i+1][1] == '2') { //L L2
                    simplifiedMoves.push_back(faceToMove + '\'');
                }
                else {} // L L', don't do anything
            }
            i++;
        }
        else { // nothing to simplify
            simplifiedMoves.push_back(input[i]);
        }
    }

    solveMoves = simplifiedMoves;
    return solveMoves;
}


vector<string> MoveSimplify::getSolveMoves()
{
    return solveMoves;
}

string MoveSimplify::getSolveMovesString()
{
    string output = "";
    for (int i = 0; i < solveMoves.size(); i++) {
        output = output + solveMoves[i] + " ";

    }
    return output;
}

vector<CubeModel::MOVE> MoveSimplify::getSolveMovesCube(vector<string> input)
{
    vector<CubeModel::MOVE> output;
    vector<string> tempMoves;

    for (int i = 0; i < input.size(); i++) {
        output.push_back(convertToMove(input[i]));
        string move = input[i];
        if (move[1] == ' ') {
            move = move[0];
        }
        tempMoves.push_back(move);
    }
    solveMoves = tempMoves;
    return output;
}

CubeModel::MOVE MoveSimplify::convertToMove(string move)
{
    switch(move[0]) {
    case('F'):
        switch(move[1]) {
        case(' '):
            return CubeModel::MOVE::F;
        case('2'):
            return CubeModel::MOVE::F2;
        case('\''):
            return CubeModel::MOVE::FPRIME;
        }
    case('B'):
        switch(move[1]) {
        case(' '):
            return CubeModel::MOVE::B;
        case('2'):
            return CubeModel::MOVE::B2;
        case('\''):
            return CubeModel::MOVE::BPRIME;
        }
    case('U'):
        switch(move[1]) {
        case(' '):
            return CubeModel::MOVE::U;
        case('2'):
            return CubeModel::MOVE::U2;
        case('\''):
            return CubeModel::MOVE::UPRIME;
        }
    case('D'):
        switch(move[1]) {
        case(' '):
            return CubeModel::MOVE::D;
        case('2'):
            return CubeModel::MOVE::D2;
        case('\''):
            return CubeModel::MOVE::DPRIME;
        }
    case('L'):
        switch(move[1]) {
        case(' '):
            return CubeModel::MOVE::L;
        case('2'):
            return CubeModel::MOVE::L2;
        case('\''):
            return CubeModel::MOVE::LPRIME;
        }
    case('R'):
        switch(move[1]) {
        case(' '):
            return CubeModel::MOVE::R;
        case('2'):
            return CubeModel::MOVE::R2;
        case('\''):
            return CubeModel::MOVE::RPRIME;
        }
    }
    return CubeModel::MOVE::F;
}
