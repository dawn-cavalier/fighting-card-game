#include <string>
#include <vector>
#include <iostream>

// TODO: Replace with SDL Random
#include <random>

struct Card
{
    std::string name;
    unsigned int damage;
    unsigned int block;
    unsigned int evade;
};

int main()
{
    std::vector<Card> masterDeck = {};
    std::vector<Card> drawPile = {};
    std::vector<Card> discard = {};

    // TODO: Move to a card list file
    Card block = {"Block", 0, 1, 0};
    Card bash = {"Bash", 2, 1, 0};
    Card feint = {"Feint", 0, 0, 1};
    Card punch = {"Punch", 1, 0, 0};
    Card bigPunch = {"Punch", 3, 0, 0};

    // TODO: Move to build starter deck function
    masterDeck.push_back(block);
    masterDeck.push_back(block);
    masterDeck.push_back(bash);
    masterDeck.push_back(feint);
    masterDeck.push_back(feint);
    masterDeck.push_back(feint);
    masterDeck.push_back(punch);
    masterDeck.push_back(punch);
    masterDeck.push_back(bigPunch);

    // Start of Fight
    drawPile = masterDeck;
    // Shuffle
    // TODO: Replace
    srand(time(0));
    for (auto index = 0; index < drawPile.size(); index++)
    {
        int newPosition = index + (rand() % (drawPile.size() - index));
        Card hold = drawPile.at(newPosition);
        drawPile.at(newPosition) = drawPile.at(index);
        drawPile.at(index) = hold;
    }
    
    // TODO: Remove
    // TEST DISPLAY START
    for (auto card : drawPile)
    {
        std::cout << card.name << std::endl;
    }
    // TEST DISPLAY END
    return 0;
}