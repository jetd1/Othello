#include "board.h"
#include <iomanip>
#include <sstream>
#include <iterator>
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
    validCountFor[Black] = validCountFor[White] = 0;

    passCount = 0;
    passFlag[Black] = passFlag[White] = false;

    sideFrontier[White].clear();
    sideFrontier[Black].clear();
    allFrontier.clear();

    validCoord.clear();
    movesRecord.clear();

    for (int i : {0, 1, 3})
        statusCount[i] = 0;

    statusCount[2] = 64;

    aValue[White] = aValue[Black] = 0;
    sideFlag = Black;
}

//overload operators
Cell* Board::operator [](int i) { return cell[i]; }
short Board::operator ()(Status stat) { return statusCount[stat]; }
short Board::operator ()(bool flag) { return statusCount[flag]; }
bool Board::operator ==(const Status &stat)const { return int(sideFlag) == stat; }
void Board::operator =(Board &board)     //need to rewrite
{
    board.count();
    for (int i = 0; i < SAFE_LENGTH; i++)
        for (int j = 0; j < SAFE_LENGTH; j++)
            cell[i][j] = board.cell[i][j];

    validCountFor[Black] = board.validCountFor[Black];
    validCountFor[White] = board.validCountFor[White];

    passCount = board.passCount;
    passFlag[Black] = board.passFlag[Black];
    passFlag[White] = board.passFlag[White];

    sideFrontier[White] = board.sideFrontier[White];
    sideFrontier[Black] = board.sideFrontier[Black];
    allFrontier = board.allFrontier;
    validCoord = board.validCoord;
    movesRecord = board.movesRecord;

    for (int i = 0; i < 4; i++)
        statusCount[i] = board(Status(i));

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

    validCountFor[Black] = validCountFor[White] = 0;
    passCount = 0;
    passFlag[Black] = passFlag[White] = false;

    sideFrontier[White].clear();
    sideFrontier[Black].clear();
    allFrontier.clear();
    validCoord.clear();
    movesRecord.clear();

    for (int i : {0, 1, 3})
        statusCount[i] = 0;

    statusCount[2] = 64;

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

void Board::setFrontierFor(bool side)
{
    sideFrontier[side].clear();
    for (short i = 1; i <= SIDE_LENGTH; i++)
        for (short j = 1; j <= SIDE_LENGTH; j++)
            if (cell[i][j].stat == Status(side))
                for (int d = 0; d < 8; d++)
                {
                    short x = i + dir[d][0];
                    short y = j + dir[d][1];
                    if (inRange(x, y) && (cell[x][y].stat >= Empty))
                        sideFrontier[Status(side)].insert(cell[x][y].coord);
                }
}

void Board::setFrontier()
{
    setFrontierFor(sideFlag);
    setFrontierFor(!sideFlag);
    allFrontier.clear();
    set_union(sideFrontier[sideFlag].begin(), sideFrontier[sideFlag].end(), sideFrontier[!sideFlag].begin(), sideFrontier[!sideFlag].end(), inserter(allFrontier, allFrontier.begin()));
}

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
                if (cell[p][q].stat >= Empty) 
                    break;
                if (cell[p][q].stat == int(side)) 
                    return true;
            }
        }
    }
    return false;
}

void Board::setValid()
{
    setFrontier();
    validCoord.clear();
    statusCount[Valid] = 0;
    validCountFor[Black] = validCountFor[White] = 0;
    for (auto itr = allFrontier.begin(); itr != allFrontier.end(); itr++)
    {
        Coord tmpCoord = *itr;
        short x = tmpCoord.x;
        short y = tmpCoord.y;
        if (isValid(tmpCoord, sideFlag))
        {
            cell[x][y].stat = Valid;
            statusCount[Valid]++;
            validCountFor[sideFlag]++;
            validCoord.push_back(cell[x][y].coord);
        }
        else
        {
            cell[x][y].stat = Empty;
            if (isValid(tmpCoord, !sideFlag))
                validCountFor[!sideFlag]++;
        }
    }
        
    sort(validCoord.begin(), validCoord.end(), cmpCoord);
}

