#include "base.h"
#include "extern.h"

bool isValid(sBoard &board, Coord &pos, bool side)
{
    if (board.cell[pos.x][pos.y].stat < Empty) return false;
    for (int i = 0; i < 8; i++)
    {
        short dx = dir[i][0], dy = dir[i][1];
        if (board.cell[pos.x + dx][pos.y + dy].stat == !side)
        {
            for (int p = pos.x + dx, q = pos.y + dy; inRange(p, q); p += dx, q += dy)
            {
                if (board.cell[p][q].stat >= Empty) break;
                if (board.cell[p][q].stat == int(side)) return true;
            }
        }
    }
    return false;
}

void setValid(sBoard &board, bool side)
{
    validCoord.clear();
    board.statusCount[Valid] = 0;
    for (int i = 1; i <= SIDE_LENGTH; i++) for (int j = 1; j <= SIDE_LENGTH; j++)
    {
        if (board.cell[i][j].stat <= Black) continue;

        Coord tmpCoord;
        tmpCoord.x = i;
        tmpCoord.y = j;
        if (isValid(board, tmpCoord, side))
        {
            board.cell[i][j].stat = Valid;
            board.statusCount[Valid]++;
            validCoord.push_back(tmpCoord);
        }
        else board.cell[i][j].stat = Empty;
    }
}

void count(sBoard &board)
{
    board.statusCount[Black] = board.statusCount[White] = board.statusCount[Empty] = 0;
    for (int i = 1; i <= SIDE_LENGTH; i++) for (int j = 1; j <= SIDE_LENGTH; j++)
    {
        board.statusCount[Black] += (board.cell[i][j].stat == Black);
        board.statusCount[White] += (board.cell[i][j].stat == White);
        board.statusCount[Empty] += (board.cell[i][j].stat >= Empty);
    }
}

void move(sBoard &board, Coord &pos, bool side)
{
    for (int i = 0; i < 8; i++)
    {
        int dx = dir[i][0], dy = dir[i][1];
        if (board.cell[pos.x + dx][pos.y + dy].stat == !side)
        {
            for (int p = pos.x + dx, q = pos.y + dy; inRange(p, q); p += dx, q += dy)
            {
                if (board.cell[p][q].stat>= Empty) break;
                if (board.cell[p][q].stat == status(side))
                {
                    board.cell[pos.x][pos.y].stat = status(side);
                    for (int r = p - dx, s = q - dy; board.cell[r][s].stat != status(side); r -= dx, s -= dy) board.cell[r][s].stat = status(side);
                    break;
                }
            }
        }
    }
}

inline bool inRange(int p, int q)
{
    return p >= 1 && p <= SIDE_LENGTH && q >= 1 && q <= SIDE_LENGTH;
}

void judge()
{
    if (modeFlag == AI_MODE)
    {
        if (gameBoard.statusCount[playerSide] > gameBoard.statusCount[!playerSide]) cout << "You Defeated Computer! Congratulations!" << endl << endl;
        else if (gameBoard.statusCount[playerSide] < gameBoard.statusCount[!playerSide]) cout << "Too Young too Simple!" << endl << endl;
        else cout << "Tie! But Liangchen Want to Play Again With You." << endl << endl;
    }
    else
    {
        if (gameBoard.statusCount[Black] > gameBoard.statusCount[White] || !gameBoard.statusCount[White]) cout << "Black Win!" << endl << endl;
        else if (gameBoard.statusCount[Black] < gameBoard.statusCount[White] || !gameBoard.statusCount[Black]) cout << "White Win!" << endl << endl;
        else cout << "Tie!" << endl << endl;
    }
}