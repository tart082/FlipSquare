# include "Visual.hpp"
Grid<bool> Visual::getSquare()
{
	return square;
}

void Visual::drawCard(int32 X, int32 Y, int32 R)
{
	Grid sq = getSquare();
	int32 r = R / 4;
	Rect(X, Y, R).draw(Palette::White).drawFrame(3, 0, Palette::Orange);
	for (int32 i = 0; i < SizeCard; i++)
	{
		for (int32 j = 0; j < SizeCard; j++)
		{
			int32 x = X + r / 2 + r * j;
			int32 y = Y + r / 2 + r * i;
			if (sq[i][j])
				Rect(x, y, r).draw(Palette::Red);
			else
				Rect(x, y, r).draw(Palette::Gray);
		}
	}
}

void Visual::drawBoard(Grid<bool> B, int32 X, int32 Y, int32 R)
{
	int32 r = R / 10;
	Rect(X, Y, R).draw(Palette::White).drawFrame(3, 0, Palette::Orange);
	for (int32 i = 0; i < SizeBoard; i++)
	{
		for (int32 j = 0; j < SizeBoard; j++)
		{
			int32 x = X + r + r * j;
			int32 y = Y + r + r * i;
			if (B[i][j])
				Rect(x, y, r).draw(Palette::Black).drawFrame(1, 0, Palette::Gray);
			else
				Rect(x, y, r).draw(Palette::White).drawFrame(1, 0, Palette::Gray);
		}
	}
	Rect(X + r, Y + r, r * 8).drawFrame(0, 1, Palette::Gray);
}

void Visual::drawPoint(int32 wp, int32 bp, int32 X, int32 Y, int32 R, Font font)
{
	Rect(X, Y, R * 2, R).draw(Palette::Gray).drawFrame(3, 0, Palette::Orange);
	font(U"BlackPoint : ", bp, U"\nvs\nWhitePoint : ", wp).draw(X + R / 4, Y);
}
