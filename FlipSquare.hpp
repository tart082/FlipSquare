#ifndef FLIPSQUARE_HPP
#define FLIPSQUARE_HPP

#include <string>
#include <vector>
#include <queue>

enum WinningStatus
{
    WIN,
    LOSE,
    DRAW,
    NONE,
};

enum Player
{
    First,
    Second,
};

class FlipSquareState
{
private:
    static const int BoardSize = 8;        // 盤面のサイズ
    static const int CardSize = 3;          // カードのサイズ
    static const int CardNum = 5;           //  各プレイヤーの手札の枚数
    static const int MaxTurn_ = 20;         // 最大ターン数

    // 盤面の色, 先手が黒で1, 後手が白で0
    // 処理を簡単にするために上下左右を1列空ける
    int board_[BoardSize+2][BoardSize+2] = {};
    int NowTurn_ = 1;                       // 現在のターン, 手番ｇ変わるたびに1増える
    Player TurnPlayer = Player::First;      // 現在のターンプレイヤー
    // bool is_first_ = true;              // 先手番であるか
    std::queue<int>  deck_;                 // 山札
    std::vector<int> first_cards_;          // 先手の手札
    std::vector<int> second_cards_;         // 後手の手札
    // WinningStatus first_winning_status_ = WinningStatus::NONE;

public:
    FlipSquareState();
    bool isDone() const;
    void advance(const int action);
    void distribute_card(const Player player);
    std::vector<int> legalActions() const;
    // WinningStatus getWinningStatus() const;
    std::string toString() const;
};

#endif