# include <Siv3D.hpp> // OpenSiv3D v0.6.6

const int32 SizeCard = 3;
const int32 SizeBoard = 8;

class Card
{
private:
	int32 id;			// カードの種類
	Grid<bool> square;	// マス目
public:
	Grid<bool> getSquare(); // マス目
	void drawCard(int32 X, int32 Y, int32 R);
	/* コンストラクタ */
	Card(int32 num)
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

Grid<bool> Card::getSquare()
{
	return square;
}

void Card::drawCard(int32 X, int32 Y, int32 R)
{
	Grid sq = getSquare();
	int32 r = R / 4;
	Rect(X, Y, R).draw(Palette::White).drawFrame(3, 0, Palette::Orange);
	for (int32 i = 0; i < SizeCard; i++)
	{
		for (int32 j = 0; j < SizeCard; j++)
		{
			int32 x = X + r/2 + r * j;
			int32 y = Y + r/2 + r * i;
			if (sq[i][j])
				Rect(x, y, r).draw(Palette::Red);
			else
				Rect(x, y, r).draw(Palette::Gray);
		}
	}
}

Grid<bool> Board = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};



void drawBoard(Grid<bool> B, int32 X, int32 Y, int32 R)
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
	Rect(X+r, Y+r, r*8).drawFrame(0, 1, Palette::Gray);
}

int32 whitePoint = 32;
int32 blackPoint = 32;

void drawPoint(int32 wp, int32 bp, int32 X, int32 Y, int32 R, Font font)
{
	Rect(X, Y, R * 2, R).draw(Palette::Gray).drawFrame(3, 0, Palette::Orange);
	font(U"BlackPoint : ", bp, U"\nvs\nWhitePoint : ", wp).draw(X+ R / 4,Y);
}

void Main()
{
	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// 通常のフォントを作成 | Create a new font
	const Font font{ 20 };

	// 絵文字用フォントを作成 | Create a new emoji font
	const Font emojiFont{ 60, Typeface::ColorEmoji };

	// `font` が絵文字用フォントも使えるようにする | Set emojiFont as a fallback
	font.addFallback(emojiFont);

	// 画像ファイルからテクスチャを作成 | Create a texture from an image file
	const Texture texture{ U"example/windmill.png" };

	// 絵文字からテクスチャを作成 | Create a texture from an emoji
	const Texture emoji{ U"🐈"_emoji };

	Array<Card> Hands = {0, 0, 0, 0, 0};

	while (System::Update())
	{
		for (int32 i = 0; i < 5; i++)
		{
			Hands[i].drawCard(100 + i * 120, 400, 100);
		}
		for (int32 i = 0; i < 5; i++)
		{
			Hands[i].drawCard(400 + i * 80, 40, 60);
		}
		drawBoard(Board, 50, 50, 300);
		drawPoint(whitePoint, blackPoint, 400, 200, 100, font);
	}
}
