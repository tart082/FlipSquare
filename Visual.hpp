#ifndef VISUAL_H
#define VISUAL_H

#include "FlipSquareState.hpp"

class Visual
{
private:
	FlipSquareState *state_;	// ゲームの状態
public:
	Visual(FlipSquareState *state);

	// 欲を言えばdraw関数は盤面のサイズやカードのサイズが変わってもうまく
	// 表示できるようにしたい。割合で持つなどして
	void drawFrontCard(int32 X, int32 Y, int32 R, int32 D);
	void drawBackCard (int32 X, int32 Y, int32 R, int32 D);
	void drawBoard(int32 X, int32 Y, int32 R);
	void drawPoint(int32 X, int32 Y, int32 R, Font font);
};


# endif
