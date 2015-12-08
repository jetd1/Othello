#ifndef ELMTS_H
#define ELMTS_H

#include "base.h"
#include <set>

enum playerType { Human, AI };
enum Status { White, Black, Empty, Valid };    //Then status<Empty: Have Stone on It, status>=Empty: Truly Empty
                                               //White=false & Black=true

class Coord
{
public:
    short x;
    short y;
    short value;     //Characteristic Value (Fixed to Position)
    bool operator <(const Coord coord)const
    {
        if (*this == coord)
            return false;
        else if (value != coord.value)
            return value > coord.value;
        else if (x != coord.x)
            return x > coord.x;
        else
            return y > coord.y;
    }
    bool operator ==(const Coord coord)const { return x == coord.x&&y == coord.y; }
};

struct Cell
{
    Coord coord;
    Status stat;
};


class Board
{
private:
    bool sideFlag;
    short statusCount[4];
    Cell cell[SAFE_LENGTH][SAFE_LENGTH];

public:   
    bool passFlag[2];
    short validCountFor[2];
    short passCount;
    set<Coord> sideFrontier[2];
    set<Coord> allFrontier;
    vector<Coord> validCoord;
    vector<Coord> movesRecord;
    double aValue[2];
    

public:
    Board();

    void operator =(Board&);
    bool operator ==(const Status&)const;
    bool operator !()const;
    bool operator ~()const;
    Cell* operator [](int);
    short operator ()(Status);
    short operator ()(bool);

    void clear();
    void flipSide();
    void count();
    bool isValid(Coord&, bool);
    void setFrontier();
    void setFrontierFor(bool);
    void setValid();
    void move(Coord&);
    void print();
    void recordPrint();

    double allEvalFor(bool);

    bool save(string saveName = "Othello");

    //todo
    void colorReverse();
    void randomize();

    inline bool Board::end()
    {
        return (!statusCount[Empty] || !statusCount[Black] || !statusCount[White] || (passFlag[Black] && passFlag[White]));
    }

    inline int Board::isWin(bool side)
    {
        return (end() && (statusCount[side] > statusCount[!side])) ? statusCount[side] - statusCount[!side] : 0;
    }

    inline bool Board::inRange(int p, int q) { return p >= 1 && p <= SIDE_LENGTH && q >= 1 && q <= SIDE_LENGTH; }
};


#endif
