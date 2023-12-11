#include "CubeModel.h"

/**
* Initialize the cube with orange on the top and green up front.
*/
CubeModel::CubeModel()
{
    reset();
}

std::string CubeModel::reset()
{
    // Edges.
    for (unsigned i = 0; i < 12; ++i)
    {
        this->edges[i].index       = i;
        this->edges[i].orientation = 0;
    }

    // Corners.
    for (unsigned i = 0; i < 8; ++i)
    {
        this->corners[i].index       = i;
        this->corners[i].orientation = 0;
    }

    // Centers.
    this->centers[0] = COLOR::ORANGE;
    this->centers[1] = COLOR::YELLOW;
    this->centers[2] = COLOR::GREEN;
    this->centers[3] = COLOR::WHITE;
    this->centers[4] = COLOR::BLUE;
    this->centers[5] = COLOR::RED;

    return toString();
}

std::vector<std::string> CubeModel::scramble(int numMoves)
{
    RandomGenerator rand;
    std::vector<std::string> output;
    std::vector<int> moves = rand.getRand(numMoves);
    for (auto i : moves) {
        move(static_cast<MOVE>(i));
        output.push_back(getMove(static_cast<MOVE>(i)));
    }
    return output;
}

CubeModel& CubeModel::move(MOVE ind)
{
    switch (ind)
    {
    case MOVE::L:
        return this->l();
    case MOVE::LPRIME:
        return this->lPrime();
    case MOVE::L2:
        return this->l2();
    case MOVE::R:
        return this->r();
    case MOVE::RPRIME:
        return this->rPrime();
    case MOVE::R2:
        return this->r2();
    case MOVE::U:
        return this->u();
    case MOVE::UPRIME:
        return this->uPrime();
    case MOVE::U2:
        return this->u2();
    case MOVE::D:
        return this->d();
    case MOVE::DPRIME:
        return this->dPrime();
    case MOVE::D2:
        return this->d2();
    case MOVE::F:
        return this->f();
    case MOVE::FPRIME:
        return this->fPrime();
    case MOVE::F2:
        return this->f2();
    case MOVE::B:
        return this->b();
    case MOVE::BPRIME:
        return this->bPrime();
    case MOVE::B2:
        return this->b2();
    default:
        throw CubeException("Invalid face turn index. (MOVE)");
    };
}

std::string CubeModel::getFaceColor(COLOR input) const {
    switch (input) {
    case(COLOR::GREEN):
        return "F";
    case(COLOR::BLUE):
        return "B";
    case(COLOR::ORANGE):
        return "U";
    case(COLOR::RED):
        return "D";
    case(COLOR::WHITE):
        return "R";
    case(COLOR::YELLOW):
        return "L";
    }
    return "ERROR";
}

