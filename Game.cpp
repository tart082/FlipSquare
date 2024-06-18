# include "Game.hpp"

Game::Game(const InitData& init) : IScene{ init }
{
	state_ = FlipSquareState(0);
}

void Game::update()
{
	// 使用する手札を選択していない　→　手札を選択する

	// 使用する手札を選択している　　→　手札の選択を解除する　or　盤面のマスを選ぶ

	if (!SelectCardFlag_)
	{
		for (int32 ind = 0; ind < CardNum; ind++)
		{
			const Rect CardCell(FrontX_ + ind * FrontD_, FrontY_, FrontR_);
			if (CardCell.leftClicked())
			{
				this->SelectCardFlag_ = true;
				SelectCardNum_ = ind;
			}
		}
	}
	else
	{
		const Rect CardCell(FrontX_ + SelectCardNum_ * FrontD_, FrontY_, FrontR_);
		if (CardCell.leftClicked())
		{
			this->SelectCardFlag_ = false;
			SelectCardNum_ = -1;
		}
		else
		{
			int32 r = BoardR_ / (BoardSize + 2);
			for (int32 i = 1; i <= BoardSize; i++)
			{
				for (int32 j = 1; j <= BoardSize; j++)
				{
					int32 x = BoardX_ + r * j;
					int32 y = BoardY_ + r * i;
					const Rect BoardCell(x, y, r);

					if (BoardCell.leftClicked())
					{
						state_.advance(ActionInfo(SelectCardNum_, i, j));
						SelectCardFlag_ = false;
						SelectCardNum_ = -1;
					}
				}
			}
		}
	}
	if (state_.isDone())
	{
		changeScene(State::Ranking);
	}
}


void Game::drawFrontCard() const
{
	// ターンプレイヤーのカードが手前側に表示される

	Array<int32> FrontCards;

	if (state_.getTurnPlayer() == Player::First) {
		FrontCards = state_.getFirstCards();
	}
	else {
		FrontCards = state_.getSecondCards();
	}

	int32 r = FrontR_ / (CardNum - 1);
	for (int32 ind = 0; ind < CardNum; ind++)
	{
		const Rect Cell(FrontX_ + ind * FrontD_, FrontY_, FrontR_);
		Cell.draw(Palette::White).drawFrame(3, 0, Palette::Orange);

		for (int32 i = 0; i < CardSize; i++)
		{
			for (int32 j = 0; j < CardSize; j++)
			{
				int32 x = (FrontX_ + ind * FrontD_) + r / 2 + r * j;
				int32 y = FrontY_ + r / 2 + r * i;
				if (FrontCards[ind] & (1 << (i * CardSize + j)))
					Rect(x, y, r).draw(Palette::Red);
				else
					Rect(x, y, r).draw(Palette::Gray);
			}
		}
		if (Cell.mouseOver())
		{
			if (!SelectCardFlag_)
			{
				// カーソルを手のアイコンに
				Cursor::RequestStyle(CursorStyle::Hand);
				// セルの上に半透明の白を描く
				Cell.stretched(-2).draw(ColorF{ 1.0, 0.6 });
			}
		}
	}
	if (SelectCardFlag_)
	{
		const Rect CardCell(FrontX_ + SelectCardNum_ * FrontD_, FrontY_, FrontR_);
		Cursor::RequestStyle(CursorStyle::Hand);
		CardCell.stretched(-2).draw(ColorF{ 1.0, 0.6 });
	}
}

void Game::drawBackCard() const
{
	// Notターンプレイヤーのカードが奥に表示される。

	Array<int32> BackCards;

	if(state_.getTurnPlayer() == Player::First) {
		BackCards = state_.getSecondCards();
	}
	else {
		BackCards = state_.getFirstCards();
	}
	int32 r = BackR_ / (CardNum - 1);
	for (int32 ind = 0; ind < CardNum; ind++)
	{
		const Rect Cell(BackX_ + ind * BackD_, BackY_, BackR_);
		Cell.draw(Palette::White).drawFrame(3, 0, Palette::Orange);

		for (int32 i = 0; i < CardSize; i++)
		{
			for (int32 j = 0; j < CardSize; j++)
			{
				int32 x = (BackX_ + ind * BackD_) + r / 2 + r * j;
				int32 y = BackY_ + r / 2 + r * i;
				if (BackCards[ind] & (1 << (i * CardSize + j)))
					Rect(x, y, r).draw(Palette::Red);
				else
					Rect(x, y, r).draw(Palette::Gray);
			}
		}
	}
}

void Game::drawBoard() const
{
	// Boardの見えている範囲は、左上が(1, 1)、右下が(BoardSize, BoardSize)
	Grid<int> Board = state_.getBoard();
	int32 r = BoardR_ / (BoardSize + 2);
	Rect(BoardX_, BoardY_, BoardR_).draw(Palette::White).drawFrame(3, 0, Palette::Orange);
	for (int32 i = 1; i <= BoardSize; i++)
	{
		for (int32 j = 1; j <= BoardSize; j++)
		{
			int32 x = BoardX_ + r * j;
			int32 y = BoardY_ + r * i;
			const Rect Cell(x, y, r);
			Cell.draw(Palette::White).drawFrame(3, 0, Palette::Orange);
			if (Board[i][j])
				Cell.draw(Palette::Black).drawFrame(1, 0, Palette::Gray);
			else
				Cell.draw(Palette::White).drawFrame(1, 0, Palette::Gray);
		}
	}
	Rect(BoardX_ + r, BoardY_ + r, r * 8).drawFrame(0, 1, Palette::Gray);
	for (int32 i = 1; i <= BoardSize; i++)
	{
		for (int32 j = 1; j <= BoardSize; j++)
		{
			int32 x = BoardX_ + r * j;
			int32 y = BoardY_ + r * i;
			const Rect Cell(x, y, r);
			if (SelectCardFlag_ && Cell.mouseOver())
			{
				Cursor::RequestStyle(CursorStyle::Hand);
				// 選んだセルとその近傍に半透明の水色を描く
				for (int32 k = Max(1, i - 1); k <= Min(BoardSize, i + 1); k++)
				{
					for (int32 l = Max(1, j - 1); l <= Min(BoardSize, j + 1); l++)
					{
						int32 xn = BoardX_ + r * l;
						int32 yn = BoardY_ + r * k;
						const Rect NearCell(xn, yn, r);
						NearCell.stretched(-5).draw(ColorF{ 0.8, 0.9, 1.0 });
					}
				}
			}
		}
	}
}

void Game::drawPoint() const
{
	int32 BlackPoint = state_.getScore().first_score_;
	int32 WhitePoint = state_.getScore().second_score_;
	Rect(PointX_, PointY_, PointR_ * 2, PointR_).draw(Palette::Gray).drawFrame(3, 0, Palette::Orange);
	PointFont_(U"BlackPoint : ", BlackPoint, U"\nvs\nWhitePoint : ", WhitePoint).draw(PointX_ + PointR_ / 4, PointY_);
}

void Game::draw() const
{
	//背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	Game::drawFrontCard();
	Game::drawBackCard();
	Game::drawBoard();
	Game::drawPoint();
}
