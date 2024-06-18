# pragma once
# include "Common.hpp"
#include "FlipSquareState.hpp"

// ゲームシーン
class Game : public App::Scene
{
private:
	FlipSquareState state_ = FlipSquareState(0);		// ゲームの状態
	bool  SelectCardFlag_ = false;	// 使用するカードを選んでいるかどうか
	int32 SelectCardNum_ = -1;		// 現在選択しているカード

	// 手前に表示するカードの基準の座標とカードの幅と間隔
	int32 FrontX_ = 100;	// 最左カード左辺のX座標
	int32 FrontY_ = 400;	// カード上辺のY座標
	int32 FrontR_ = 100;	// カードの幅
	int32 FrontD_ = 120;	// カードの間隔

	// 奥に表示するカードの基準の座標とカードの幅と間隔
	int32 BackX_ = 400;	// 最左カード左辺のX座標
	int32 BackY_ =  40;	// カード上辺のY座標
	int32 BackR_ =  60;	// カードの幅
	int32 BackD_ =  80;	// カードの間隔

	// 盤面の基準の座標とカードの幅
	int32 BoardX_ = 50;	// 盤面左辺のX座標
	int32 BoardY_ = 50;	// 盤面上辺のY座標
	int32 BoardR_ = 300;	// 盤面の幅

	// ポイント表示の座標
	int32 PointX_ = 400;
	int32 PointY_ = 200;
	int32 PointR_ = 100;
	Font PointFont_{ 20 };

public:
	Game(const InitData& init);

	void update() override;

	void drawFrontCard() const;
	void drawBackCard() const;
	void drawBoard() const;
	void drawPoint() const;

	void draw() const override;
};
