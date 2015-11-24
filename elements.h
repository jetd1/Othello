#ifndef ELMTS_H
#define ELMTS_H

#include "base.h"

enum getType { Player, Computer };
enum Status { White, Black, Empty, Valid };    //Then status<Empty: Have Stone on It, status>=Empty: Truly Empty
                                               //White=false & Black=true

struct Coord
{
    short x;
    short y;
    short value;     //Characteristic Value (Fixed to Position)
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
    vector<Coord> validCoord;
    vector<Coord> movesRecord;
    double vValue;
    double aValue[2];
    

public:
    Board();

    void operator =(Board &board);
    bool operator >(const Board &board)const;
    bool operator <(const Board &board)const;
    bool operator ==(const Board &board)const;
    bool operator ==(const Status &stat)const;
    bool operator >=(const Board &board)const;
    bool operator <=(const Board &board)const;
    Status operator !()const;
    Status operator ~()const;
    Cell* operator [](int i);
    short operator ()(Status stat);
    short operator ()(bool flag);

    void clear();
    void cellclear();
    void flipSide();
    void count();
    short count(Status stat);
    bool isValid(Coord &pos, bool side);
    void setValid();
    void setValidFor(bool side);
    void move(Coord &pos);
    void print();


    double validEval(bool side);
    double allEval(bool side);
    short frontierCount(bool side);

    double aEvalRate(bool side);
    double aEvalDiff(bool side);
    double CountRate(bool side);
    double CountDiff(bool side);
    double frontierCountRate(bool side);
    double frontierCountDiff(bool side);
    short countValidFor(bool side);
    bool save(string saveName = "Othello");

    //todo
    void colorReverse();
    void randomize();
};

#endif
