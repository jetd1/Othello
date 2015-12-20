#include <iostream>
#include "elements.h"

using std::string;

void langStrings::setLangStrings(language langFlag)
{
    switch (langFlag)
    {
        case en_us:
            EN_US();
            break;
        case zh_cn:
            ZH_CN();
            break;
        case zh_tw:
            ZH_TW();
            break;
        case zh_wy:
            break;
        case jp:
            break;
        case fr:
            break;
        case es:
            break;
        default:
            break;
    }
}

void langStrings::EN_US()
{
    stitle = "title=JetOthello";
    for (int i = 0; i < stitle.length(); i++)
        title[i] = stitle[i];
    title[stitle.length()] = '\0';

    verl1 = "Othello Main Version ";
    verl2 = "Achilles Version ";
    verl3 = "Copyleft 2015";
    verl4 = "By Jet";

    menu1 = "1.Play with Friends";
    menu2 = "2.Play with Achilles";
    menu3 = "3.Achilles Auto Play";
    menu41 = "4.Turn Off GUI";
    menu42 = "4.Turn On GUI";
    menu5 = "5.Load Game";
    menu6 = "6.Settings";
    menu7 = "7.Instructions";
    menu0 = "0.Exit";

    sglipt = "Input:_\b";

    guion = "GUI Mode On";

    atplbs = "Please Set Mode of Achilles Playing Black";
    atplws = "Please Set Mode of Achilles Playing White";

    ivldipt = "Invalid Input!!!";

    sidesel = "Play Black or White?(B/W):_\b";

    dif[0] = "1.Dumb Mode";
    dif[1] = "2.Easy Mode";
    dif[2] = "3.Normal Mode";
    dif[3] = "4.Hard Mode";
    dif[4] = "5.Call Police Mode";

    isass = "Do You Want Any Assistance When Placing the Stone?(Y/N):_\b";

    seltheme = "Please Select Theme:";
    theme[0] = "0.Default (White on Black)";
    theme[1] = "1.Reverse (Black on White)";
    theme[2] = "2.Borland (Yellow on Blue) ";
    theme[3] = "3.BlueScreen (White on Blue)";
    theme[4] = "4.Geek (Green on Black)";
    theme[5] = "5.Glamorous (Blue on Purple)";
    theme[6] = "6.Pinky (Yellow on Pink)";
    theme[7] = "7.Yima (White on Red)";
    theme[8] = "8.DiDiaoYiMa (Red on Black)";
    theme[9] = "9.Dragon (Yellow on Dark Red)";
    rdmtheme = "Input JET to Randomize the Theme.";
    triipt = "Input:___\b\b\b";

    sts[0] = "1.Select Console Theme";
    sts[1] = "2.Select Language";
    sts[2] = "3.Assistance Setting";
    sts[3] = "0.Back to Main Menu";

    themenspt = "Sorry, Theme Changing Only Support in Windows...";

    rnd = "          Round ";
    rnd1.clear();
    blk = "Black";
    wht = "White";
    trn = "'s Turn";
    aps = "Achilles Placed a Stone at ";
    aps1.clear();
    tmcsm1.clear();
    tmcsm = " Seconds Consumed.";

    gmrcd = "Game Record:";
    pass = "PASS";

    savefl = "    Unable to Save, Game Will Now Resume!";
    savedmg = "Saved File Damaged!";
    savess = "         Game Successfully Saved!";
    gotomainspc = "       ";
    loadfl = "Unable to Open Saved File!";

    gotomain = "Press Any Key to Main Menu...";

    ytrn1 = "            Your(●) Turn:__\b\b";
    ytrn2 = "            Your(○) Turn:__\b\b";

    btrn = "           Black(●) Turn:__\b\b";
    wtrn = "           White(○) Turn:__\b\b";

    nposm = "      No Possible Move, Enter to Pass!";
    aipass = "      Achilles Passed, Enter to Your Turn!";

    ip = "       Invalid Position! Your input is ";

    aithink = "            Achilles Thinking ...";

    dftai = "    You Defeated Achilles! Congratulations!";
    toosimple = "           Too Young Too Simple!";
    tieai = "Tie!";
    tie = "Tie!";
    win = "Win!";
}

