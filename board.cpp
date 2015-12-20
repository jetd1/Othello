#include "board.h"
#include <iomanip>
#include <sstream>
#include <iterator>
#include <algorithm>

//construct function
Board::Board()
{
    for (short i = 0; i < 10; i++)
        for (short j = 0; j < 10; j++)
        {
            cell[i][j] = {
                {i, j},
                Empty,
                {}};
        }
    validCountFor[Black] = validCountFor[White] = 0;

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
short Board::operator ()(const Status &stat) { return statusCount[stat]; }
short Board::operator ()(const bool &flag) { return statusCount[flag]; }
bool Board::operator ==(const Status &stat)const { return int(sideFlag) == stat; }
void Board::operator =(const Board &board)     //need to rewrite
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            cell[i][j] = board.cell[i][j];

    //validCountFor[Black] = board.validCountFor[Black];
    //validCountFor[White] = board.validCountFor[White];

    passFlag[Black] = board.passFlag[Black];
    passFlag[White] = board.passFlag[White];

    //sideFrontier[White] = board.sideFrontier[White];
    //sideFrontier[Black] = board.sideFrontier[Black];
    //allFrontier = board.allFrontier;
    validCoord = board.validCoord;
    //movesRecord = board.movesRecord;

    //for (int i = 0; i < 4; i++)
    //    statusCount[i] = board(Status(i));

    //aValue[White] = board.aValue[White];
    //aValue[Black] = board.aValue[Black];
    sideFlag = board.sideFlag;
}
bool Board::operator ~()const { return Status(sideFlag); }
bool Board::operator !()const { return Status(!sideFlag); }


void Board::init()
{
    srand(unsigned(clock()));

    clear();
    cell[4][4].stat = cell[5][5].stat = White;
    cell[4][5].stat = cell[5][4].stat = Black;
    setValid_fast();
    count();
}

//member functions
void Board::clear()
{
    for (short i = 0; i < 10; i++)
        for (short j = 0; j < 10; j++)
        {
            cell[i][j] = {
                {i, j},
                Empty,
                {}};
        }

    validCountFor[Black] = validCountFor[White] = 0;
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
    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++)
        {
            statusCount[Black] += (cell[i][j].stat == Black);
            statusCount[White] += (cell[i][j].stat == White);
            statusCount[Empty] += (cell[i][j].stat >= Empty);
        }
}

void Board::setFrontierFor(const bool& side)
{
    sideFrontier[side].clear();
    for (short i = 1; i <= 8; i++)
        for (short j = 1; j <= 8; j++)
            if (cell[i][j].stat == Status(side))
                for (int d = 0; d < 8; d++)
                {
                    short x = i + dir[d][0];
                    short y = j + dir[d][1];
                    if (inRange(x, y) && (cell[x][y].stat >= Empty))
                        sideFrontier[side].insert(cell[x][y].coord);
                }
}

void Board::setFrontier()
{
    setFrontierFor(sideFlag);
    setFrontierFor(!sideFlag);
    allFrontier.clear();
    set_union(sideFrontier[sideFlag].begin(), sideFrontier[sideFlag].end(), sideFrontier[!sideFlag].begin(), sideFrontier[!sideFlag].end(), inserter(allFrontier, allFrontier.begin()));
}

bool Board::isValid(const Coord &pos, const bool& side)
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

bool Board::isValid_fast(const Coord &pos, const bool& side)
{
    bool R = false;
    for (int i = 0; i < 8; i++)
    {
        short x = pos.x, y = pos.y;
        cell[x][y].validDir[i] = false;

        short nx = x + dir[i][0], ny = y + dir[i][1];
        if (cell[nx][ny].stat == Status(!side))
        {
            for (int p = nx, q = ny; ; p += dir[i][0], q += dir[i][1])
            {
                if (cell[p][q].stat == Status(!side))
                    continue;
                if (cell[p][q].stat >= Empty)
                {
                    cell[x][y].validDir[i] = false;
                    break;
                }
                if (cell[p][q].stat == Status(side))
                {
                    cell[x][y].validDir[i] = true;
                    R = true;
                    break;
                }
            }
        }
    }
    return R;
}

void Board::setValid()
{
    setFrontier();
    validCoord.clear();
    statusCount[Valid] = 0;
    validCountFor[Black] = validCountFor[White] = 0;
    for (auto coord : allFrontier)
    {
        short x = coord.x;
        short y = coord.y;
        if (isValid(coord, sideFlag))
        {
            cell[x][y].stat = Valid;
            statusCount[Valid]++;
            validCountFor[sideFlag]++;
            validCoord.push_back(cell[x][y].coord);
        }
        else
        {
            cell[x][y].stat = Empty;
            if (isValid(coord, !sideFlag))
                validCountFor[!sideFlag]++;
        }
    }
        
    sort(validCoord.begin(), validCoord.end(), cmpCoord);
}