std::vector<std::string> CubeModel::getSolverOutput() const
{
    std::vector<std::string> output = std::vector<std::string> (20);
    //Edges
    output[0] = getFaceColor(getColor(FACE::UP, 2, 1)) + getFaceColor(getColor(FACE::FRONT, 0, 1));
    output[1] = getFaceColor(getColor(FACE::UP, 1, 2)) + getFaceColor(getColor(FACE::RIGHT, 0, 1));
    output[2] = getFaceColor(getColor(FACE::UP, 0, 1)) + getFaceColor(getColor(FACE::BACK, 0, 1));
    output[3] = getFaceColor(getColor(FACE::UP, 1, 0)) + getFaceColor(getColor(FACE::LEFT, 0, 1));
    output[4] = getFaceColor(getColor(FACE::DOWN, 0, 1)) + getFaceColor(getColor(FACE::FRONT, 2, 1));
    output[5] = getFaceColor(getColor(FACE::DOWN, 1, 2)) + getFaceColor(getColor(FACE::RIGHT, 2, 1));
    output[6] = getFaceColor(getColor(FACE::DOWN, 2, 1)) + getFaceColor(getColor(FACE::BACK, 2, 1));
    output[7] = getFaceColor(getColor(FACE::DOWN, 1, 0)) + getFaceColor(getColor(FACE::LEFT, 2, 1));
    output[8] = getFaceColor(getColor(FACE::FRONT, 1, 2)) + getFaceColor(getColor(FACE::RIGHT, 1, 0));
    output[9] = getFaceColor(getColor(FACE::FRONT, 1, 0)) + getFaceColor(getColor(FACE::LEFT, 1, 2));
    output[10] = getFaceColor(getColor(FACE::BACK, 1, 0)) + getFaceColor(getColor(FACE::RIGHT, 1, 2));
    output[11] = getFaceColor(getColor(FACE::BACK, 1, 2)) + getFaceColor(getColor(FACE::LEFT, 1, 0));
    //Corners
    output[12] = getFaceColor(getColor(FACE::UP, 2, 2)) + getFaceColor(getColor(FACE::FRONT, 0, 2)) + getFaceColor(getColor(FACE::RIGHT, 0, 0));
    output[13] = getFaceColor(getColor(FACE::UP, 0, 2)) + getFaceColor(getColor(FACE::RIGHT, 0, 2)) + getFaceColor(getColor(FACE::BACK, 0, 0));
    output[14] = getFaceColor(getColor(FACE::UP, 0, 0)) + getFaceColor(getColor(FACE::BACK, 0, 2)) + getFaceColor(getColor(FACE::LEFT, 0, 0));
    output[15] = getFaceColor(getColor(FACE::UP, 2, 0)) + getFaceColor(getColor(FACE::LEFT, 0, 2)) + getFaceColor(getColor(FACE::FRONT, 0, 0));
    output[16] = getFaceColor(getColor(FACE::DOWN, 0, 2)) + getFaceColor(getColor(FACE::RIGHT, 2, 0)) + getFaceColor(getColor(FACE::FRONT, 2, 2));
    output[17] = getFaceColor(getColor(FACE::DOWN, 0, 0)) + getFaceColor(getColor(FACE::FRONT, 2, 0)) + getFaceColor(getColor(FACE::LEFT, 2, 2));
    output[18] = getFaceColor(getColor(FACE::DOWN, 2, 0)) + getFaceColor(getColor(FACE::LEFT, 2, 0)) + getFaceColor(getColor(FACE::BACK, 2, 2));
    output[19] = getFaceColor(getColor(FACE::DOWN, 2, 2)) + getFaceColor(getColor(FACE::BACK, 2, 0)) + getFaceColor(getColor(FACE::RIGHT, 2, 2));

    return output;
}

/**
 * Describe a move using an index.
 */
std::string CubeModel::getMove(MOVE ind) const
{
    switch (ind)
    {
    case MOVE::L:
        return "L";
    case MOVE::LPRIME:
        return "L'";
    case MOVE::L2:
        return "L2";
    case MOVE::R:
        return "R";
    case MOVE::RPRIME:
        return "R'";
    case MOVE::R2:
        return "R2";
    case MOVE::U:
        return "U";
    case MOVE::UPRIME:
        return "U'";
    case MOVE::U2:
        return "U2";
    case MOVE::D:
        return "D";
    case MOVE::DPRIME:
        return "D'";
    case MOVE::D2:
        return "D2";
    case MOVE::F:
        return "F";
    case MOVE::FPRIME:
        return "F'";
    case MOVE::F2:
        return "F2";
    case MOVE::B:
        return "B";
    case MOVE::BPRIME:
        return "B'";
    case MOVE::B2:
        return "B2";
    default:
        throw CubeException("Invalid face turn index. (GET MOVE)");
    };
}



/**
   * Get the edge colors at an index.
   */
std::array<CubeModel::COLOR, 2> CubeModel::getEdgeColors(
    CubeModel::EDGE ind) const
{
    std::array<COLOR, 2> colors;

    Cubie edge = this->edges.at((unsigned)ind);

    switch ((EDGE)edge.index)
    {
    case EDGE::UB:
        colors[0] = COLOR::ORANGE;
        colors[1] = COLOR::BLUE;
        break;

    case EDGE::UR:
        colors[0] = COLOR::ORANGE;
        colors[1] = COLOR::WHITE;
        break;

    case EDGE::UF:
        colors[0] = COLOR::ORANGE;
        colors[1] = COLOR::GREEN;
        break;

    case EDGE::UL:
        colors[0] = COLOR::ORANGE;
        colors[1] = COLOR::YELLOW;
        break;

    case EDGE::FR:
        colors[0] = COLOR::GREEN;
        colors[1] = COLOR::WHITE;
        break;

    case EDGE::FL:
        colors[0] = COLOR::GREEN;
        colors[1] = COLOR::YELLOW;
        break;

    case EDGE::BL:
        colors[0] = COLOR::BLUE;
        colors[1] = COLOR::YELLOW;
        break;

    case EDGE::BR:
        colors[0] = COLOR::BLUE;
        colors[1] = COLOR::WHITE;
        break;

    case EDGE::DF:
        colors[0] = COLOR::RED;
        colors[1] = COLOR::GREEN;
        break;

    case EDGE::DL:
        colors[0] = COLOR::RED;
        colors[1] = COLOR::YELLOW;
        break;

    case EDGE::DB:
        colors[0] = COLOR::RED;
        colors[1] = COLOR::BLUE;
        break;

    case EDGE::DR:
        colors[0] = COLOR::RED;
        colors[1] = COLOR::WHITE;
        break;
    }

    if (edge.orientation == 1)
        std::swap(colors[0], colors[1]);

    return colors;
}

