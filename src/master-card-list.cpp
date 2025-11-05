#include <string>
#include <vector>
#include <map>

enum CardColor
{
    Red = 0,
    Green = 1,
    Blue = 2
};

enum CardName
{
    Block,
    Bash,
    Feint,
    Punch,
    BigPunch
};

struct Card
{
    std::string name;
    std::vector<int> cost;
    CardColor cardColor;
    int damage;
    int block;
    int evade;
    std::vector<int> embuedColors = {0, 0, 0};
    bool isEmbued = false;

    Card(std::string name,
         std::vector<int> cost,
         CardColor cardColor,
         int damage,
         int block,
         int evade)
    {
        this->name = name;
        this->cost = cost;
        this->cardColor = cardColor;
        this->damage = damage;
        this->block = block;
        this->evade = evade;
    };
};

std::map<CardName, Card> masterCardList =
    {
        {Block, Card("Block", {0, 0, 1}, Blue, 0, 1, 0)},
        {Bash, Card("Bash", {1, 0, 1}, Blue, 2, 1, 0)},
        {Feint, Card("Feint", {0, 1, 0}, Green, 0, 0, 1)},
        {Punch, Card("Punch", {1, 0, 0}, Red, 1, 0, 0)},
        {BigPunch, Card("Big Punch", {2, 0, 0}, Red, 3, 0, 0)},
};
