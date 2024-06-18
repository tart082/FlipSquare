#ifndef BASEDATA_HPP
#define BASEDATA_HPP

# include <Siv3D.hpp> // OpenSiv3D v0.6.14

enum Player
{
	First,
	Second,
	PlayerNum,
};

struct ActionInfo
{
	int32 card_ind_;      // 手札のうちのカードのインデックス
	int32 i_;
	int32 j_;
	ActionInfo(const int32 card_ind, const int32 i, const int32 j) : card_ind_(card_ind), i_(i), j_(j) {}
};

struct ScoreInfo
{
	int32 first_score_;
	int32 second_score_;
	ScoreInfo(const int32 f, const int32 s) : first_score_(f), second_score_(s) {}
};

static constexpr int32 BoardSize =  8;	// 盤面のサイズ
static constexpr int32 CardSize  =  3;	// カードのサイズ
static constexpr int32 CardNum   =  5;  // 各プレイヤーの手札の枚数
static constexpr int32 MaxTurn   = 10;	// 最大ターン数

#endif
