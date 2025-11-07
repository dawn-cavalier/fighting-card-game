#include "game-state-manager.h"

GameStateManager::GameStateManager()
{
}

int GameStateManager::pollUserInput()
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

bool GameStateManager::inhaleIteration()
{
    auto focusZone = &playerRef->focusZone;
    auto handZone = &playerRef->handZone;
    auto discardZone = &playerRef->discardZone;
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

bool GameStateManager::exhaleIteration()
{
    auto focusZone = &playerRef->focusZone;
    auto handZone = &playerRef->handZone;
    auto discardZone = &playerRef->discardZone;

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

bool GameStateManager::playIteration()
{
    auto focusZone = &playerRef->focusZone;
    auto handZone = &playerRef->handZone;
    auto discardZone = &playerRef->discardZone;

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

GameStateManager *GameStateManager::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new GameStateManager();
    }
    return instancePtr;
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::startUp()
{
    playerRef = PlayerManager::getInstance();
    cardRef = CardManager::getInstance();
    state = GameSetUp;
}

void GameStateManager::shutDown()
{
}

bool GameStateManager::processState()
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
        return false;
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
        if (inhaleIteration())
        {
            std::cout << "Exhale Phase" << std::endl;
            state = FightExhale;
        };
        break;
    case FightExhale:
        if (exhaleIteration())
        {
            state = FightPlay;
        }
        break;
    case FightPlay:
        if (playIteration())
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
    return true;
}
