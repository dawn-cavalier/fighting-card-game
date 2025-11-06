#include <string>
#include <vector>
#include <iostream>

// TODO: Replace with SDL Random
#include <random>

#include "./src/managers/card-manager/card-manager.h"
#include "./src/managers/player-manager/player-manager.h"
#include "./src/managers/game-state-manager/game-state-manager.h"
// TODO: These should be linked automatically but for some reason they are not
#include "./src/managers/card-manager/card-manager.cpp"
#include "./src/managers/player-manager/player-manager.cpp"
#include "./src/managers/game-state-manager/game-state-manager.cpp"

enum GameState
{
    GameSetUp = 0,
    GameShutDown,
    FightStart,
    FightTurnStart,
    FightInhale,
    FightExhale,
    FightPlay,
    FightDiscard,
    FightTurnEnd
};

/**
 * @brief Request and converts user's input into a number.
 *
 * @return int
 */
int pollUserInput();

/**
 * @brief   Executes one interation of the inhale phase and returns if the phase should end.
 *
 * @param   handZone
 * @param   focusZone
 * @return  true
 * @return  false
 */
bool inhaleIteration(
    std::vector<CardManager::Card> *handZone,
    std::vector<CardManager::Card> *focusZone);

/**
 * @brief   Executes one interation of the exhale phase and returns if the phase should end.
 *
 * @param   handZone
 * @param   focusZone
 * @param   discardZone
 * @return  true
 * @return  false
 */
bool exhaleIteration(
    std::vector<CardManager::Card> *handZone,
    std::vector<CardManager::Card> *focusZone,
    std::vector<CardManager::Card> *discardZone);

/**
 * @brief Executes one interation of the play phase and returns if the phase should end.
 *
 * @param focusZone
 * @param discardZone
 * @return true
 * @return false
 */
bool playIteration(
    std::vector<CardManager::Card> *focusZone,
    std::vector<CardManager::Card> *discardZone);

/**
 * @brief Intializes all Managers
 *
 */
const void startUp();

/**
 * @brief Cleans up all Managers
 *
 */
const void shutDown();

CardManager *CardManager::instancePtr = nullptr;
PlayerManager *PlayerManager::instancePtr = nullptr;
GameStateManager *GameStateManager::instancePtr = nullptr;

int main(int argCount, char *argVariables[])
{
    // TODO: Replace
    startUp();
    auto cardRef = CardManager::getInstance();
    auto playerRef = PlayerManager::getInstance();

    std::vector<CardManager::Card> *masterDeck = &playerRef->masterDeck;
    std::vector<CardManager::Card> *deckZone = &playerRef->deckZone;
    std::vector<CardManager::Card> *discardZone = &playerRef->discardZone;
    std::vector<CardManager::Card> *handZone = &playerRef->handZone;
    std::vector<CardManager::Card> *focusZone = &playerRef->focusZone;

    GameState state = GameSetUp;

    auto masterCardList = cardRef->masterCardList;

    // Start of Game Loop
    bool running = true;
    while (true)
    {
        switch (state)
        {
        case GameSetUp:
            playerRef->addCardsToMasterDeck(
                {cardRef->Block,
                 cardRef->Block,
                 cardRef->Bash,
                 cardRef->Feint,
                 cardRef->Feint,
                 cardRef->Feint,
                 cardRef->Punch,
                 cardRef->Punch,
                 cardRef->BigPunch});
            state = FightStart;
            break;
        case GameShutDown:
            running = false;
            break;
        case FightStart:
            playerRef->fightStart();
            state = FightTurnStart;
            break;
        case FightTurnStart:
            playerRef->drawCards(5);
            std::cout << "Inhale Phase" << std::endl;
            state = FightInhale;
            break;
        case FightInhale:
            if (inhaleIteration(handZone, focusZone))
            {
                std::cout << "Exhale Phase" << std::endl;
                state = FightExhale;
            };
            break;
        case FightExhale:
            if (exhaleIteration(handZone, focusZone, discardZone))
            {
                state = FightPlay;
            }
            break;
        case FightPlay:
            if (playIteration(focusZone, discardZone))
            {
                state = FightDiscard;
            }
            break;
        case FightDiscard:
            playerRef->moveToDiscard();
            state = FightTurnEnd;
            break;
        case FightTurnEnd:
            state = FightTurnStart;
            break;
        default:
            std::string msg = "ERROR: Entered recognized game state (";
            msg.append(std::to_string(state));
            msg.append(").");
            std::cerr << msg << std::endl;
            throw std::logic_error(msg);
            break;
        }
    }
    return 0;
}

