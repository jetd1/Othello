#include "elements.h"
#include <iomanip>

extern bool inRange(int p, int q);
extern void fatalError(unsigned ErrorCode);

extern short dir[8][2];
extern Cell NULLCELL[SAFE_LENGTH][SAFE_LENGTH];
extern short NULLCOUNT[4];
extern bool assistFlag, modeFlag, sideFlag, playerSide;

Board::Board()
{
    memcpy((Cell*)cell, (Cell*)NULLCELL, sizeof(Cell)*SAFE_LENGTH*SAFE_LENGTH);
    memcpy(statusCount, NULLCOUNT, sizeof(short) * 4);
    value = 0;
}

Cell* Board::operator [](int i)
{
    return cell[i];
}

void Board::operator =(Board &board)
{
    board.count();
    memcpy((Cell*)cell, (Cell*)board.cell, sizeof(Cell)*SAFE_LENGTH*SAFE_LENGTH);
    memcpy(statusCount, board.statusCount, sizeof(short) * 4);
    value = board.value;
}

bool Board::operator >(Board &board) { return value > board.value; }
bool Board::operator <(Board &board) { return value < board.value; }
bool Board::operator ==(Board &board) { return value == board.value; }


void Board::count()
{
    statusCount[Black] = statusCount[White] = statusCount[Empty] = 0;
    for (int i = 1; i <= SIDE_LENGTH; i++) for (int j = 1; j <= SIDE_LENGTH; j++)
    {
        statusCount[Black] += (cell[i][j].stat == Black);
        statusCount[White] += (cell[i][j].stat == White);
        statusCount[Empty] += (cell[i][j].stat >= Empty);
    }
}

short Board::count(status stat)
{
    statusCount[stat] = 0;
    for (int i = 1; i <= SIDE_LENGTH; i++) for (int j = 1; j <= SIDE_LENGTH; j++)
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
    for (int i = 1; i <= SIDE_LENGTH; i++) for (int j = 1; j <= SIDE_LENGTH; j++)
    {
        if (cell[i][j].stat <= Black) continue;

        Coord tmpCoord;
        tmpCoord.x = i;
        tmpCoord.y = j;
        if (isValid(tmpCoord, side))
        {
            cell[i][j].stat = Valid;
            statusCount[Valid]++;
            validCoord.push_back(tmpCoord);
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
                    for (int r = p - dx, s = q - dy; cell[r][s].stat != status(side); r -= dx, s -= dy) cell[r][s].stat = status(side);
                    break;
                }
            }
        }
    }
}

void Board::print()
{
    SLP(200);
    CLS;
    cout << " ";
    for (int i = 1; i <= SIDE_LENGTH; i++) cout << ' ' << char('@' + i);
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
                    if (assistFlag && ((modeFlag == AI_MODE&&sideFlag == playerSide) || (modeFlag == NON_AI_MODE))) outTmp = '*';
                    else outTmp = ' ';
                    break;
                default:
                    fatalError(1);
            }
            cout << ' ' << outTmp;
        }
        if (i - SIDE_LENGTH) cout << endl;
    }
    cout << endl << left << "Black(X):" << setw(2) << statusCount[Black] << "  White(O):" << setw(2) << statusCount[White] << endl << endl;
}

