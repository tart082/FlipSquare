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

	// 手前(1Pプレイヤー)のカードの基準の座標とカードの幅と間隔
	int32 FrontX_ = 550;	// 最左カード左辺のX座標
	int32 FrontY_ = 430;	// カード上辺のY座標
	int32 FrontR_ = 120;	// カードの幅
	int32 FrontD_ = 130;	// カードの間隔

	// 奥(2Pプレイヤー)のカードの基準の座標とカードの幅と間隔
	int32 BackX_ = 550;		// 最左カード左辺のX座標
	int32 BackY_ =  50;		// カード上辺のY座標
	int32 BackR_ = 120;		// カードの幅
	int32 BackD_ = 130;		// カードの間隔

	// 強調表示の長方形のX座標，幅と高さ
	int32 EmphaX_ = 540;	// 
	int32 EmphaW_ = 820;	// 
	int32 EmphaH_ = 140;	//

	// 手前(1Pプレイヤー)のカードの強調表示
	int32 EmphaFrontY_ = 420;

	// 奥(2Pプレイヤー)のカードの強調表示
	int32 EmphaBackY_  =  40;

	// 盤面の基準の座標とカードの幅
	int32 BoardX_ = 25;	// 盤面左辺のX座標
	int32 BoardY_ = 50;	// 盤面上辺のY座標
	int32 BoardR_ = 500;	// 盤面の幅

	// ポイント表示の座標
	int32 PointX_ = 550;
	int32 PointY_ = 250;
	int32 PointR_ = 100;
	Font PointFont_{ 20 };

public:
	Game(const InitData& init);
	bool isFirstTurn() const;

	void update() override;

	void drawFrontCard()	const;
	void drawBackCard()		const;
	void drawEmphasizeCard()const;
	void drawBoard()		const;
	void drawPoint()		const;

	void draw() const override;
};
