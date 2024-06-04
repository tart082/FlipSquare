#ifndef VISUAL_H
#define VISUAL_H

const int32 SizeCard = 3;
const int32 SizeBoard = 8;

class Visual
{
private:
	int32 id;			// カードの種類
	Grid<bool> square;	// マス目
public:
	Grid<bool> getSquare(); // マス目
	void drawCard(int32 X, int32 Y, int32 R);
	void drawBoard(Grid<bool> B, int32 X, int32 Y, int32 R);
	void drawPoint(int32 wp, int32 bp, int32 X, int32 Y, int32 R, Font font);
	/* コンストラクタ */
	Visual(int32 num)
	{
		id = num;
		for (int32 i = 0; i < SizeCard * SizeCard; i++)
		{
			//square[i / 3][i % 3] = ((id & (1<<i)) == (1<<i));
			if (id % 2 == 1)
				square[i / 3][i % 3] = 1;
			else
				square[i / 3][i % 3] = 0;
			id /= 2;
		}
		id = num;
		square = { {1, 0, 1}, {1, 1 , 1}, {1, 0, 1} }; // テスト用
	}
};


# endif