void Board::setValid_fast()
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
        if (isValid_fast(tmpCoord, sideFlag))
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

void Board::move(const Coord &pos)
{
    if (pos.x == -1 && pos.y == -1)
        passFlag[sideFlag] = true;

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

void Board::fastmove(const Coord &pos)
{
    for (int i = 0; i < 8; i++)
    {
        short x = pos.x, y = pos.y;
        if (cell[x][y].validDir[i])
        {
            do
            {
                cell[x][y].stat = Status(sideFlag);
                x += dir[i][0];
                y += dir[i][1];
            } while (cell[x][y].stat == Status(!sideFlag));
        }
    }

    flipSide();
    setValid_fast();
    count();
}

#ifdef _WIN32
void Board::print()
{
    if (!Game::debugFlag)
    {
        SLP(1);
        CLS;
    }
    cout << endl;
    cout << Game::mainLang.rnd << movesRecord.size() + 1 << Game::mainLang.rnd1 << ", " << (sideFlag ? Game::mainLang.blk : Game::mainLang.wht) << Game::mainLang.trn << endll;
    cout << "      ";
    for (int i = 1; i <= 8; i++)
        cout << char('@' + i) << "   ";

    cout << endl << "    ┌─┬─┬─┬─┬─┬─┬─┬─┐" << endl;

    for (int i = 1; i <= 8; i++)
    {
        cout << "   " << i << "│";
        for (int j = 1; j <= 8; j++)
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
                    if ((Game::assistFlag && ((Game::AIFlag && sideFlag == Game::humanSide) || !Game::AIFlag)) || Game::autoFlag)
                        cout << "╋│";
                    else
                        cout << "  │";
                    break;
                default:
                    fatalError(1);
            }
        }
        if (i - 8)
            cout << endl << "    ├─┼─┼─┼─┼─┼─┼─┼─┤";
        else
            cout << endl << "    └─┴─┴─┴─┴─┴─┴─┴─┘";
        if (i - 8) cout << endl;
    }
    cout << endl << left << "       "
        << Game::mainLang.blk << "(●):" << setw(2) << statusCount[Black] << "    "
        << Game::mainLang.wht << "(○):" << setw(2) << statusCount[White] << endl;

    if (movesRecord.size() && Game::AIFlag && sideFlag == Game::humanSide && !Game::AIPass && !Game::autoFlag)
    {
        if (Game::debugFlag)
        {
            ofstream out("timecsm.txt", ios::app);
            out << Game::mainLang.aps
                << movesRecord[movesRecord.size() - 1].x
                << char(movesRecord[movesRecord.size() - 1].y + '@')
                << Game::mainLang.aps1
                << endl
                << Game::mainLang.tmcsm1
                << double(clock() - startTime) / CLOCKS_PER_SEC
                << Game::mainLang.tmcsm
                << endll;
            out.close();
        }
        cout << endl << "        "
            << Game::mainLang.aps
            << movesRecord[movesRecord.size() - 1].x
            << char(movesRecord[movesRecord.size() - 1].y + '@')
            << Game::mainLang.aps1
            << endl << "          "
            << Game::mainLang.tmcsm1
            << double(clock() - startTime) / CLOCKS_PER_SEC
            << Game::mainLang.tmcsm
            << endll;
    }
    else cout << endll;
}

