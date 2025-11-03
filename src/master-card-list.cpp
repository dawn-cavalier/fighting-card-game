#include <string>
#include <vector>
#include <map>

enum CardColor
{
    Red,
    Blue,
    Green
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
    std::vector<CardColor> cost;
    CardColor value;
    int damage;
    int block;
    int evade;
    std::vector<CardColor> embued = {};

    Card(std::string name,
         std::vector<CardColor> cost,
         CardColor value,
         int damage,
         int block,
         int evade)
    {
        this->name = name;
        this->cost = cost;
        this->value = value;
        this->damage = damage;
        this->block = block;
        this->evade = evade;
    };
};

std::map<CardName, Card> masterCardList =
    {
        {Block, Card("Block", {Blue}, Blue, 0, 1, 0)},
        {Bash, Card("Bash", {Red, Blue}, Blue, 2, 1, 0)},
        {Feint, Card("Feint", {Green}, Green, 0, 0, 1)},
        {Punch, Card("Punch", {Red}, Red, 1, 0, 0)},
        {BigPunch, Card("Big Punch", {Red, Red}, Red, 3, 0, 0)},
};
