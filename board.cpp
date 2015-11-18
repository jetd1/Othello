#include "elements.h"
#include <iomanip>
#include <sstream>
#include <algorithm>

extern bool inRange(int p, int q);
extern bool cmpCoordC(const Coord &A, const Coord &B);
extern void fatalError(unsigned ErrorCode);

extern Cell NULLCELL;
extern short dir[8][2];
extern short coordChara[SAFE_LENGTH][SAFE_LENGTH];
extern bool debugFlag, assistFlag, AIFlag, playerSide;

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
    movesRecord.clear();

    for (int i : {0, 1, 3})
        statusCount[i] = 0;

    statusCount[2] = 64;
    vValue = 0;

    aValue[White] = aValue[Black] = 0;
    sideFlag = Black;
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
    movesRecord = board.movesRecord;

    for (int i = 0; i < 4; i++)
        statusCount[i] = board.statusCount[i];

    vValue = board.vValue;

    aValue[White] = board.aValue[White];
    aValue[Black] = board.aValue[Black];
    sideFlag = board.sideFlag;
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
    movesRecord.clear();

    for (int i : {0, 1, 3})
        statusCount[i] = 0;

    statusCount[2] = 64;

    vValue = 0;

    aValue[White] = aValue[Black] = 0;
    sideFlag = Black;
}

void Board::flipSide() { sideFlag ^= 1; }

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

void Board::setValid()
{
    validCoord.clear();
    statusCount[Valid] = 0;
    for (int i = 1; i <= SIDE_LENGTH; i++)
        for (int j = 1; j <= SIDE_LENGTH; j++)
        {
            if (cell[i][j].stat <= Black) continue;

            if (isValid(cell[i][j].pos, sideFlag))
            {
                cell[i][j].stat = Valid;
                statusCount[Valid]++;
                validCoord.push_back(cell[i][j].pos);
            }
            else cell[i][j].stat = Empty;
        }
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

void Board::move(Coord &pos)
{
    for (int i = 0; i < 8; i++)
    {
        int dx = dir[i][0], dy = dir[i][1];

        if (cell[pos.x + dx][pos.y + dy].stat == !sideFlag)
        {
            for (int p = pos.x + dx, q = pos.y + dy; inRange(p, q); p += dx, q += dy)
            {
                if (cell[p][q].stat >= Empty) break;
                if (cell[p][q].stat == status(sideFlag))
                {
                    cell[pos.x][pos.y].stat = status(sideFlag);

                    for (int r = p - dx, s = q - dy; cell[r][s].stat != status(sideFlag); r -= dx, s -= dy)
                        cell[r][s].stat = status(sideFlag);
                    break;
                }
            }
        }
    }
    flipSide();
    setValid();
    count();
}

void Board::print()
{
    if (!debugFlag)
    {
        SLP(100);
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
                    if (assistFlag && ((AIFlag == AI_MODE&&sideFlag == playerSide) || (AIFlag == NON_AI_MODE))) 
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

bool Board::save()
{
    ofstream save("Othello.save");
    if (!save)
    {
        cout << "Unable to Save, Game Will Now Resume!";
        PAUSE;
        return false;
    }
    save << assistFlag << endl;
    save << playerSide << endl;
    save << AI_MODE << endl << endl;
    save << movesRecord.size() << endl;
    for (int i = 0; i < movesRecord.size(); i++)
        save << movesRecord[i].x << ' '
             << movesRecord[i].y << endl << endl;
    save.close();
    
    ifstream load("Othello.save");
    ofstream hsave("Othello.hash");
    if (!load||!hsave)
    {
        remove("Othello.save");
        remove("Othello.hash");
        cout << "Unable to Save, Game Will Now Resume!";
        PAUSE;
        return false;
    }
    ostringstream sload;
    sload << load.rdbuf();

    string read = sload.str();

    hash<string> hashptr;

    hsave << hashptr(read);
    hsave.close();
    load.close();

    return true;
}



