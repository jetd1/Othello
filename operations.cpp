#include "base.h"
#include "extern.h"

bool isValid(Coord pos, bool side, Cell board[SAFE_LENGTH][SAFE_LENGTH])
{
    if (board[pos.x][pos.y].stat < Empty) return false;
    for (int i = 0; i < 8; i++)
    {
        int dx = dir[i][0], dy = dir[i][1];
        if (board[pos.x + dx][pos.y + dy].stat == !side)
        {
            for (int p = pos.x + dx, q = pos.y + dy; inRange(p, q); p += dx, q += dy)
            {
                if (board[p][q].stat >= Empty) break;
                if (board[p][q].stat == int(side)) return true;
            }
        }
    }
    return false;
}

void setValid(Cell board[SAFE_LENGTH][SAFE_LENGTH], bool side)
{
    validCoord.clear();
    stoneCount[Valid] = 0;
    for (int i = 1; i <= SIDE_LENGTH; i++) for (int j = 1; j <= SIDE_LENGTH; j++)
    {
        if (board[i][j].stat <= Black) continue;

        Coord tmpCoord;
        tmpCoord.x = i;
        tmpCoord.y = j;
        if (isValid(tmpCoord, side, board))
        {
            board[i][j].stat = Valid;
            stoneCount[Valid]++;
            validCoord.push_back(tmpCoord);
        }
        else board[i][j].stat = Empty;
    }
}

void count(Cell board[SAFE_LENGTH][SAFE_LENGTH])
{
    stoneCount[Black] = stoneCount[White] = stoneCount[Empty] = 0;
    for (int i = 1; i <= SIDE_LENGTH; i++) for (int j = 1; j <= SIDE_LENGTH; j++)
    {
        stoneCount[Black] += (board[i][j].stat == Black);
        stoneCount[White] += (board[i][j].stat == White);
        stoneCount[Empty] += (board[i][j].stat >= Empty);
    }
}

void move(Coord pos, Cell board[SAFE_LENGTH][SAFE_LENGTH])
{
    for (int i = 0; i < 8; i++)
    {
        int dx = dir[i][0], dy = dir[i][1];
        if (board[pos.x + dx][pos.y + dy].stat == !sideFlag)
        {
            for (int p = pos.x + dx, q = pos.y + dy; inRange(p, q); p += dx, q += dy)
            {
                if (board[p][q].stat>= Empty) break;
                if (board[p][q].stat == status(sideFlag))
                {
                    board[pos.x][pos.y].stat = status(sideFlag);
                    for (int r = p - dx, s = q - dy; board[r][s].stat != status(sideFlag); r -= dx, s -= dy) board[r][s].stat = status(sideFlag);
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
    if (modeFlag)
    {
        if (stoneCount[playerSide] > stoneCount[!playerSide]) cout << "You Defeated Computer! Congratulations!" << endl << endl;
        else if (stoneCount[playerSide] < stoneCount[!playerSide]) cout << "Too Young too Simple!" << endl << endl;
        else cout << "Tie! But Liangchen Want to Play Again With You." << endl << endl;
    }
    else
    {
        if (stoneCount[Black] > stoneCount[White] || !stoneCount[White]) cout << "Black Win!" << endl << endl;
        else if (stoneCount[Black] < stoneCount[White] || !stoneCount[Black]) cout << "White Win!" << endl << endl;
        else cout << "Tie!" << endl << endl;
    }
}