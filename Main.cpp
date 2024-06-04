# include <Siv3D.hpp> // OpenSiv3D v0.6.6
# include "Visual.hpp"

/* テスト用変数 */

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

int32 whitePoint = 32;
int32 blackPoint = 32;

void Main()
{
	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// 通常のフォントを作成 | Create a new font
	const Font font{ 20 };

	Array<Visual> Hands = {0, 0, 0, 0, 0};

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
		Hands[0].drawBoard(Board, 50, 50, 300);
		Hands[0].drawPoint(whitePoint, blackPoint, 400, 200, 100, font);
	}
}
