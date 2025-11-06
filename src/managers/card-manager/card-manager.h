#ifndef FCARD_CARDMANAGER_H_
#define FCARD_CARDMANAGER_H_

#include <string>
#include <vector>
#include <map>

#include "../manager/manager.h"

class CardManager : public Manager
{
private:
    static CardManager *instancePtr;
    CardManager();

public:
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

    std::map<CardName, Card> masterCardList;

    static CardManager *getInstance();

    CardManager(const CardManager &other) = delete;
    ~CardManager();

    void startUp() override;
    void shutDown() override;
};
#endif