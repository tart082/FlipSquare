#include "FlipSquare.hpp"
#include <sstream>
#include <iostream>
#include <queue>
#include <random>
#include <algorithm>
#include <vector>

std::mt19937 mt_for_deck(0);

FlipSquareState::FlipSquareState()
{
    // 盤面の初期化
    const int N = BoardSize;
    const int half = N / 2;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            if(i <= half) {
                board_[i][j] = 1;
            } else {
                board_[i][j] = 0;
            }
        }
    }
    
    // 山札の準備とシャッフル
    const int M = CardSize;
    std::vector<int> temp_deck;
    for(int i = 0; i < (1<<(M*M)); i++)
    {
        temp_deck.push_back(i);
    }
    std::shuffle(temp_deck.begin(), temp_deck.end(), mt_for_deck);
    for(auto card : temp_deck)
    {
        deck_.push(card);
    }
    
    // カードの分配
    const int K = CardNum;
    for(int i = 0; i < K; i++) distribute_card(Player::First);
    for(int i = 0; i < K; i++) distribute_card(Player::Second);
}

bool FlipSquareState::isDone() const
{
    return NowTurn_ > MaxTurn;
}

void FlipSquareState::advance(const ActionInfo action)
{
    int card_ind = action.card_ind_;
    int center_i = action.i_;
    int center_j = action.j_;

    int card;

    if(TurnPlayer_ == Player::First)
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

    int M = CardSize;
    int topleft_i = center_i - (M-1)/2;
    int topleft_j = center_j - (M-1)/2;

    for(int cnt_i = 0; cnt_i < M; cnt_i++)
    {
        int i = topleft_i + cnt_i;
        for(int cnt_j = 0; cnt_j < M; cnt_j++)
        {
            int j = topleft_j + cnt_j;
            int dig = cnt_i*M + cnt_j;
            if(card & (1 << dig)) {
                board_[i][j] = 1 - board_[i][j];
            }
        }
    }
    NowTurn_++;
}

void FlipSquareState::distribute_card(const Player player)
{
    if(deck_.empty()) return;

    if(player == Player::First) {
        const int top_deck = deck_.front();
        deck_.pop();
        first_cards_.push_back(top_deck);
    } else {
        const int top_deck = deck_.front();
        deck_.pop();
        second_cards_.push_back(top_deck); 
    }
}

std::vector<ActionInfo> FlipSquareState::legalActions() const
{
    std::vector<ActionInfo> actions;
    if(TurnPlayer_ == Player::First)
    {
        for(int card_ind = 0; card_ind < CardNum; card_ind++)
        {
            for(int i = 1; i <= BoardSize; i++)
            {
                for(int j = 1; j <= BoardSize; j++)
                {
                    actions.push_back(ActionInfo(card_ind, i, j));
                }    
            }
        }
    } else {
        for(int card_ind = 0; card_ind < CardNum; card_ind++)
        {
            for(int i = 1; i <= BoardSize; i++)
            {
                for(int j = 1; j <= BoardSize; j++)
                {
                    actions.push_back(ActionInfo(card_ind, i, j));
                }    
            }
        }
    }
    return actions;
}

ScoreInfo FlipSquareState::calcScore() const
{
    int first_score = 0;
    int second_score = 0;
    for(int i = 1; i <= BoardSize; i++)
    {
        for(int j = 1; j <= BoardSize; j++)
        {
            if(board_[i][j] == 1) {
                first_score++;
            } else {
                second_score++;
            }
        }
    }
    return ScoreInfo(first_score, second_score);
}

std::string FlipSquareState::toString() const
{
    std::stringstream ss("");
    ss << "---- Now Turn:" << NowTurn_ - 1;
    if(NowTurn_ != 1)
    {
        ss << " (" << ((TurnPlayer_ == Player::First) ? 2 : 1) << "p Turn) -------------------";
    }
    ss << '\n';
    const int N = BoardSize;    
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            if(board_[i][j] == 1) {
                ss << 'o';
            } else {
                ss << 'x';
            }
        }
        ss << '\n';
    }

    ss << '\n';
    ss << "First cards\n";
    const int M = CardSize;
    for(int col = 0; col < M; col++)
    {
        for(auto card : first_cards_)
        {
            for(int dig = col*M; dig < (col+1)*M; dig++)
            {
                if(card & (1 << dig)) {
                    ss << '#';
                } else {
                    ss << '.';
                }
            }
            ss << "   ";
        }
        ss << '\n';
    }

    ss << '\n';
    ss << "Second cards\n";
    for(int col = 0; col < M; col++)
    {
        for(auto card : second_cards_)
        {
            for(int dig = col*M; dig < (col+1)*M; dig++)
            {
                if(card & (1 << dig)) {
                    ss << '#';
                } else {
                    ss << '.';
                }
            }
            ss << "   ";
        }
        ss << '\n';
    }
    auto score = calcScore();
    ss << "First  Score : " << score.first_score_ << '\n';
    ss << "Second Score : " << score.second_score_ << '\n';
    ss << '\n';
    return ss.str();
}