int pollUserInput()
{
    std::string input = "";
    int inputNum = -1;
    std::cin >> input;
    try
    {
        std::size_t processedChars;
        inputNum = std::stoi(input, &processedChars);
        if (processedChars != input.length())
        {
            throw std::invalid_argument("String contains non-numeric characters after number.");
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Invalid Command!" << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown Error." << std::endl;
    }
    std::cout << std::endl;
    return inputNum;
}

bool inhaleIteration(std::vector<CardManager::Card> *handZone, std::vector<CardManager::Card> *focusZone)
{
    int inputNum = -1;

    std::cout << "Focused Cards:" << std::endl;
    for (int i = 0; i < focusZone->size(); i++)
    {
        std::cout << focusZone->at(i).name << std::endl;
    }

    std::cout << "Hand:" << std::endl;
    std::cout << "(" << 0 << "): " << "End Inhale Phase" << std::endl;
    for (int i = 0; i < handZone->size(); i++)
    {
        std::cout << "(" << i + 1 << "): " << handZone->at(i).name << std::endl;
    }

    inputNum = pollUserInput();
    // User wishes to end the inhale phase, exit
    if (inputNum == 0)
    {
        return true;
    }

    // Check if input is within range
    if (inputNum < 0 || inputNum > handZone->size())
    {
        std::cerr << "Invalid input" << std::endl;
        return false;
    }

    // Undo padding for ease of use
    inputNum--;

    CardManager::Card hold = handZone->at(inputNum);
    handZone->erase(handZone->begin() + inputNum);
    focusZone->push_back(hold);
    return false;
}

bool exhaleIteration(std::vector<CardManager::Card> *handZone, std::vector<CardManager::Card> *focusZone, std::vector<CardManager::Card> *discardZone)
{
    int inputNum = -1;

    std::cout << "Focused Cards:" << std::endl;
    for (int i = 0; i < focusZone->size(); i++)
    {
        auto currentCard = focusZone->at(i);
        std::string imbuedMessage = "";

        imbuedMessage.append("(");
        imbuedMessage.append(std::to_string(currentCard.embuedColors.at(CardManager::Red)));
        imbuedMessage.append("/");
        imbuedMessage.append(std::to_string(currentCard.cost.at(CardManager::Red)));
        imbuedMessage.append(", ");
        imbuedMessage.append(std::to_string(currentCard.embuedColors.at(CardManager::Green)));
        imbuedMessage.append("/");
        imbuedMessage.append(std::to_string(currentCard.cost.at(CardManager::Green)));
        imbuedMessage.append(", ");
        imbuedMessage.append(std::to_string(currentCard.embuedColors.at(CardManager::Blue)));
        imbuedMessage.append("/");
        imbuedMessage.append(std::to_string(currentCard.cost.at(CardManager::Blue)));
        imbuedMessage.append(")");

        if (currentCard.isEmbued)
        {
            imbuedMessage.append(" (Ready!)");
        }

        std::cout << currentCard.name << ": " << imbuedMessage << std::endl;
    }

    std::cout << "Hand:" << std::endl;
    std::cout << "(" << 0 << "): " << "End Exhale Phase" << std::endl;
    for (int i = 0; i < handZone->size(); i++)
    {
        auto currentCard = handZone->at(i);
        std::string message = "";

        message.append("(");
        message.append(std::to_string(i + 1));
        message.append("): ");
        message.append(currentCard.name);
        message.append(": ");
        message.append("<");
        switch (currentCard.cardColor)
        {
        case CardManager::Red:
            message.append("Red");
            break;
        case CardManager::Green:
            message.append("Green");
            break;
        case CardManager::Blue:
            message.append("Blue");
            break;
        default:
            break;
        }
        message.append(">");
        std::cout << message << std::endl;
    }

    inputNum = pollUserInput();

    // User wishes to end the exhale phase, exit
    if (inputNum == 0)
    {
        return true;
    }

    // Check if input is within range
    if (inputNum < 0 || inputNum > handZone->size())
    {
        std::cerr << "Invalid input" << std::endl;
        return false;
    }

    // Undo padding for ease of use
    inputNum--;

    // Playing the Card and Imbuing the focused cards
    CardManager::Card playedCard = handZone->at(inputNum);
    handZone->erase(handZone->begin() + inputNum);
    discardZone->push_back(playedCard);

    for (CardManager::Card &card : *focusZone)
    {
        // If full embued skip
        if (card.isEmbued)
        {
            continue;
        }

        card.embuedColors.at(playedCard.cardColor)++;
        card.isEmbued =
            card.embuedColors.at(CardManager::Red) >= card.cost.at(CardManager::Red) &&
            card.embuedColors.at(CardManager::Green) >= card.cost.at(CardManager::Green) &&
            card.embuedColors.at(CardManager::Blue) >= card.cost.at(CardManager::Blue);
    }

    return false;
}

bool playIteration(std::vector<CardManager::Card> *focusZone, std::vector<CardManager::Card> *discardZone)
{
    int inputNum = -1;

    std::cout << "Focused Cards:" << std::endl;
    std::cout << "(" << 0 << "): " << "End Exhale Phase" << std::endl;
    for (int i = 0; i < focusZone->size(); i++)
    {
        auto currentCard = focusZone->at(i);
        std::string imbuedMessage = "";
        if (currentCard.isEmbued)
        {
            imbuedMessage = " (Ready!) ";
        }
        std::cout << "(" << i + 1 << "): " << currentCard.name << imbuedMessage << std::endl;
    }

    inputNum = pollUserInput();

    // User wishes to end the exhale phase, exit
    if (inputNum == 0)
    {
        return true;
    }

    // Check if input is within range
    if (inputNum < 0 || inputNum > focusZone->size())
    {
        std::cerr << "Invalid input" << std::endl;
        return false;
    }

    // Undo padding for ease of use
    inputNum--;

    CardManager::Card playedCard = focusZone->at(inputNum);
    focusZone->erase(focusZone->begin() + inputNum);
    playedCard.embuedColors = {0, 0, 0};
    playedCard.isEmbued = false;
    discardZone->push_back(playedCard);
    return false;
}

const void startUp()
{
    // TODO: Replace with SDL
    srand(time(0));

    CardManager::getInstance()->startUp();
    PlayerManager::getInstance()->startUp();
}

const void shutDown()
{
    PlayerManager::getInstance()->shutDown();
    CardManager::getInstance()->shutDown();
}