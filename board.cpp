#include "board.h"
#include <iomanip>
#include <sstream>
#include <algorithm>

//construct function
Board::Board()  //need to rewrite
{
    for (short i = 0; i < SAFE_LENGTH; i++)
        for (short j = 0; j < SAFE_LENGTH; j++)
        {
            cell[i][j] = {
                {i, j, coordChara[i][j]},
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
Cell* Board::operator [](int i) { return cell[i]; }
short Board::operator ()(Status stat) { return statusCount[stat]; }
short Board::operator ()(bool flag) { return statusCount[flag]; }
bool Board::operator >(const Board &board)const { return vValue > board.vValue; }
bool Board::operator <(const Board &board)const { return vValue < board.vValue; }
bool Board::operator ==(const Board &board)const { return vValue == board.vValue; }
bool Board::operator ==(const Status &stat)const { return int(sideFlag) == stat; }
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
        statusCount[i] = board(Status(i));

    vValue = board.vValue;

    aValue[White] = board.aValue[White];
    aValue[Black] = board.aValue[Black];
    sideFlag = board.sideFlag;
}
bool Board::operator ~()const { return Status(sideFlag); }
bool Board::operator !()const { return Status(!sideFlag); }


//member functions
void Board::clear()
{
    for (short i = 0; i < SAFE_LENGTH; i++)
        for (short j = 0; j < SAFE_LENGTH; j++)
        {
            cell[i][j] = {
                {i, j, coordChara[i][j]},
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

void Board::cellclear()
{
    for (short i = 0; i < SAFE_LENGTH; i++)
        for (short j = 0; j < SAFE_LENGTH; j++)
        {
            cell[i][j] = {
                {i, j, coordChara[i][j]},
                Empty};
        }

    validCoord.clear();

    vValue = 0;

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

//short Board::count(Status stat)
//{
//    statusCount[stat] = 0;
//
//    for (int i = 1; i <= SIDE_LENGTH; i++)
//        for (int j = 1; j <= SIDE_LENGTH; j++)
//            statusCount[stat] += (cell[i][j].stat == stat);
//
//    return statusCount[stat];
//}

bool Board::isValid(Coord &pos, bool side)
{
    if (!inRange(pos.x, pos.y))
        return false;
    if (cell[pos.x][pos.y].stat < Empty)
        return false;
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

            if (isValid(cell[i][j].coord, sideFlag))
            {
                cell[i][j].stat = Valid;
                statusCount[Valid]++;
                validCoord.push_back(cell[i][j].coord);
            }
            else cell[i][j].stat = Empty;
        }
    sort(validCoord.begin(), validCoord.end(), cmpCoordV);
}

void Board::setValidFor(bool side)
{
    validCoord.clear();
    statusCount[Valid] = 0;
    for (int i = 1; i <= SIDE_LENGTH; i++)
        for (int j = 1; j <= SIDE_LENGTH; j++)
        {
            if (cell[i][j].stat <= Black) continue;

            if (isValid(cell[i][j].coord, side))
            {
                cell[i][j].stat = Valid;
                statusCount[Valid]++;
                validCoord.push_back(cell[i][j].coord);
            }
            else cell[i][j].stat = Empty;
        }
}

void Board::move(Coord &pos)
{
    if (pos.x == -1)
        passCount++;

    if (inRange(pos.x, pos.y))
        for (int i = 0; i < 8; i++)
        {
            int dx = dir[i][0], dy = dir[i][1];

            if (cell[pos.x + dx][pos.y + dy].stat == !sideFlag)
            {
                for (int p = pos.x + dx, q = pos.y + dy; inRange(p, q); p += dx, q += dy)
                {
                    if (cell[p][q].stat >= Empty) break;
                    if (cell[p][q].stat == Status(sideFlag))
                    {
                        cell[pos.x][pos.y].stat = Status(sideFlag);

                        for (int r = p - dx, s = q - dy; cell[r][s].stat != Status(sideFlag); r -= dx, s -= dy)
                            cell[r][s].stat = Status(sideFlag);
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
    cout << endl;
    cout << "            Round " << movesRecord.size() + 1 << (sideFlag ? ", Black" : ", White") << " Turn" << endl;
    cout << endl;
    cout << "      ";
    for (int i = 1; i <= SIDE_LENGTH; i++)
        cout << char('@' + i) << "   ";
#ifdef WINDOWS_
    cout << endl << "    ┌─┬─┬─┬─┬─┬─┬─┬─┐" << endl;
#else
                    cout << endl << "    ┌───┬───┬───┬───┬───┬───┬───┬───┐" << endl;
#endif

    for (int i = 1; i <= SIDE_LENGTH; i++)
    {
        cout << "   " << i << "│";
        for (int j = 1; j <= SIDE_LENGTH; j++)
        {
            switch (cell[i][j].stat)
            {
                case Black:
#ifdef WINDOWS_
                    cout << "●│";
#else
                    cout << " ● │";
#endif
                    break;
                case White:
#ifdef WINDOWS_
                    cout << "○│";
#else
                    cout << " ○ │";
#endif
                    break;
                case Empty:
#ifdef WINDOWS_
                    cout << "  │";
#else
                    cout << "   │";
#endif
                    break;
                case Valid:
                    if (assistFlag && ((AIFlag == AI_MODE&&sideFlag == playerSide) || (AIFlag == NON_AI_MODE)))
#ifdef WINDOWS_
                    cout << " +│";
#else
                    cout << " + │";
#endif
                    else
#ifdef WINDOWS_
                    cout << "  │";
#else
                    cout << "   │";
#endif
                    break;
                default:
                    fatalError(1);
            }
        }
        if(i-SIDE_LENGTH)
#ifdef WINDOWS_
            cout << endl << "    ├─┼─┼─┼─┼─┼─┼─┼─┤";
#else
                    cout << endl << "    ├───┼───┼───┼───┼───┼───┼───┼───┤";
#endif
        else
#ifdef WINDOWS_
            cout << endl << "    └─┴─┴─┴─┴─┴─┴─┴─┘";
#else
                    cout << endl << "    └───┴───┴───┴───┴───┴───┴───┴───┘";
#endif
        if (i - SIDE_LENGTH) cout << endl;
    }
    cout << endl << left << "       "
        << "Black(●):" << setw(2) << statusCount[Black] << "    "
        << "White(○):" << setw(2) << statusCount[White] << endl;

    if (movesRecord.size()&&AIFlag == AI_MODE&&sideFlag == playerSide&&!cPass)
    {
        if (debugFlag)
        {
            ofstream out("timecsm.txt", ios::app);
            out << "Jacob Placed a Stone at "
                << movesRecord[movesRecord.size() - 1].x
                << char(movesRecord[movesRecord.size() - 1].y + '@')
                << endl
                << double(clock() - startTime) / CLOCKS_PER_SEC << " Seconds Consumed."
                << endl << endl;
        }
        cout << endl << "        "  
            << "Jacob Placed a Stone at "
            << movesRecord[movesRecord.size() - 1].x
            << char(movesRecord[movesRecord.size() - 1].y + '@')
            << endl << "          " 
            << double(clock() - startTime) / CLOCKS_PER_SEC << " Seconds Consumed."
            << endl << endl;
    }
    else cout << endl << endl;
}

double Board::allEval(bool side) //Evaluation for all coordinates of side
{
    int aval = 0;
    for (int i = 0; i < SIDE_LENGTH; i++)
        for (int j = 0; j < SIDE_LENGTH; j++)
            if (cell[i][j].stat == Status(side))
                aval += cell[i][j].coord.value;

    aValue[side] = aval;
    return aValue[side];
}

short Board::frontierCount(bool side)
{
    short cnt = 0;
    for (short i = 1; i <= SIDE_LENGTH; i++)
        for (short j = 1; j <= SIDE_LENGTH; j++)
            if (cell[i][j].stat == Status(side))
                for (int d = 0; d < 8; d++)
                {
                    short x = i + dir[d][0];
                    short y = j + dir[d][1];
                    cnt += (inRange(x, y) && (cell[x][y].stat >= Empty));
                }

    return cnt;
}

//double Board::aEvalRate(bool side) { return double(allEval(side)) / allEval(!side); }
//double Board::aEvalDiff(bool side) { return allEval(side) - allEval(!side); }

//double Board::CountRate(bool side) { return double(count(Status(side))) / count(Status(!side)); }
//double Board::CountDiff(bool side) { return count(Status(side)) - count(Status(!side)); }

//double Board::frontierCountRate(bool side) { return double(frontierCount(side)) / frontierCount(!side); }
//double Board::frontierCountDiff(bool side) { return frontierCount(side) - frontierCount(!side); }

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

bool Board::save(string saveName)
{
    ofstream save(saveName+".save");
    if (!save)
    {
        cout << "    Unable to Save, Game Will Now Resume!";
        PAUSE;
        return false;
    }

    save << AIFlag << endl;
    save << assistFlag << endl;
    save << playerSide << endl;
    save << diff << endl << endl;
    save << movesRecord.size() << endl;
    for (unsigned i = 0; i < movesRecord.size(); i++)
        save << movesRecord[i].x << ' '
        << movesRecord[i].y << endl << endl;
    save.close();

    ifstream load(saveName + ".save");
    ofstream hsave(saveName + ".hash");
    if (!load || !hsave)
    {
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

inline bool inRange(int p, int q) { return p >= 1 && p <= SIDE_LENGTH && q >= 1 && q <= SIDE_LENGTH; }