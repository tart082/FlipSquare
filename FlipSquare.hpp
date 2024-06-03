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
    PlayerNum,
};

struct ActionInfo
{
    int card_ind_;      // 手札のうちのカードのインデックス
    int i_;
    int j_;
    ActionInfo(const int card_ind, const int i, const int j) : card_ind_(card_ind), i_(i), j_(j) {}
};

struct ScoreInfo
{
    int first_score_;
    int second_score_;
    ScoreInfo(const int f, const int s) : first_score_(f), second_score_(s) {}
};

static const int BoardSize = 8;         // 盤面のサイズ
static const int CardSize = 3;          // カードのサイズ
static const int CardNum = 5;           //  各プレイヤーの手札の枚数
static const int MaxTurn = 10;          // 最大ターン数

class FlipSquareState
{
private:
    // 盤面の色, 先手が黒で1, 後手が白で0
    // 処理を簡単にするために上下左右を1列空ける
    int board_[BoardSize+2][BoardSize+2] = {};
    int NowTurn_ = 1;                       // 現在のターン, 手番ｇ変わるたびに1増える
    Player TurnPlayer_ = Player::First;     // 現在のターンプレイヤー
    std::queue<int>  deck_;                 // 山札
    std::vector<int> first_cards_;          // 先手の手札
    std::vector<int> second_cards_;         // 後手の手札

public:
    FlipSquareState();
    bool isDone() const;
    void advance(const ActionInfo action);
    void distribute_card(const Player player);
    std::vector<ActionInfo> legalActions() const;
    ScoreInfo calcScore() const;
    std::string toString() const;
};

#endif