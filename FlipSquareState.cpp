#include "FlipSquareState.hpp"

FlipSquareState::FlipSquareState(int32 seed)
{
	// 引数のシード値からデッキシャッフル用の乱数を生成
	std::mt19937 mt_for_deckshufle(seed);

	// 盤面の初期化
	const int32 N = BoardSize;
	const int32 half = N / 2;
	for (int32 i = 1; i <= N; i++)
	{
		for (int32 j = 1; j <= N; j++)
		{
			if (i <= half) {
				board_[i][j] = 1;
			}
			else {
				board_[i][j] = 0;
			}
		}
	}
	FlipSquareState::calcScore();

	// 山札の準備とシャッフル
	const int32 M = CardSize;
	Array<int32> temp_deck;
	for (int32 i = 0; i < (1 << (M * M)); i++)
	{
		temp_deck.push_back(i);
	}
	std::shuffle(temp_deck.begin(), temp_deck.end(), mt_for_deckshufle);
	for (auto card : temp_deck)
	{
		deck_.push(card);
	}

	// カードの分配
	const int32 K = CardNum;
	for (int32 i = 0; i < K; i++) distribute_card(Player::First);
	for (int32 i = 0; i < K; i++) distribute_card(Player::Second);
}

Grid<int32>  FlipSquareState::getBoard()		const { return board_; }
int32		 FlipSquareState::getNowTurn()		const { return NowTurn_; }
ScoreInfo	 FlipSquareState::getScore()		const { return score_; }
Player		 FlipSquareState::getTurnPlayer()	const { return TurnPlayer_; }
Array<int32> FlipSquareState::getFirstCards()	const { return first_cards_; }
Array<int32> FlipSquareState::getSecondCards()	const { return second_cards_; }

bool FlipSquareState::isDone() const
{
	return NowTurn_ > MaxTurn;
}

void FlipSquareState::advance(const ActionInfo action)
{
	int32 card_ind = action.card_ind_;
	int32 center_i = action.i_;
	int32 center_j = action.j_;

	int32 card;

	if (TurnPlayer_ == Player::First)
	{
		card = first_cards_[card_ind];
		auto card_itr = first_cards_.begin() + card_ind;
		first_cards_.erase(card_itr);
		distribute_card(Player::First);
		TurnPlayer_ = Player::Second;
	}
	else
	{
		card = second_cards_[card_ind];
		auto card_itr = second_cards_.begin() + card_ind;
		second_cards_.erase(card_itr);
		distribute_card(Player::Second);
		TurnPlayer_ = Player::First;
	}

	int32 M = CardSize;
	int32 topleft_i = center_i - (M - 1) / 2;
	int32 topleft_j = center_j - (M - 1) / 2;

	for (int32 cnt_i = 0; cnt_i < M; cnt_i++)
	{
		int32 i = topleft_i + cnt_i;
		for (int32 cnt_j = 0; cnt_j < M; cnt_j++)
		{
			int32 j = topleft_j + cnt_j;
			int32 dig = cnt_i * M + cnt_j;
			if (card & (1 << dig)) {
				board_[i][j] = 1 - board_[i][j];
			}
		}
	}
	FlipSquareState::calcScore();
	NowTurn_++;
}

void FlipSquareState::distribute_card(const Player player)
{
	if (deck_.empty()) return;

	if (player == Player::First) {
		const int32 top_deck = deck_.front();
		deck_.pop();
		first_cards_.push_back(top_deck);
	}
	else {
		const int32 top_deck = deck_.front();
		deck_.pop();
		second_cards_.push_back(top_deck);
	}
}

Array<ActionInfo> FlipSquareState::legalActions() const
{
	Array<ActionInfo> actions;
	if (TurnPlayer_ == Player::First)
	{
		for (int32 card_ind = 0; card_ind < CardNum; card_ind++)
		{
			for (int32 i = 1; i <= BoardSize; i++)
			{
				for (int32 j = 1; j <= BoardSize; j++)
				{
					actions.push_back(ActionInfo(card_ind, i, j));
				}
			}
		}
	}
	else {
		for (int32 card_ind = 0; card_ind < CardNum; card_ind++)
		{
			for (int32 i = 1; i <= BoardSize; i++)
			{
				for (int32 j = 1; j <= BoardSize; j++)
				{
					actions.push_back(ActionInfo(card_ind, i, j));
				}
			}
		}
	}
	return actions;
}

void FlipSquareState::calcScore()
{
	int32 first_score = 0;
	int32 second_score = 0;
	for (int32 i = 1; i <= BoardSize; i++)
	{
		for (int32 j = 1; j <= BoardSize; j++)
		{
			if (board_[i][j] == 1) {
				first_score++;
			}
			else {
				second_score++;
			}
		}
	}
	score_ = ScoreInfo(first_score, second_score);
}

std::string FlipSquareState::toString() const
{
	std::stringstream ss("");
	ss << "---- Now Turn:" << NowTurn_ - 1;
	if (NowTurn_ != 1)
	{
		ss << " (" << ((TurnPlayer_ == Player::First) ? 2 : 1) << "p Turn) -------------------";
	}
	ss << '\n';
	const int32 N = BoardSize;
	for (int32 i = 1; i <= N; i++)
	{
		for (int32 j = 1; j <= N; j++)
		{
			if (board_[i][j] == 1) {
				ss << 'o';
			}
			else {
				ss << 'x';
			}
		}
		ss << '\n';
	}

	ss << '\n';
	ss << "First cards\n";
	const int32 M = CardSize;
	for (int32 col = 0; col < M; col++)
	{
		for (auto card : first_cards_)
		{
			for (int32 dig = col * M; dig < (col + 1) * M; dig++)
			{
				if (card & (1 << dig)) {
					ss << '#';
				}
				else {
					ss << '.';
				}
			}
			ss << "   ";
		}
		ss << '\n';
	}

	ss << '\n';
	ss << "Second cards\n";
	for (int32 col = 0; col < M; col++)
	{
		for (auto card : second_cards_)
		{
			for (int32 dig = col * M; dig < (col + 1) * M; dig++)
			{
				if (card & (1 << dig)) {
					ss << '#';
				}
				else {
					ss << '.';
				}
			}
			ss << "   ";
		}
		ss << '\n';
	}
	auto score = getScore();
	ss << "First  Score : " << score.first_score_ << '\n';
	ss << "Second Score : " << score.second_score_ << '\n';
	ss << '\n';
	return ss.str();
}