/**
   * Get the corner colors at an index.  Three colors are returns: U or D, L or
   * R, F or B (YXZ).
   */
std::array<CubeModel::COLOR, 3> CubeModel::getCornerColors(
    CubeModel::CORNER ind) const
{
    std::array<COLOR, 3> colors;

    Cubie corner = this->corners.at((unsigned)ind);

    unsigned i0, i1, i2;

    // Red or orange on top.
    if (corner.orientation == 0)
    {
        i0 = 0;
        i1 = 1;
        i2 = 2;

        // A quarter turn of U or D std::swaps the two other colors.
        if ((corner.index + (unsigned)ind) % 2 == 1)
            std::swap(i1, i2);
    }
    else if (corner.orientation == 1)
    {
        i0 = 1;
        i1 = 2;
        i2 = 0;

        if ((corner.index + (unsigned)ind) % 2 == 1)
            std::swap(i0, i1);
    }
    else // if (corner.orientation == 2)
    {
        i0 = 2;
        i1 = 0;
        i2 = 1;

        if ((corner.index + (unsigned)ind) % 2 == 1)
            std::swap(i0, i2);
    }

    switch ((CORNER)corner.index)
    {
    case CORNER::ULB:
        colors[i0] = COLOR::ORANGE;
        colors[i1] = COLOR::YELLOW;
        colors[i2] = COLOR::BLUE;
        break;

    case CORNER::URB:
        colors[i0] = COLOR::ORANGE;
        colors[i1] = COLOR::WHITE;
        colors[i2] = COLOR::BLUE;
        break;

    case CORNER::URF:
        colors[i0] = COLOR::ORANGE;
        colors[i1] = COLOR::WHITE;
        colors[i2] = COLOR::GREEN;
        break;

    case CORNER::ULF:
        colors[i0] = COLOR::ORANGE;
        colors[i1] = COLOR::YELLOW;
        colors[i2] = COLOR::GREEN;
        break;

    case CORNER::DLF:
        colors[i0] = COLOR::RED;
        colors[i1] = COLOR::YELLOW;
        colors[i2] = COLOR::GREEN;
        break;

    case CORNER::DLB:
        colors[i0] = COLOR::RED;
        colors[i1] = COLOR::YELLOW;
        colors[i2] = COLOR::BLUE;
        break;

    case CORNER::DRB:
        colors[i0] = COLOR::RED;
        colors[i1] = COLOR::WHITE;
        colors[i2] = COLOR::BLUE;
        break;

    case CORNER::DRF:
        colors[i0] = COLOR::RED;
        colors[i1] = COLOR::WHITE;
        colors[i2] = COLOR::GREEN;
        break;
    }

    return colors;
}


/**
   * Get the facet color using a face, row, and column.
   */