void langStrings::ZH_CN()
{
    stitle = "title=张小帅的黑白棋";
    for (int i = 0; i < stitle.length(); i++)
        title[i] = stitle[i];
    title[stitle.length()] = '\0';

    verl1 = "黑白棋主程序版本 ";
    verl2 = "Achilles版本 ";
    verl3 = "Copyleft 2015";
    verl4 = "By 张小帅";

    menu1 = "1.和朋友一起玩儿（PvP）";
    menu2 = "2.和Achilles玩儿（PvAI）";
    menu3 = "3.看Achilles自己玩儿（AIvAI）";
    menu41 = "4.关闭图形界面";
    menu42 = "4.打开图形界面";
    menu5 = "5.加载游戏";
    menu6 = "6.游戏设置";
    menu7 = "7.帮助";
    menu0 = "0.退出游戏";

    sglipt = "请输入:_\b";

    guion = "图形界面已打开";

    atplbs = "请选择黑方Achilles模式";
    atplws = "请选择白方Achilles模式";

    ivldipt = "输入不正确!!!";

    sidesel = "你要执黑还是执白？(B/W):_\b";

    dif[0] = "1.陈泽坤模式";
    dif[1] = "2.简单模式";
    dif[2] = "3.正常模式";
    dif[3] = "4.困难模式";
    dif[4] = "5.报警模式";

    isass = "下棋时需要提示可行位置吗？(Y/N):_\b";

    seltheme = "请选择主题：";
    theme[0] = "0.默认主题 (白/黑)";
    theme[1] = "1.反色 (黑/白)";
    theme[2] = "2.波尔兰德 (浅黄/蓝) ";
    theme[3] = "3.蓝屏 (白/蓝)";
    theme[4] = "4.极客 (绿/黑)";
    theme[5] = "5.格拉莫萝丝 (蓝/紫)";
    theme[6] = "6.粉嫩 (黄/粉)";
    theme[7] = "7.姨妈 (白/红)";
    theme[8] = "8.低调姨妈 (红/黑)";
    theme[9] = "9.龙 (黄/红)（推荐）";
    rdmtheme = "键入 JET 以获得随机化主题.";
    triipt = "输入:___\b\b\b";

    sts[0] = "1.选择命令行主题";
    sts[1] = "2.选择语言";
    sts[2] = "3.辅助模式开关";
    sts[3] = "0.返回主菜单";

    themenspt = "很抱歉，更换主题功能只能在Windows下使用...";

    rnd = "             第";
    rnd1 = "轮";
    blk = "黑方";
    wht = "白方";
    trn = "回合";
    aps = "   Achilles在 ";
    aps1 = " 处着子";
    tmcsm1 = "    耗时";
    tmcsm = " 秒.";

    gmrcd = "游戏记录:";
    pass = "PASS";

    savefl = "         保存失败，游戏将继续！";
    savedmg = "存档文件损坏";
    savess = "               游戏成功保存";
    gotomainspc = "           ";
    loadfl = "无法打开存档文件！";

    gotomain = "按任意键回到主菜单...";

    ytrn1 = "             你(●) 的回合:__\b\b";
    ytrn2 = "             你(○) 的回合:__\b\b";

    btrn = "            黑棋(●) 的回合:__\b\b";
    wtrn = "            白棋(○) 的回合:__\b\b";

    nposm = "        您无子可下，按回车以跳过回合";
    aipass = "  Achilles 跳过了回合, 按回车来进入你的回合";

    ip = "           该位置不能着子，您输入的是 ";

    aithink = "           Achilles 正在思考 ...";

    dftai = "            你打败了 Achilles! NB!";
    toosimple = "        Too Young Too Simple!";
    tieai = "                    平局！";
    tie = "平局!";
    win = "获胜!";

}