#else
void Board::print()
{
    if (!Game::debugFlag)
    {
        SLP(1);
        CLS;
    }
    cout << endl;
    cout << Game::mainLang.rnd << movesRecord.size() + 1 << Game::mainLang.rnd1 << ", " << (sideFlag ? Game::mainLang.blk : Game::mainLang.wht) << Game::mainLang.trn << endll;
    cout << "      ";
    for (int i = 1; i <= 8; i++)
        cout << char('@' + i) << "   ";

    cout << endl << "    ┌───┬───┬───┬───┬───┬───┬───┬───┐" << endl;

    for (int i = 1; i <= 8; i++)
    {
        cout << "   " << i << "│";
        for (int j = 1; j <= 8; j++)
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
                    if (Game::assistFlag && ((Game::AIFlag == AI_MODE&&sideFlag == Game::humanSide) || (Game::AIFlag == NON_AI_MODE)))
                        cout << " ╋ │";
                    else
                        cout << "   │";
                    break;
                default:
                    fatalError(1);
            }
        }
        if (i - 8)
            cout << endl << "    ├───┼───┼───┼───┼───┼───┼───┼───┤";
        else
            cout << endl << "    └───┴───┴───┴───┴───┴───┴───┴───┘";
        if (i - 8) cout << endl;
    }
    cout << endl << left << "       "
        << Game::mainLang.blk << "(●):" << setw(2) << statusCount[Black] << "    "
        << Game::mainLang.wht << "(○):" << setw(2) << statusCount[White] << endl;

    if (movesRecord.size() && Game::AIFlag && sideFlag == Game::humanSide && !Game::AIPass && !Game::autoFlag)
    {
        if (Game::debugFlag)
        {
            ofstream out("timecsm.txt", ios::app);
            out << Game::mainLang.aps
                << movesRecord[movesRecord.size() - 1].x
                << char(movesRecord[movesRecord.size() - 1].y + '@')
                << Game::mainLang.aps1
                << endl
                << Game::mainLang.tmcsm1
                << double(clock() - startTime) / CLOCKS_PER_SEC
                << Game::mainLang.tmcsm
                << endll;
            out.close();
        }
        cout << endl << "        "
            << Game::mainLang.aps
            << movesRecord[movesRecord.size() - 1].x
            << char(movesRecord[movesRecord.size() - 1].y + '@')
            << Game::mainLang.aps1
            << endl << "          "
            << Game::mainLang.tmcsm1
            << double(clock() - startTime) / CLOCKS_PER_SEC
            << Game::mainLang.tmcsm
            << endll;
    }
    else cout << endll;
}

#endif

void Board::recordPrint()
{
    cout << Game::mainLang.gmrcd << endll;
    for (unsigned i = 0; i < movesRecord.size(); i++)
        if (movesRecord[i].x != -1)
            cout << movesRecord[i].x << char(movesRecord[i].y + '@') << ' ';
        else
            cout << Game::mainLang.pass << ' ';
    cout << endl;
}

double Board::allEvalFor(const bool& side) //Evaluation for all cells of the side
{
    int aval = 0;
    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++)
            if (cell[i][j].stat == Status(side))
                aval += coordValue[i][j];

    aValue[side] = aval;
    return aValue[side];
}

bool Board::save(string saveName)
{
    ofstream save(saveName+".save",ios::binary);
    if (!save)
    {
        cout << Game::mainLang.savefl;
        PAUSE;
        return false;
    }

    save << Game::AIFlag << endl;
    save << Game::assistFlag << endl;
    save << Game::humanSide << endl;
    save << Game::diff << endl << endl;
    save << movesRecord.size() << endl;
    for (unsigned i = 0; i < movesRecord.size(); i++)
        save << movesRecord[i].x << ' '
        << movesRecord[i].y << endl << endl;
    save.close();

    ifstream load(saveName + ".save");
    ofstream hsave(saveName + ".hash");
    if (!load || !hsave)
    {
        cout << Game::mainLang.savefl;
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

bool Board::load(string loadName, int undoSteps)
{
    CLS;
    ifstream load(loadName + ".save", ios::binary);
    ifstream hload(loadName + ".hash");
    ostringstream sload, hsload;
    if (!load || !hload || !sload)
    {
        cout << Game::mainLang.loadfl << endl;
        cout << Game::mainLang.gotomain;
        PAUSE;
        return false;
    }

    hash<string> hashptr;
    hsload << hload.rdbuf();
    sload << load.rdbuf();

    string saveHash = hsload.str();
    string file = sload.str();

    ostringstream convert;
    convert << hashptr(file);
    string fileHash = convert.str();

    if (fileHash != saveHash)
    {
        cout << Game::mainLang.savedmg << endl;
        cout << Game::mainLang.gotomain;
        PAUSE;
        return false;
    }
    load.close();
    hload.close();

    Game::board.init();

    load.open(loadName + ".save");

    load >> Game::AIFlag;
    load >> Game::assistFlag;
    load >> Game::humanSide;
    load >> Game::diff;

    if (Game::diff)
        AchillesInit(Game::diff);

    int movesCount;
    load >> movesCount;
    movesCount -= undoSteps;
    Game::board.movesRecord.clear();

    for (int i = 0; i < movesCount; i++)
    {
        Coord tmpCoord{};
        load >> tmpCoord.x;
        load >> tmpCoord.y;
        Game::board.move(tmpCoord);
    }
    load.close();

    print();

    return true;
}

void Board::undo()
{
    save("undoTmp");
    load("undoTmp", Game::AIFlag + 1);
}