CubeModel::COLOR CubeModel::getColor(
    FACE f, unsigned row, unsigned col) const
{
    if (row == 1 && col == 1)
        return (COLOR)this->centers[(unsigned)f];

    // The colors are arranged Y, X, Z (see getCornerColors).
    if (f == FACE::UP)
    {
        if (row == 0)
        {
            if (col == 0)
                return this->getCornerColors(CORNER::ULB)[0];
            else if (col == 1)
                return this->getEdgeColors(EDGE::UB)[0];
            else
                return this->getCornerColors(CORNER::URB)[0];
        }
        else if (row == 1)
        {
            if (col == 0)
                return this->getEdgeColors(EDGE::UL)[0];
            else
                return this->getEdgeColors(EDGE::UR)[0];
        }
        else
        {
            if (col == 0)
                return this->getCornerColors(CORNER::ULF)[0];
            else if (col == 1)
                return this->getEdgeColors(EDGE::UF)[0];
            else
                return this->getCornerColors(CORNER::URF)[0];
        }
    }
    else if (f == FACE::LEFT)
    {
        if (row == 0)
        {
            if (col == 0)
                return this->getCornerColors(CORNER::ULB)[1];
            else if (col == 1)
                return this->getEdgeColors(EDGE::UL)[1];
            else
                return this->getCornerColors(CORNER::ULF)[1];
        }
        else if (row == 1)
        {
            if (col == 0)
                return this->getEdgeColors(EDGE::BL)[1];
            else
                return this->getEdgeColors(EDGE::FL)[1];
        }
        else
        {
            if (col == 0)
                return this->getCornerColors(CORNER::DLB)[1];
            else if (col == 1)
                return this->getEdgeColors(EDGE::DL)[1];
            else
                return this->getCornerColors(CORNER::DLF)[1];
        }
    }
    else if (f == FACE::FRONT)
    {
        if (row == 0)
        {
            if (col == 0)
                return this->getCornerColors(CORNER::ULF)[2];
            else if (col == 1)
                return this->getEdgeColors(EDGE::UF)[1];
            else
                return this->getCornerColors(CORNER::URF)[2];
        }
        else if (row == 1)
        {
            if (col == 0)
                return this->getEdgeColors(EDGE::FL)[0];
            else
                return this->getEdgeColors(EDGE::FR)[0];
        }
        else
        {
            if (col == 0)
                return this->getCornerColors(CORNER::DLF)[2];
            else if (col == 1)
                return this->getEdgeColors(EDGE::DF)[1];
            else
                return this->getCornerColors(CORNER::DRF)[2];
        }
    }
    else if (f == FACE::RIGHT)
    {
        if (row == 0)
        {
            if (col == 0)
                return this->getCornerColors(CORNER::URF)[1];
            else if (col == 1)
                return this->getEdgeColors(EDGE::UR)[1];
            else
                return this->getCornerColors(CORNER::URB)[1];
        }
        else if (row == 1)
        {
            if (col == 0)
                return this->getEdgeColors(EDGE::FR)[1];
            else
                return this->getEdgeColors(EDGE::BR)[1];
        }
        else
        {
            if (col == 0)
                return this->getCornerColors(CORNER::DRF)[1];
            else if (col == 1)
                return this->getEdgeColors(EDGE::DR)[1];
            else
                return this->getCornerColors(CORNER::DRB)[1];
        }
    }
    else if (f == FACE::BACK)
    {
        if (row == 0)
        {
            if (col == 0)
                return this->getCornerColors(CORNER::URB)[2];
            else if (col == 1)
                return this->getEdgeColors(EDGE::UB)[1];
            else
                return this->getCornerColors(CORNER::ULB)[2];
        }
        else if (row == 1)
        {
            if (col == 0)
                return this->getEdgeColors(EDGE::BR)[0];
            else
                return this->getEdgeColors(EDGE::BL)[0];
        }
        else
        {
            if (col == 0)
                return this->getCornerColors(CORNER::DRB)[2];
            else if (col == 1)
                return this->getEdgeColors(EDGE::DB)[1];
            else
                return this->getCornerColors(CORNER::DLB)[2];
        }
    }
    else // if (f == FACE::DOWN)
    {
        if (row == 0)
        {
            if (col == 0)
                return this->getCornerColors(CORNER::DLF)[0];
            else if (col == 1)
                return this->getEdgeColors(EDGE::DF)[0];
            else
                return this->getCornerColors(CORNER::DRF)[0];
        }
        else if (row == 1)
        {
            if (col == 0)
                return this->getEdgeColors(EDGE::DL)[0];
            else
                return this->getEdgeColors(EDGE::DR)[0];
        }
        else
        {
            if (col == 0)
                return this->getCornerColors(CORNER::DLB)[0];
            else if (col == 1)
                return this->getEdgeColors(EDGE::DB)[0];
            else
                return this->getCornerColors(CORNER::DRB)[0];
        }
    }
}


/**
* Helper to update the orientation of corners on an L or R turn.
*/
inline void CubeModel::updateCornerOrientationX(CORNER ind)
{
    Cubie& corner = this->corners[(unsigned)ind];

    // The new orientation differs based on its distance from home.  E.g.
    // moving corner 0 (RBY) left moves it from ULB (0) to ULF (3).  That's an
    // odd distance (0+3), so the orientation is 1 (Y on top).  Moving corner 0
    // (RBY) left prime from ULF (3) to ULB (0) is even (0+0), so the
    // orientation is 2.
    bool evenDist = ((uint8_t)ind + corner.index) % 2 == 0;

    if (corner.orientation == 0)
        corner.orientation = evenDist ? 2 : 1;
    else if (corner.orientation == 1)
        corner.orientation = evenDist ? 0 : 2;
    else // if (corner.orientation == 2)
        corner.orientation = evenDist ? 1 : 0;
}

/**
 * Helper to update the orientation of corners on an F or B turn.
 */
