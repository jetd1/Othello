#include "elements.h"
#include <iomanip>
#include <algorithm>

extern bool inRange(int p, int q);
extern bool cmpCoordC(const Coord &A, const Coord &B);
extern void fatalError(unsigned ErrorCode);

extern Cell NULLCELL;
extern short dir[8][2];
extern short coordChara[SAFE_LENGTH][SAFE_LENGTH];
extern bool assistFlag, modeFlag, sideFlag, playerSide;

//construct function
Board::Board()  //need to rewrite
{
    for (short i = 0; i < SAFE_LENGTH; i++)
        for (short j = 0; j < SAFE_LENGTH; j++)
        {
            cell[i][j] = {
                {i, j, coordChara[i][j], 0},
                Empty};
        }

    validCoord.clear();

    for (int i : {0, 1, 3})
        statusCount[i] = 0;

    statusCount[2] = 64;
    vValue = 0;

    aValue[White] = aValue[Black] = 0;
}

//overload operators
Cell* Board::operator [](int i){return cell[i];}
bool Board::operator >(const Board &board)const { return vValue > board.vValue; }
bool Board::operator <(const Board &board)const { return vValue < board.vValue; }
bool Board::operator ==(const Board &board)const { return vValue == board.vValue; }
bool Board::operator >=(const Board &board)const { return vValue >= board.vValue; }
bool Board::operator <=(const Board &board)const { return vValue <= board.vValue; }

void Board::operator =(Board &board)     //need to rewrite
{
    board.count();
    for (int i = 0; i < SAFE_LENGTH; i++)
        for (int j = 0; j < SAFE_LENGTH; j++)
            cell[i][j] = board.cell[i][j];

    validCoord = board.validCoord;

    for (int i = 0; i < 4; i++)
        statusCount[i] = board.statusCount[i];

    vValue = board.vValue;

    aValue[White] = board.aValue[White];
    aValue[Black] = board.aValue[Black];
}


//member functions
void Board::clear()
{
    for (short i = 0; i < SAFE_LENGTH; i++)
        for (short j = 0; j < SAFE_LENGTH; j++)
        {
            cell[i][j] = {
                {i, j, coordChara[i][j], 0},
                Empty};
        }

    validCoord.clear();

    for (int i : {0, 1, 3})
        statusCount[i] = 0;

    statusCount[2] = 64;

    vValue = 0;

    aValue[White] = aValue[Black] = 0;
}

void Board::count()
{
    statusCount[Black] = statusCount[White] = statusCount[Empty] = 0;
    for (int i = 1; i <= SIDE_LENGTH; i++) 
        for (int j = 1; j <= SIDE_LENGTH; j++)
        {
            statusCount[Black] += (cell[i][j].stat == Black);
            statusCount[White] += (cell[i][j].stat == White);
            statusCount[Empty] += (cell[i][j].stat >= Empty);
        }
}

short Board::count(status stat)
{
    statusCount[stat] = 0;

    for (int i = 1; i <= SIDE_LENGTH; i++) 
        for (int j = 1; j <= SIDE_LENGTH; j++)
            statusCount[stat] += (cell[i][j].stat == stat);

    return statusCount[stat];
}

bool Board::isValid(Coord &pos, bool side)
{
    if (cell[pos.x][pos.y].stat < Empty) return false;
    for (int i = 0; i < 8; i++)
    {
        short dx = dir[i][0], dy = dir[i][1];
        if (cell[pos.x + dx][pos.y + dy].stat == !side)
        {
            for (int p = pos.x + dx, q = pos.y + dy; inRange(p, q); p += dx, q += dy)
            {
                if (cell[p][q].stat >= Empty) break;
                if (cell[p][q].stat == int(side)) return true;
            }
        }
    }
    return false;
}

void Board::setValidFor(bool side)
{
    validCoord.clear();
    statusCount[Valid] = 0;
    for (int i = 1; i <= SIDE_LENGTH; i++) 
        for (int j = 1; j <= SIDE_LENGTH; j++)
        {
            if (cell[i][j].stat <= Black) continue;

            if (isValid(cell[i][j].pos, side))
            {
                cell[i][j].stat = Valid;
                statusCount[Valid]++;
                validCoord.push_back(cell[i][j].pos);
            }
            else cell[i][j].stat = Empty;
        }
}