void Board::move(Coord &pos)
{
    if (pos.x == -1 && pos.y == -1)
    {
        passCount++;
        passFlag[sideFlag] = true;
    }

    else if (inRange(pos.x, pos.y))
    {
        for (int i = 0; i < 8; i++)
        {
            int dx = dir[i][0], dy = dir[i][1];

            if (cell[pos.x + dx][pos.y + dy].stat == !sideFlag)
            {
                for (int p = pos.x + dx, q = pos.y + dy; inRange(p, q); p += dx, q += dy)
                {
                    if (cell[p][q].stat >= Empty)
                        break;
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
        passFlag[sideFlag] = false;
    }
    else
        fatalError(1);

    movesRecord.push_back(pos);
    flipSide();
    setValid();
    count();
}

#ifdef WINDOWS_
void Board::print()
{
    if (!debugFlag)
    {
        SLP(1);
        CLS;
    }
    cout << endl;
    cout << "            Round " << movesRecord.size() + 1 << (sideFlag ? ", Black" : ", White") << " Turn" << endl;
    cout << endl;
    cout << "      ";
    for (int i = 1; i <= SIDE_LENGTH; i++)
        cout << char('@' + i) << "   ";

    cout << endl << "    ┌─┬─┬─┬─┬─┬─┬─┬─┐" << endl;

    for (int i = 1; i <= SIDE_LENGTH; i++)
    {
        cout << "   " << i << "│";
        for (int j = 1; j <= SIDE_LENGTH; j++)
        {
            switch (cell[i][j].stat)
            {
                case Black:
                    cout << "●│";
                    break;
                case White:
                    cout << "○│";
                    break;
                case Empty:
                    cout << "  │";
                    break;
                case Valid:
                    if (assistFlag && ((AIFlag == AI_MODE&&sideFlag == playerSide) || (AIFlag == NON_AI_MODE)))
                        cout << " +│";
                    else
                        cout << "  │";
                    break;
                default:
                    fatalError(1);
            }
        }
        if (i - SIDE_LENGTH)
            cout << endl << "    ├─┼─┼─┼─┼─┼─┼─┼─┤";
        else
            cout << endl << "    └─┴─┴─┴─┴─┴─┴─┴─┘";
        if (i - SIDE_LENGTH) cout << endl;
    }
    cout << endl << left << "       "
        << "Black(●):" << setw(2) << statusCount[Black] << "    "
        << "White(○):" << setw(2) << statusCount[White] << endl;

    if (movesRecord.size() && AIFlag == AI_MODE&&sideFlag == playerSide&&!cPass)
    {
        if (debugFlag)
        {
            ofstream out("timecsm.txt", ios::app);
            out << "Achilles Placed a Stone at "
                << movesRecord[movesRecord.size() - 1].x
                << char(movesRecord[movesRecord.size() - 1].y + '@')
                << endl
                << double(clock() - startTime) / CLOCKS_PER_SEC << " Seconds Consumed."
                << endl << endl;
        }
        cout << endl << "        "
            << "Achilles Placed a Stone at "
            << movesRecord[movesRecord.size() - 1].x
            << char(movesRecord[movesRecord.size() - 1].y + '@')
            << endl << "          "
            << double(clock() - startTime) / CLOCKS_PER_SEC << " Seconds Consumed."
            << endl << endl;
    }
    else cout << endl << endl;
}

#else
void Board::print()
{
    if (!debugFlag)
    {
        SLP(1);
        CLS;
    }
    cout << endl;
    cout << "            Round " << movesRecord.size() + 1 << (sideFlag ? ", Black" : ", White") << " Turn" << endl;
    cout << endl;
    cout << "      ";
    for (int i = 1; i <= SIDE_LENGTH; i++)
        cout << char('@' + i) << "   ";

    cout << endl << "    ┌───┬───┬───┬───┬───┬───┬───┬───┐" << endl;

    for (int i = 1; i <= SIDE_LENGTH; i++)
    {
        cout << "   " << i << "│";
        for (int j = 1; j <= SIDE_LENGTH; j++)
        {
            switch (cell[i][j].stat)
            {
                case Black:
                    cout << " ● │";
                    break;
                case White:
                    cout << " ○ │";
                    break;
                case Empty:
                    cout << "   │";
                    break;
                case Valid:
                    if (assistFlag && ((AIFlag == AI_MODE&&sideFlag == playerSide) || (AIFlag == NON_AI_MODE)))
                        cout << " + │";
                    else
                        cout << "   │";
                    break;
                default:
                    fatalError(1);
            }
        }
        if (i - SIDE_LENGTH)
            cout << endl << "    ├───┼───┼───┼───┼───┼───┼───┼───┤";
        else
            cout << endl << "    └───┴───┴───┴───┴───┴───┴───┴───┘";
        if (i - SIDE_LENGTH) cout << endl;
    }
    cout << endl << left << "       "
        << "Black(●):" << setw(2) << statusCount[Black] << "    "
        << "White(○):" << setw(2) << statusCount[White] << endl;

    if (movesRecord.size() && AIFlag == AI_MODE&&sideFlag == playerSide&&!cPass)
    {
        if (debugFlag)
        {
            ofstream out("timecsm.txt", ios::app);
            out << "Achilles Placed a Stone at "
                << movesRecord[movesRecord.size() - 1].x
                << char(movesRecord[movesRecord.size() - 1].y + '@')
                << endl
                << double(clock() - startTime) / CLOCKS_PER_SEC << " Seconds Consumed."
                << endl << endl;
        }
        cout << endl << "        "
            << "Achilles Placed a Stone at "
            << movesRecord[movesRecord.size() - 1].x
            << char(movesRecord[movesRecord.size() - 1].y + '@')
            << endl << "          "
            << double(clock() - startTime) / CLOCKS_PER_SEC << " Seconds Consumed."
            << endl << endl;
    }
    else cout << endl << endl;
}

#endif

void Board::recordPrint()
{
    cout << "Game Record:" << endl << endl;
    for (unsigned i = 0; i < movesRecord.size(); i++)
        if (movesRecord[i].x != -1)
            cout << movesRecord[i].x << char(movesRecord[i].y + '@') << ' ';
        else
            cout << "PASS" << ' ';
    cout << endl;
}

double Board::allEvalFor(bool side) //Evaluation for all cells of the side
{
    int aval = 0;
    for (int i = 1; i <= SIDE_LENGTH; i++)
        for (int j = 1; j <= SIDE_LENGTH; j++)
            if (cell[i][j].stat == Status(side))
                aval += cell[i][j].coord.value;

    aValue[side] = aval;
    return aValue[side];
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