inline void CubeModel::updateCornerOrientationZ(CORNER ind)
{
    Cubie& corner = this->corners[(unsigned)ind];

    // Moving corner 3 (RBW) front moves it from ULF (3) to URF (2).  That's an
    // odd distance (3+2), so the orientation is 2 (B on top).  Moving corner 3
    // (RBW) front prime from URF (2) to ULF (3) is even (3+3), so the
    // orientation is 1.
    bool evenDist = ((uint8_t)ind + corner.index) % 2 == 0;

    if (corner.orientation == 0)
        corner.orientation = evenDist ? 1 : 2;
    else if (corner.orientation == 1)
        corner.orientation = evenDist ? 2 : 0;
    else // if (corner.orientation == 2)
        corner.orientation = evenDist ? 0 : 1;
}

/**
* Helper to update the orientation of edges on an F or B turn.  Moving F or
* B toggles the orientation of each edge.
*/
inline void CubeModel::updateEdgeOrientationZ(EDGE ind)
{
    this->edges[(unsigned)ind].orientation ^= 1;
}

CubeModel& CubeModel::f()
{
    Cubie hold                           = this->corners[(unsigned)CORNER::ULF];
    this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::DLF];
    this->corners[(unsigned)CORNER::DLF] = this->corners[(unsigned)CORNER::DRF];
    this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::URF];
    this->corners[(unsigned)CORNER::URF] = hold;

    hold                                 = this->edges[(unsigned)EDGE::UF];
    this->edges[(unsigned)EDGE::UF]      = this->edges[(unsigned)EDGE::FL];
    this->edges[(unsigned)EDGE::FL]      = this->edges[(unsigned)EDGE::DF];
    this->edges[(unsigned)EDGE::DF]      = this->edges[(unsigned)EDGE::FR];
    this->edges[(unsigned)EDGE::FR]      = hold;

    this->updateCornerOrientationZ(CORNER::ULF);
    this->updateCornerOrientationZ(CORNER::URF);
    this->updateCornerOrientationZ(CORNER::DRF);
    this->updateCornerOrientationZ(CORNER::DLF);

    this->updateEdgeOrientationZ(EDGE::UF);
    this->updateEdgeOrientationZ(EDGE::FL);
    this->updateEdgeOrientationZ(EDGE::DF);
    this->updateEdgeOrientationZ(EDGE::FR);

    return *this;
}

CubeModel& CubeModel::fPrime()
{
    Cubie hold                           = this->corners[(unsigned)CORNER::ULF];
    this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::URF];
    this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::DRF];
    this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::DLF];
    this->corners[(unsigned)CORNER::DLF] = hold;

    hold                                 = this->edges[(unsigned)EDGE::UF];
    this->edges[(unsigned)EDGE::UF]      = this->edges[(unsigned)EDGE::FR];
    this->edges[(unsigned)EDGE::FR]      = this->edges[(unsigned)EDGE::DF];
    this->edges[(unsigned)EDGE::DF]      = this->edges[(unsigned)EDGE::FL];
    this->edges[(unsigned)EDGE::FL]      = hold;

    this->updateCornerOrientationZ(CORNER::ULF);
    this->updateCornerOrientationZ(CORNER::URF);
    this->updateCornerOrientationZ(CORNER::DRF);
    this->updateCornerOrientationZ(CORNER::DLF);

    this->updateEdgeOrientationZ(EDGE::UF);
    this->updateEdgeOrientationZ(EDGE::FL);
    this->updateEdgeOrientationZ(EDGE::DF);
    this->updateEdgeOrientationZ(EDGE::FR);

    return *this;
}


CubeModel& CubeModel::b()
{
    Cubie hold                           = this->corners[(unsigned)CORNER::ULB];
    this->corners[(unsigned)CORNER::ULB] = this->corners[(unsigned)CORNER::URB];
    this->corners[(unsigned)CORNER::URB] = this->corners[(unsigned)CORNER::DRB];
    this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::DLB];
    this->corners[(unsigned)CORNER::DLB] = hold;

    hold                                 = this->edges[(unsigned)EDGE::UB];
    this->edges[(unsigned)EDGE::UB]      = this->edges[(unsigned)EDGE::BR];
    this->edges[(unsigned)EDGE::BR]      = this->edges[(unsigned)EDGE::DB];
    this->edges[(unsigned)EDGE::DB]      = this->edges[(unsigned)EDGE::BL];
    this->edges[(unsigned)EDGE::BL]      = hold;

    this->updateCornerOrientationZ(CORNER::ULB);
    this->updateCornerOrientationZ(CORNER::URB);
    this->updateCornerOrientationZ(CORNER::DRB);
    this->updateCornerOrientationZ(CORNER::DLB);

    this->updateEdgeOrientationZ(EDGE::UB);
    this->updateEdgeOrientationZ(EDGE::BL);
    this->updateEdgeOrientationZ(EDGE::DB);
    this->updateEdgeOrientationZ(EDGE::BR);

    return *this;
}

