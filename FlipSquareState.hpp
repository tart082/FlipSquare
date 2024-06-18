#ifndef FLIPSQUARESTATE_HPP
#define FLIPSQUARESTATE_HPP

#include "BaseData.hpp"

class FlipSquareState
{
private:
	// 盤面の色, 先手が黒で1, 後手が白で0
	// 処理を簡単にするために上下左右を1列空ける
	Grid<int32> board_ = Grid<int32>(BoardSize + 2, BoardSize + 2, 0);
	int32 NowTurn_ = 1;                       // 現在のターン, 手番ｇ変わるたびに1増える
	ScoreInfo score_ = ScoreInfo(0, 0);     // 先手と後手のスコア
	Player TurnPlayer_ = Player::First;     // 現在のターンプレイヤー
	std::queue<int32>  deck_;                 // 山札
	Array<int32> first_cards_;          // 先手の手札
	Array<int32> second_cards_;         // 後手の手札

public:
	FlipSquareState(int32 seed);

	Grid<int32>	 getBoard()		  const;
	int32		 getNowTurn()	  const;
	ScoreInfo	 getScore()		  const;
	Player		 getTurnPlayer()  const;
	Array<int32> getFirstCards()  const;
	Array<int32> getSecondCards() const;

	bool isDone() const;
	void advance(const ActionInfo action);
	void distribute_card(const Player player);
	Array<ActionInfo> legalActions() const;
	void calcScore();
	std::string toString() const;
};

#endif
