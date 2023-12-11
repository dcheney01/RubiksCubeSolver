#ifndef CUBEMODEL_H
#define CUBEMODEL_H

#include <string>
using std::string;
#include <array>
using std::array;
#include <vector>
using std::vector;

#include "CubeException.h"
#include "RandomGenerator.h"

/**
 * A CubeModelModel that is optimized for fast moves and pattern database
 * indexing.  It stores each cubie as an index and orientation, with edges
 * and corners in separate arrays.
 *
 * Note that the cube is oriented with orange on top and green up front
 *
 * Edge indexes.
 *
 * 0  1  2  3  4  5  6  7  8  9  10 11
 * UB UR UF UL FR FL BL BR DF DL DB DR
 * OB OW OG OY GW GY BY BW RG RY RB RW
 *
 *
 * Corner indexes.
 *
 * 0   1   2   3   4   5   6   7
 * ULB URB ULF URF DLB DRB DLF DRF
 * OYB OWB OYG OWG RYB RWB RYG RWG
 */


class CubeModel
{
public:
    enum class FACE   : uint8_t {UP, LEFT, FRONT, RIGHT, BACK, DOWN};
    enum class COLOR  : uint8_t {ORANGE, YELLOW, GREEN, WHITE, BLUE, RED};
    enum class EDGE   : uint8_t {UB, UR, UF, UL, FR, FL, BL, BR, DF, DL, DB, DR};
    enum class CORNER : uint8_t {ULB, URB, URF, ULF, DLF, DLB, DRB, DRF};
    enum class MOVE   : uint8_t
    {
        L, LPRIME, L2,
        R, RPRIME, R2,
        U, UPRIME, U2,
        D, DPRIME, D2,
        F, FPRIME, F2,
        B, BPRIME, B2,
    };

private:
    struct Cubie
    {
        uint8_t index;                    // 0 - 11 for edges, 0 - 7 for corners.
        uint8_t orientation;              // 0 - 1 for edges, 0 - 2 for corners.
    };

    array<Cubie, 12> edges;
    array<Cubie, 8>  corners;
    array<COLOR, 6>  centers;

    inline void updateCornerOrientationX(CORNER ind);
    inline void updateCornerOrientationZ(CORNER ind);
    inline void updateEdgeOrientationZ(EDGE ind);

    char getColor(COLOR color) const;
    array<int, 3> getCornerPosition(int index, int orientation) const;
    array<int, 2> getEdgePosition(int index, int orientation) const;

    array<COLOR, 2> getEdgeColors(EDGE ind) const;
    array<COLOR, 3> getCornerColors(CORNER ind) const;

public:
    CubeModel();
    string toString() const;
    vector<string> getSolverOutput() const;
    string getMove(MOVE ind) const;
    string reset();
    std::vector<string> scramble(int numMoves);

    COLOR getColor(FACE face, unsigned row, unsigned col) const;
    string getFaceColor(COLOR input) const;

    CubeModel& move(MOVE ind);

    // Face moves
    CubeModel& f();
    CubeModel& fPrime();
    CubeModel& f2();

    CubeModel& b();
    CubeModel& bPrime();
    CubeModel& b2();

    CubeModel& l();
    CubeModel& lPrime();
    CubeModel& l2();

    CubeModel& r();
    CubeModel& rPrime();
    CubeModel& r2();

    CubeModel& u();
    CubeModel& uPrime();
    CubeModel& u2();

    CubeModel& d();
    CubeModel& dPrime();
    CubeModel& d2();
};

#endif