CubeModel& CubeModel::bPrime()
{
    Cubie hold                           = this->corners[(unsigned)CORNER::ULB];
    this->corners[(unsigned)CORNER::ULB] = this->corners[(unsigned)CORNER::DLB];
    this->corners[(unsigned)CORNER::DLB] = this->corners[(unsigned)CORNER::DRB];
    this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::URB];
    this->corners[(unsigned)CORNER::URB] = hold;

    hold                                 = this->edges[(unsigned)EDGE::UB];
    this->edges[(unsigned)EDGE::UB]      = this->edges[(unsigned)EDGE::BL];
    this->edges[(unsigned)EDGE::BL]      = this->edges[(unsigned)EDGE::DB];
    this->edges[(unsigned)EDGE::DB]      = this->edges[(unsigned)EDGE::BR];
    this->edges[(unsigned)EDGE::BR]      = hold;

    this->updateCornerOrientationZ(CORNER::ULB);
    this->updateCornerOrientationZ(CORNER::URB);
    this->updateCornerOrientationZ(CORNER::DRB);
    this->updateCornerOrientationZ(CORNER::DLB);

    this->updateEdgeOrientationZ(EDGE::UB);
    this->updateEdgeOrientationZ(EDGE::BL);
    this->updateEdgeOrientationZ(EDGE::DB);
    this->updateEdgeOrientationZ(EDGE::BR);

    return *this;
}

CubeModel& CubeModel::l()
{
    Cubie hold                           = this->corners[(unsigned)CORNER::DLB];
    this->corners[(unsigned)CORNER::DLB] = this->corners[(unsigned)CORNER::DLF];
    this->corners[(unsigned)CORNER::DLF] = this->corners[(unsigned)CORNER::ULF];
    this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::ULB];
    this->corners[(unsigned)CORNER::ULB] = hold;

    hold                                 = this->edges[(unsigned)EDGE::BL];
    this->edges[(unsigned)EDGE::BL]      = this->edges[(unsigned)EDGE::DL];
    this->edges[(unsigned)EDGE::DL]      = this->edges[(unsigned)EDGE::FL];
    this->edges[(unsigned)EDGE::FL]      = this->edges[(unsigned)EDGE::UL];
    this->edges[(unsigned)EDGE::UL]      = hold;

    this->updateCornerOrientationX(CORNER::DLB);
    this->updateCornerOrientationX(CORNER::DLF);
    this->updateCornerOrientationX(CORNER::ULF);
    this->updateCornerOrientationX(CORNER::ULB);

    return *this;
}

CubeModel& CubeModel::lPrime()
{
    Cubie hold                           = this->corners[(unsigned)CORNER::DLB];
    this->corners[(unsigned)CORNER::DLB] = this->corners[(unsigned)CORNER::ULB];
    this->corners[(unsigned)CORNER::ULB] = this->corners[(unsigned)CORNER::ULF];
    this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::DLF];
    this->corners[(unsigned)CORNER::DLF] = hold;

    hold                                 = this->edges[(unsigned)EDGE::BL];
    this->edges[(unsigned)EDGE::BL]      = this->edges[(unsigned)EDGE::UL];
    this->edges[(unsigned)EDGE::UL]      = this->edges[(unsigned)EDGE::FL];
    this->edges[(unsigned)EDGE::FL]      = this->edges[(unsigned)EDGE::DL];
    this->edges[(unsigned)EDGE::DL]      = hold;

    this->updateCornerOrientationX(CORNER::DLB);
    this->updateCornerOrientationX(CORNER::DLF);
    this->updateCornerOrientationX(CORNER::ULF);
    this->updateCornerOrientationX(CORNER::ULB);

    return *this;
}

CubeModel& CubeModel::r()
{
    Cubie hold                           = this->corners[(unsigned)CORNER::DRB];
    this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::URB];
    this->corners[(unsigned)CORNER::URB] = this->corners[(unsigned)CORNER::URF];
    this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::DRF];
    this->corners[(unsigned)CORNER::DRF] = hold;

    hold                                 = this->edges[(unsigned)EDGE::BR];
    this->edges[(unsigned)EDGE::BR]      = this->edges[(unsigned)EDGE::UR];
    this->edges[(unsigned)EDGE::UR]      = this->edges[(unsigned)EDGE::FR];
    this->edges[(unsigned)EDGE::FR]      = this->edges[(unsigned)EDGE::DR];
    this->edges[(unsigned)EDGE::DR]      = hold;

    this->updateCornerOrientationX(CORNER::DRB);
    this->updateCornerOrientationX(CORNER::DRF);
    this->updateCornerOrientationX(CORNER::URF);
    this->updateCornerOrientationX(CORNER::URB);

    return *this;
}

