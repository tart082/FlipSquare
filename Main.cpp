# include "Common.hpp"
# include "Title.hpp"
# include "Game.hpp"
# include "Ranking.hpp"

void Main()
{
	Window::Resize(1200, 600);
	FontAsset::Register(U"TitleFont", FontMethod::MSDF, 50, U"example/font/RocknRoll/RocknRollOne-Regular.ttf");
	FontAsset(U"TitleFont").setBufferThickness(4);
	FontAsset::Register(U"Menu", FontMethod::MSDF, 40, Typeface::Medium);
	FontAsset::Register(U"Ranking", 40, Typeface::Heavy);
	FontAsset::Register(U"GameScore", 30, Typeface::Light);
	AudioAsset::Register(U"Brick", GMInstrument::Woodblock, PianoKey::C5, 0.2s, 0.1s);

	App manager;
	manager.add<Title>(State::Title);
	manager.add<Game>(State::Game);
	manager.add<Ranking>(State::Ranking);

	// ゲームシーンから開始したい場合はこのコメントを外す
	//manager.init(State::Game);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
//# include "Visual.hpp"
//# include "Controller.hpp"
//
//void Main()
//{
//	// 背景の色を設定 | Set background color
//	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
//
//	// 通常のフォントを作成 | Create a new font
//	const Font font{ 20 };
//
//	int32 seed = 0;
//	FlipSquareState state = FlipSquareState(seed);
//	auto visual = Visual(&state);
//	auto cont = Controller(&state);
//
//	int32 X1, Y1, R1, D1;
//	int32 X2, Y2, R2, D2;
//	X1 = 100; Y1 = 400; R1 = 100; D1 = 120;
//	X2 = 400; Y2 =  40; R2 =  60; D2 =  80;
//
//	cont.setCardInfo(X1, Y1, R1, D1);
//	cont.setBoardInfo(50, 50, 300);
//	
//	while (System::Update())
//	{
//		visual.drawFrontCard(X1, Y1, R1, D1);
//		visual.drawBackCard (X2, Y2, R2, D2);
//		visual.drawBoard(50, 50, 300);
//		visual.drawPoint(400, 200, 100, font);
//		cont.update();
//	}
//}