void langStrings::ZH_TW()
{
    stitle = "title=張大帥的黑白棋";
    for (int i = 0; i < stitle.length(); i++)
        title[i] = stitle[i];
    title[stitle.length()] = '\0';

    verl1 = "黑白棋主程式版本 ";
    verl2 = "Achilles版本 ";
    verl3 = "Copyleft 2015";
    verl4 = "By 張大帥";

    menu1 = "1.和朋友一起玩（PvP）";
    menu2 = "2.和Achilles玩（PvAI）";
    menu3 = "3.看Achilles自己玩（AIvAI）";
    menu41 = "4.關閉圖形介面";
    menu42 = "4.打開圖形介面";
    menu5 = "5.載入遊戲";
    menu6 = "6.遊戲設置";
    menu7 = "7.幫助";
    menu0 = "0.退出遊戲";

    sglipt = "請輸入:_\b";

    guion = "圖形介面已打開";

    atplbs = "請選擇黑方Achilles模式";
    atplws = "請選擇白方Achilles模式";

    ivldipt = "輸入不正確!!!";

    sidesel = "你想執黑還是執白？(B/W):_\b";

    dif[0] = "1.陸一平模式";
    dif[1] = "2.簡單模式";
    dif[2] = "3.正常模式";
    dif[3] = "4.困難模式";
    dif[4] = "5.報警模式";

    isass = "下棋時需要提示可行位置嗎？(Y/N):_\b";

    seltheme = "請選擇主題：";
    theme[0] = "0.預設主題 (白/黑)";
    theme[1] = "1.反色 (黑/白)";
    theme[2] = "2.波爾蘭德 (淺黃/藍) ";
    theme[3] = "3.藍屏 (白/藍)";
    theme[4] = "4.極客 (綠/黑)";
    theme[5] = "5.格拉莫蘿絲 (藍/紫)";
    theme[6] = "6.粉嫩 (黃/粉)";
    theme[7] = "7.姨媽 (白/紅)";
    theme[8] = "8.低調姨媽 (紅/黑)";
    theme[9] = "9.龍 (黃/紅)（推薦）";
    rdmtheme = "鍵入 JET 以獲得隨機化主題.";
    triipt = "輸入:___\b\b\b";

    sts[0] = "1.選擇命令列主題";
    sts[1] = "2.選擇語言";
    sts[2] = "3.輔助模式開關";
    sts[3] = "0.返回主菜單";

    themenspt = "很抱歉，更換主題功能只能在Windows下使用...";

    rnd = "             第";
    rnd1 = "輪";
    blk = "黑方";
    wht = "白方";
    trn = "回合";
    aps = "   Achilles在 ";
    aps1 = " 處著子";
    tmcsm1 = "    耗時";
    tmcsm = " 秒.";

    gmrcd = "遊戲記錄:";
    pass = "PASS";

    savefl = "         保存失敗，遊戲將繼續！";
    savedmg = "存檔文件損壞";
    savess = "               遊戲成功保存";
    gotomainspc = "           ";
    loadfl = "無法打開存檔文件！";

    gotomain = "按任意鍵回到主菜單...";

    ytrn1 = "             你(●) 的回合:__\b\b";
    ytrn2 = "             你(○) 的回合:__\b\b";

    btrn = "            黑棋(●) 的回合:__\b\b";
    wtrn = "            白棋(○) 的回合:__\b\b";

    nposm = "        您無子可下，按回車以跳過回合";
    aipass = "  Achilles 跳過了回合, 按回車來進入你的回合";

    ip = "           該位置不能著子，您輸入的是 ";

    aithink = "           Achilles 正在思考 ...";

    dftai = "            你打敗了 Achilles! NB!";
    toosimple = "        Too Young Too Simple!";
    tieai = "                    平局！";
    tie = "平局!";
    win = "獲勝!";
}

void langStrings::printVersion()
{
    cout << verl1 << MAIN_VERSION << endl;
    cout << verl2 << ACHILLES_VERSION << endll;
    cout << verl3 << endl;
    cout << verl4 << endll;
}

void langStrings::printMenu()
{
    CLS;

    if (PRINT_VERSION)
        printVersion();

    if (Game::UIFlag)
        cout << guion << endll;
    else
        cout << endl;

    cout << menu1 << endl;
    cout << menu2 << endl;
    cout << menu3 << endl;
    if (Game::UIFlag)
        cout << menu41 << endl;
    else
        cout << menu42 << endl;
    cout << menu5 << endl;
    cout << menu6 << endl;
    cout << menu7 << endl;
    cout << menu0 << endll;
    cout << sglipt;
}

void langStrings::help()
{
    CLS;
    cout << "***************************************************" << endll;
    cout << "ON THE BOARD OF COMMAND LINE MODE:" << endll;
    cout << "'●' STANDS FOR BLACK  '○' STANDS FOR WHITE" << endl;
    cout << "'╋' MEANS THE CELL IS VALID TO PLACE YOUR STONE" << endl;
    cout << "'  ' MEANS THE CELL IS CURRENT EMPTY AND INVALID" << endll;
    cout << "7A,A7,7a,a7 ARE ALL RECOGNIZABLE INPUTS" << endll;
    cout << "***************************************************" << endll;
    cout << "YOU CAN INPUT THESE COMMAND DURING THE GAME" << endl;
    cout << "INSTEAD OF INPUTTING THE COORDINATE:" << endll;
    cout << "1.EXIT: ABORT THE GAME AND EXIT." << endll;
    cout << "2.MENU: ABORT THE GAME AND GO BACK TO THE MAIN MENU." << endll;
    cout << "3.SAVE: SAVE THE GAME AND GO BACK TO THE MAIN MENU." << endll;
    cout << "4.UNDO: UNDO YOUR (AND ACHILLES') LAST MOVE." << endll;
    cout << "***************************************************" << endll;
    cout << endll;
    PAUSE;
}