CubeModel& CubeModel::rPrime()
{
    Cubie hold                           = this->corners[(unsigned)CORNER::DRB];
    this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::DRF];
    this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::URF];
    this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::URB];
    this->corners[(unsigned)CORNER::URB] = hold;

    hold                                 = this->edges[(unsigned)EDGE::BR];
    this->edges[(unsigned)EDGE::BR]      = this->edges[(unsigned)EDGE::DR];
    this->edges[(unsigned)EDGE::DR]      = this->edges[(unsigned)EDGE::FR];
    this->edges[(unsigned)EDGE::FR]      = this->edges[(unsigned)EDGE::UR];
    this->edges[(unsigned)EDGE::UR]      = hold;

    this->updateCornerOrientationX(CORNER::DRB);
    this->updateCornerOrientationX(CORNER::DRF);
    this->updateCornerOrientationX(CORNER::URF);
    this->updateCornerOrientationX(CORNER::URB);

    return *this;
}


CubeModel& CubeModel::u()
{
    Cubie hold                           = this->corners[(unsigned)CORNER::ULF];
    this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::URF];
    this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::URB];
    this->corners[(unsigned)CORNER::URB] = this->corners[(unsigned)CORNER::ULB];
    this->corners[(unsigned)CORNER::ULB] = hold;

    hold                                 = this->edges[(unsigned)EDGE::UL];
    this->edges[(unsigned)EDGE::UL]      = this->edges[(unsigned)EDGE::UF];
    this->edges[(unsigned)EDGE::UF]      = this->edges[(unsigned)EDGE::UR];
    this->edges[(unsigned)EDGE::UR]      = this->edges[(unsigned)EDGE::UB];
    this->edges[(unsigned)EDGE::UB]      = hold;

    return *this;
}

CubeModel& CubeModel::uPrime()
{
    Cubie hold                           = this->corners[(unsigned)CORNER::ULB];
    this->corners[(unsigned)CORNER::ULB] = this->corners[(unsigned)CORNER::URB];
    this->corners[(unsigned)CORNER::URB] = this->corners[(unsigned)CORNER::URF];
    this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::ULF];
    this->corners[(unsigned)CORNER::ULF] = hold;

    hold                                 = this->edges[(unsigned)EDGE::UB];
    this->edges[(unsigned)EDGE::UB]      = this->edges[(unsigned)EDGE::UR];
    this->edges[(unsigned)EDGE::UR]      = this->edges[(unsigned)EDGE::UF];
    this->edges[(unsigned)EDGE::UF]      = this->edges[(unsigned)EDGE::UL];
    this->edges[(unsigned)EDGE::UL]      = hold;

    return *this;
}


CubeModel& CubeModel::d()
{
    Cubie hold                           = this->corners[(unsigned)CORNER::DLB];
    this->corners[(unsigned)CORNER::DLB] = this->corners[(unsigned)CORNER::DRB];
    this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::DRF];
    this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::DLF];
    this->corners[(unsigned)CORNER::DLF] = hold;

    hold                                 = this->edges[(unsigned)EDGE::DB];
    this->edges[(unsigned)EDGE::DB]      = this->edges[(unsigned)EDGE::DR];
    this->edges[(unsigned)EDGE::DR]      = this->edges[(unsigned)EDGE::DF];
    this->edges[(unsigned)EDGE::DF]      = this->edges[(unsigned)EDGE::DL];
    this->edges[(unsigned)EDGE::DL]      = hold;

    return *this;
}


CubeModel& CubeModel::dPrime()
{
    Cubie hold                           = this->corners[(unsigned)CORNER::DLF];
    this->corners[(unsigned)CORNER::DLF] = this->corners[(unsigned)CORNER::DRF];
    this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::DRB];
    this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::DLB];
    this->corners[(unsigned)CORNER::DLB] = hold;

    hold                                 = this->edges[(unsigned)EDGE::DL];
    this->edges[(unsigned)EDGE::DL]      = this->edges[(unsigned)EDGE::DF];
    this->edges[(unsigned)EDGE::DF]      = this->edges[(unsigned)EDGE::DR];
    this->edges[(unsigned)EDGE::DR]      = this->edges[(unsigned)EDGE::DB];
    this->edges[(unsigned)EDGE::DB]      = hold;

    return *this;
}


