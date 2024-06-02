#include "FlipSquare.hpp"
#include <sstream>
#include <queue>
#include <random>
#include <algorithm>
#include <vector>

std::mt19937 get_rand_mt(0);

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
    std::shuffle(temp_deck.begin(), temp_deck.end(), get_rand_mt);
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
    return NowTurn_ > MaxTurn_;
}

void FlipSquareState::advance(const int action)
{

}

void FlipSquareState::distribute_card(const Player player)
{
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

std::vector<int> FlipSquareState::legalActions() const
{
    std::vector<int> actions;
    if(TurnPlayer == Player::First)
    {
        for(auto card : first_cards_)
        {
            actions.push_back(card);
        }
    } else {
        for(auto card : second_cards_)
        {
            actions.push_back(card);
        }
    }
    return actions;
}

// WinningStatus FlipSquareState::getWinningStatus() const
// {
//     return first_winning_status_;
// }

std::string FlipSquareState::toString() const
{
    std::stringstream ss("");

    // ss << "is_first:\t" << this->is_first_ << "\n";

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
            ss << "  ";
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
            ss << "  ";
        }
        ss << '\n';
    }

    return ss.str();
}