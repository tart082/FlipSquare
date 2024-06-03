#include "FlipSquare.hpp"
#include <iostream>
#include <random>
#include <functional>

std::mt19937 mt_for_action(50);
std::mt19937 mt_for_first_second(200);

using ActionFunc = std::function<ActionInfo(const FlipSquareState &)>;

// プレイヤーのアクションを標準入力で受け付ける
ActionInfo playerAction(const FlipSquareState &state)
{
    int card_ind = -1;
    int place_i = -1;
    int place_j = -1;
    
    while(1)
    {
        std::cout << "Type Card-index you use : ";
        std::cin >> card_ind;
        if(0 <= card_ind && card_ind < CardNum) break;
        std::cout << "Invalid Action\n";
    }

    std::cout << "Type Card place\n";
    while(1)
    {
        std::cout << "Coord i : ";
        std::cin  >> place_i;
        if(1 <= place_i && place_i <= BoardSize) break;
        std::cout << "Invalid Action\n";
    }
    while(1)
    {
        std::cout << "Coord j : ";
        std::cin  >> place_j;
        if(1 <= place_j && place_j <= BoardSize) break;
        std::cout << "Invalid Action\n";
    }
    return ActionInfo(card_ind, place_i, place_j);
}

// ランダムな行動を与える
ActionInfo randomAction(const FlipSquareState &state)
{
    auto legal_actions = state.legalActions();
    return legal_actions[mt_for_action() % (legal_actions.size())];
}

// func1の行動するプレイヤーとfunc2の行動をするプレイヤーがゲームをする
// プレイヤーはAI, 人間問わない
// 先手後手はランダムに決められる．
void playGame(ActionFunc &func1, ActionFunc &func2)
{
    auto state = FlipSquareState();
    std::cout << state.toString() << std::endl;

    ActionFunc FirstPlayer;
    ActionFunc SecondPlayer;
    
    bool isGameplayerFirst = (mt_for_first_second() % 2 == 0);
    if(isGameplayerFirst)
    {
        FirstPlayer  = func1;
        SecondPlayer = func2;
    }
    else
    {
        FirstPlayer  = func2;
        SecondPlayer = func1;
    }

    while (!state.isDone())
    {
        // 1p
        {
            ActionInfo action = FirstPlayer(state);
            state.advance(action);
            std::cout << state.toString() << std::endl;
            if(state.isDone()) break;
        }
        // 2p
        {
            ActionInfo action = SecondPlayer(state);
            state.advance(action);
            std::cout << state.toString() << std::endl;
            if(state.isDone()) break;
        }
    }
    ScoreInfo score = state.calcScore();
    int FirstScore = score.first_score_;
    int SecondScore = score.second_score_;
    if(FirstScore > SecondScore)
    {
        std::cout << "1p Win!" << std::endl;
    } else if(FirstScore < SecondScore) {
        std::cout << "2p Win!" << std::endl;
    } else {
        std::cout << "Draw Game" << std::endl;
    }
}

int main()
{
    ActionFunc func1 = [](const FlipSquareState &state) { return randomAction(state); };
    // ActionFunc func1 = [](const FlipSquareState &state) { return playerAction(state); };
    ActionFunc func2 = [](const FlipSquareState &state) { return randomAction(state); };
    playGame(func1, func2);
    return 0;
}