CubeModel& CubeModel::u2()
{
    std::swap(this->corners[(unsigned)CORNER::ULB], this->corners[(unsigned)CORNER::URF]);
    std::swap(this->corners[(unsigned)CORNER::URB], this->corners[(unsigned)CORNER::ULF]);

    std::swap(this->edges[(unsigned)EDGE::UB],      this->edges[(unsigned)EDGE::UF]);
    std::swap(this->edges[(unsigned)EDGE::UR],      this->edges[(unsigned)EDGE::UL]);

    return *this;
}


CubeModel& CubeModel::l2()
{
    std::swap(this->corners[(unsigned)CORNER::DLB], this->corners[(unsigned)CORNER::ULF]);
    std::swap(this->corners[(unsigned)CORNER::ULB], this->corners[(unsigned)CORNER::DLF]);

    std::swap(this->edges[(unsigned)EDGE::BL],      this->edges[(unsigned)EDGE::FL]);
    std::swap(this->edges[(unsigned)EDGE::UL],      this->edges[(unsigned)EDGE::DL]);

    return *this;
}


CubeModel& CubeModel::f2()
{
    std::swap(this->corners[(unsigned)CORNER::ULF], this->corners[(unsigned)CORNER::DRF]);
    std::swap(this->corners[(unsigned)CORNER::URF], this->corners[(unsigned)CORNER::DLF]);

    std::swap(this->edges[(unsigned)EDGE::UF],      this->edges[(unsigned)EDGE::DF]);
    std::swap(this->edges[(unsigned)EDGE::FL],      this->edges[(unsigned)EDGE::FR]);

    return *this;
}


CubeModel& CubeModel::r2()
{
    std::swap(this->corners[(unsigned)CORNER::DRB], this->corners[(unsigned)CORNER::URF]);
    std::swap(this->corners[(unsigned)CORNER::URB], this->corners[(unsigned)CORNER::DRF]);

    std::swap(this->edges[(unsigned)EDGE::BR],      this->edges[(unsigned)EDGE::FR]);
    std::swap(this->edges[(unsigned)EDGE::UR],      this->edges[(unsigned)EDGE::DR]);

    return *this;
}


CubeModel& CubeModel::b2()
{
    std::swap(this->corners[(unsigned)CORNER::ULB], this->corners[(unsigned)CORNER::DRB]);
    std::swap(this->corners[(unsigned)CORNER::URB], this->corners[(unsigned)CORNER::DLB]);

    std::swap(this->edges[(unsigned)EDGE::UB],      this->edges[(unsigned)EDGE::DB]);
    std::swap(this->edges[(unsigned)EDGE::BL],      this->edges[(unsigned)EDGE::BR]);

    return *this;
}


CubeModel& CubeModel::d2()
{
    std::swap(this->corners[(unsigned)CORNER::DLB], this->corners[(unsigned)CORNER::DRF]);
    std::swap(this->corners[(unsigned)CORNER::DRB], this->corners[(unsigned)CORNER::DLF]);

    std::swap(this->edges[(unsigned)EDGE::DB],      this->edges[(unsigned)EDGE::DF]);
    std::swap(this->edges[(unsigned)EDGE::DR],      this->edges[(unsigned)EDGE::DL]);

    return *this;
}

std::string CubeModel::toString() const {
    char colors[] = {'O', 'Y', 'G', 'W', 'B', 'R'};
    std::string currCube = "";

    for (unsigned row = 0; row < 3; ++ row)
    {
        for (unsigned col = 0; col < 3; ++ col)
            currCube += colors[(unsigned)getColor(FACE::UP, row, col)];
    }

    for (unsigned row = 0; row < 3; ++ row)
    {
        for (unsigned col = 0; col < 3; ++ col)
            currCube += colors[(unsigned)getColor(FACE::LEFT,  row, col)];
    }

    for (unsigned row = 0; row < 3; ++ row)
    {
        for (unsigned col = 0; col < 3; ++ col)
            currCube += colors[(unsigned)getColor(FACE::FRONT, row, col)];
    }

    for (unsigned row = 0; row < 3; ++ row)
    {
        for (unsigned col = 0; col < 3; ++ col)
            currCube += colors[(unsigned)getColor(FACE::RIGHT, row, col)];
    }

    for (unsigned row = 0; row < 3; ++ row)
    {
        for (unsigned col = 0; col < 3; ++ col)
            currCube += colors[(unsigned)getColor(FACE::BACK,  row, col)];
    }

    for (unsigned row = 0; row < 3; ++ row)
    {
        for (unsigned col = 0; col < 3; ++ col)
            currCube += colors[(unsigned)getColor(FACE::DOWN, row, col)];
    }
    return currCube;
}