void Board::move(Coord &pos, bool side)
{
    for (int i = 0; i < 8; i++)
    {
        int dx = dir[i][0], dy = dir[i][1];

        if (cell[pos.x + dx][pos.y + dy].stat == !side)
        {
            for (int p = pos.x + dx, q = pos.y + dy; inRange(p, q); p += dx, q += dy)
            {
                if (cell[p][q].stat >= Empty) break;
                if (cell[p][q].stat == status(side))
                {
                    cell[pos.x][pos.y].stat = status(side);

                    for (int r = p - dx, s = q - dy; cell[r][s].stat != status(side); r -= dx, s -= dy) 
                        cell[r][s].stat = status(side);
                    break;
                }
            }
        }
    }
    setValidFor(!side);
    count();  
}

void Board::print()
{
    if (!DEBUGMODE)
    {
        SLP(200);
        CLS;
    }

    cout << " ";
    for (int i = 1; i <= SIDE_LENGTH; i++) 
        cout << ' ' << char('@' + i);
    cout << endl;
    char outTmp;
    for (int i = 1; i <= SIDE_LENGTH; i++)
    {
        cout << i;
        for (int j = 1; j <= SIDE_LENGTH; j++)
        {
            switch (cell[i][j].stat)
            {
                case Black:
                    outTmp = 'X';
                    break;
                case White:
                    outTmp = 'O';
                    break;
                case Empty:
                    outTmp = ' ';
                    break;
                case Valid:
                    if (assistFlag && ((modeFlag == AI_MODE&&sideFlag == playerSide) || (modeFlag == NON_AI_MODE))) 
                        outTmp = '*';
                    else outTmp = ' ';
                    break;
                default:
                    fatalError(1);
            }
            cout << ' ' << outTmp;
        }
        if (i - SIDE_LENGTH) cout << endl;
    }
    cout << endl << left 
         << "Black(X):" << setw(2) << statusCount[Black]
         << "  White(O):" << setw(2) << statusCount[White] 
         << endl << endl;
}

double Board::validEval(bool side) //Evaluation for valid coordinates of side
{
    setValidFor(side);  //To be cautious, maybe not necessary
    
    sort(validCoord.begin(), validCoord.end(), cmpCoordC);

    int vval=0;
    for (size_t i = 0; i < validCoord.size(); i++)
        vval += validCoord[i].chara;

    vValue = vval;
    return vValue;
}

double Board::allEval(bool side) //Evaluation for all coordinates of side
{
    int aval = 0;
    for (int i = 0; i < SIDE_LENGTH; i++)
        for (int j = 0; j < SIDE_LENGTH; j++)
            if (cell[i][j].stat == status(side))
                aval += cell[i][j].pos.chara;

    aValue[side] = aval;
    return aValue[side];
}

short Board::frontierCount(bool side)
{
    short cnt = 0;
    for (short i = 1; i <= SIDE_LENGTH; i++)
        for (short j = 1; j <= SIDE_LENGTH; j++)
            if (cell[i][j].stat == status(side))
                for (int d = 0; d < 8; d++)
                {
                    short x = i + dir[d][0];
                    short y = j + dir[d][1];
                    cnt += (inRange(x, y) && (cell[x][y].stat >= Empty));
                }

    return cnt;
}

double Board::aEvalRate(bool side) { return double(allEval(side)) / allEval(!side); }
double Board::aEvalDiff(bool side) { return allEval(side) - allEval(!side); }

double Board::CountRate(bool side) { return double(count(status(side))) / count(status(!side)); }
double Board::CountDiff(bool side) { return count(status(side)) - count(status(!side)); }

double Board::frontierCountRate(bool side) { return double(frontierCount(side)) / frontierCount(!side); }
double Board::frontierCountDiff(bool side) { return frontierCount(side) - frontierCount(!side); }


short Board::countValidFor(bool side)
{
    short cnt = 0;
    for (int i = 1; i <= SIDE_LENGTH; i++)
        for (int j = 1; j <= SIDE_LENGTH; j++)
        {
            Coord tmpCoord{};
            tmpCoord.x = i;
            tmpCoord.y = j;
            cnt += isValid(tmpCoord, side);
        }

    return cnt;
}