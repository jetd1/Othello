#ifndef ELMTS_H
#define ELMTS_H

#include "base.h"
#include <set>

extern const short coordValue[10][10];

enum playerType { Human, AI };
enum Status { White, Black, Empty, Valid };    //Then status<Empty: Have Stone on It, status>=Empty: Truly Empty
                                               //White=false & Black=true
enum language { en_us, zh_cn, zh_tw, zh_wy, jp, fr, es };

enum gameStatus { Idle, Playing, End, Pause, Lifting };

class Coord
{
public:
    short x;
    short y;
    bool operator <(const Coord coord)const
    {
        if (*this == coord)
            return false;
        else if (coordValue[x][y]!= coordValue[coord.x][coord.y])
            return coordValue[x][y] > coordValue[coord.x][coord.y];
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
    short validDir[8];
};


class Board
{
private:
    bool sideFlag;
    short statusCount[4];
    Cell cell[10][10];

public:   
    bool passFlag[2];
    short validCountFor[2];
    set<Coord> sideFrontier[2];
    set<Coord> allFrontier;
    vector<Coord> validCoord;
    vector<Coord> movesRecord;
    double aValue[2];
    

public:
    Board();

    void operator =(const Board&);
    bool operator ==(const Status&)const;
    bool operator !()const;
    bool operator ~()const;
    Cell* operator [](int);
    short operator ()(const Status&);
    short operator ()(const bool&);

    void init();
    void clear();
    void flipSide();
    void count();
    bool isValid(const Coord&, const bool&);
    bool isValid_fast(const Coord&, const bool&);
    void setFrontier();
    void setFrontierFor(const bool&);
    void setValid();
    void setValid_fast();
    void move(const Coord&);
    void fastmove(const Coord&);
    void print();
    void recordPrint();

    void undo();

    double allEvalFor(const bool&);

    bool save(string saveName = "Othello");
    bool load(string loadName = "Othello", int UndoSteps = 0);

    //todo
    void colorReverse();
    void randomize();

    inline bool end()
    {
        return (!statusCount[Empty] || !statusCount[Black] || !statusCount[White] || (passFlag[Black] && passFlag[White]));
    }

    inline int isWin(bool side)
    {
        return (end() && (statusCount[side] > statusCount[!side])) ? statusCount[side] - statusCount[!side] : 0;
    }

    inline bool inRange(int p, int q) { return p >= 1 && p <= 8 && q >= 1 && q <= 8; }
};

class langStrings
{
public:
    string stitle;
    char title[30];
    string verl1;
    string verl2;
    string verl3;
    string verl4;
    string menu1;
    string menu2;
    string menu3;
    string menu41;
    string menu42;
    string menu5;
    string menu6;
    string menu7;
    string menu8;
    string menu0;
    string sglipt;
    string guion;
    string atplbs;
    string atplws;
    string ivldipt;
    string sidesel;
    string dif[5];
    string isass;
    string seltheme;
    string theme[10];
    string rdmtheme;
    string triipt;
    string sts[4];
    string themenspt;
    string rnd;
    string rnd1;
    string blk;
    string wht;
    string trn;
    string aps;
    string aps1;
    string tmcsm1;
    string tmcsm;
    string gmrcd;
    string pass;
    string savefl;
    string savess;
    string savedmg;
    string gotomainspc;
    string loadfl;
    string gotomain;
    string err[2];
    string ytrn1;
    string ytrn2;
    string btrn;
    string wtrn;
    string nposm;
    string aipass;
    string ip;
    string aithink;
    string dftai;
    string toosimple;
    string tieai;
    string tie;
    string win;


    void setLangStrings(language langFlag);
    void printVersion();
    void printMenu();
    void help();
    
    void EN_US();
    void ZH_CN();
    void ZH_TW();
};

class Stone
{
private:
    Status color;
    double x, y, z;
    double vx, vy, vz;
    double angle, vangle;
    double axisx, axisy, axisz;

public:
    Stone(): color(Black), x(0.0), y(0.0), z(0.0), vx(0.0), vy(0.0), vz(0.0), angle(0.0), vangle(0.0), axisx(0.0), axisy(0.0), axisz(1.0) {};
    Stone(Cell p);
    Status getColor() { return color; }
    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
    double getAngle() { return angle; }
    double getAxisx() { return axisx; }
    double getAxisy() { return axisy; }
    double getAxisz() { return axisz; }

    void fly();
    void move(double dt);
    void print();
};

class Game
{
public:
    static Board board;
    static Coord inputCoord;
    const static Coord passCoord;

    static short diff;
    static short maxDepth;
    static bool AIFlag;
    static bool UIFlag;
    static bool debugFlag;
    static bool assistFlag;
    static bool inputFlag;
    static bool humanSide;
    static bool saveSuccess;
    static bool manualFlag;
    static bool randomFlag;
    static bool AIPass;
    static bool autoFlag;
    static bool debugCalled;
    static bool finalSearch;
    static double AchillesReturn;

    static gameStatus status;

    static language langFlag;
    static langStrings mainLang;

    static bool liftTheTable();
};

#endif
