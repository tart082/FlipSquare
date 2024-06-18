# include "Visual.hpp"

/* コンストラクタ */
Visual::Visual(FlipSquareState *state)
{
	this->state_ = state;
}

void Visual::drawFrontCard(int32 X, int32 Y, int32 R, int32 D)
{
	// ターンプレイヤーのカードが手前側に表示される

	Array<int32> FrontCards;

	if ((*state_).getTurnPlayer() == Player::First){
		FrontCards = (*state_).getFirstCards();
	} else {
		FrontCards = (*state_).getSecondCards();
	}

	int32 r = R / (CardNum-1);
	for (int32 ind = 0; ind < CardNum; ind++)
	{
		const Rect Cell(X + ind * D, Y, R);
		Cell.draw(Palette::White).drawFrame(3, 0, Palette::Orange);

		for (int32 i = 0; i < CardSize; i++)
		{
			for (int32 j = 0; j < CardSize; j++)
			{
				int32 x = (X + ind * D) + r / 2 + r * j;
				int32 y = Y + r / 2 + r * i;
				if (FrontCards[ind] & (1 << (i * CardSize + j)))
					Rect(x, y, r).draw(Palette::Red);
				else
					Rect(x, y, r).draw(Palette::Gray);
			}
		}
	}
}

void Visual::drawBackCard(int32 X, int32 Y, int32 R, int32 D)
{
	// Notターンプレイヤーのカードが奥に表示される。

	Array<int32> BackCards;

	if ((*state_).getTurnPlayer() == Player::First) {
		BackCards = (*state_).getSecondCards();
	} else {
		BackCards = (*state_).getFirstCards();
	}
	int32 r = R / (CardNum - 1);
	for (int32 ind = 0; ind < CardNum; ind++)
	{
		const Rect Cell(X + ind * D, Y, R);
		Cell.draw(Palette::White).drawFrame(3, 0, Palette::Orange);

		for (int32 i = 0; i < CardSize; i++)
		{
			for (int32 j = 0; j < CardSize; j++)
			{
				int32 x = (X + ind * D) + r / 2 + r * j;
				int32 y = Y + r / 2 + r * i;
				if (BackCards[ind] & (1 << (i * CardSize + j)))
					Rect(x, y, r).draw(Palette::Red);
				else
					Rect(x, y, r).draw(Palette::Gray);
			}
		}
	}
}


void Visual::drawBoard(int32 X, int32 Y, int32 R)
{
	// Boardの見えている範囲は、左上が(1, 1)、右下が(BoardSize, BoardSize)
	Grid<int> Board = (*state_).getBoard();
	int32 r = R / (BoardSize+2);
	Rect(X, Y, R).draw(Palette::White).drawFrame(3, 0, Palette::Orange);
	for (int32 i = 1; i <= BoardSize; i++)
	{
		for (int32 j = 1; j <= BoardSize; j++)
		{
			int32 x = X + r * j;
			int32 y = Y + r * i;
			const Rect Cell(x, y, r);
			Cell.draw(Palette::White).drawFrame(3, 0, Palette::Orange);
			if (Board[i][j])
				Cell.draw(Palette::Black).drawFrame(1, 0, Palette::Gray);
			else
				Cell.draw(Palette::White).drawFrame(1, 0, Palette::Gray);
		}
	}
	Rect(X + r, Y + r, r * 8).drawFrame(0, 1, Palette::Gray);
}

void Visual::drawPoint(int32 X, int32 Y, int32 R, Font font)
{
	int32 BlackPoint = (*state_).getScore().first_score_;
	int32 WhitePoint = (*state_).getScore().second_score_;
	Rect(X, Y, R * 2, R).draw(Palette::Gray).drawFrame(3, 0, Palette::Orange);
	font(U"BlackPoint : ", BlackPoint, U"\nvs\nWhitePoint : ", WhitePoint).draw(X + R / 4, Y);
}
