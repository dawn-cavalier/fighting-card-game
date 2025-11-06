#include <string>
#include <vector>
#include <iostream>

// TODO: Replace with SDL Random
#include <random>
#include "./src/master-card-list.cpp"

#include "./src/managers/card-manager/card-manager.h"
// TODO: These should be linked automatically but for some reason they are not
#include "./src/managers/card-manager/card-manager.cpp"

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
 * @brief   Shuffles the given deck.
 *
 * @param   deck
 */
void shuffle(std::vector<Card> &deck);

/**
 * @brief Draws a card from the deck into the hand and reshuffles the discard pile into the deck if necessary.
 *
 * @param handZone
 * @param deckZone
 * @param discardZone
 */
void drawCard(std::vector<Card> &handZone, std::vector<Card> &deckZone, std::vector<Card> &discardZone);

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
bool inhaleIteration(std::vector<Card> &handZone, std::vector<Card> &focusZone);

/**
 * @brief   Executes one interation of the exhale phase and returns if the phase should end.
 *
 * @param   handZone
 * @param   focusZone
 * @param   discardZone
 * @return  true
 * @return  false
 */
bool exhaleIteration(std::vector<Card> &handZone, std::vector<Card> &focusZone, std::vector<Card> &discardZone);

/**
 * @brief Executes one interation of the play phase and returns if the phase should end.
 *
 * @param focusZone
 * @param discardZone
 * @return true
 * @return false
 */
bool playIteration(std::vector<Card> &focusZone, std::vector<Card> &discardZone);

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

CardManager* CardManager::instancePtr = nullptr;

int main(int argCount, char* argVariables[])
{
    // auto cardRef = CardManager::getInstance();
    // TODO: Replace
    startUp();

    std::vector<Card> masterDeck = {};
    std::vector<Card> deckZone = {};
    std::vector<Card> discardZone = {};
    std::vector<Card> handZone = {};
    std::vector<Card> focusZone = {};

    GameState state = GameSetUp;
    // Start of Game Loop
    bool running = true;
    while (true)
    {
        switch (state)
        {
        case GameSetUp:
            masterDeck = {};
            // TODO: Move to build starter deck function
            masterDeck.push_back(masterCardList.at(Block));
            masterDeck.push_back(masterCardList.at(Block));
            masterDeck.push_back(masterCardList.at(Bash));
            masterDeck.push_back(masterCardList.at(Feint));
            masterDeck.push_back(masterCardList.at(Feint));
            masterDeck.push_back(masterCardList.at(Punch));
            masterDeck.push_back(masterCardList.at(Punch));
            masterDeck.push_back(masterCardList.at(BigPunch));
            state = FightStart;
            break;
        case GameShutDown:
            running = false;
            break;
        case FightStart:
            deckZone = masterDeck;
            // Shuffle
            shuffle(deckZone);
            state = FightTurnStart;
            break;
        case FightTurnStart:
            for (auto i = 0; i < 5; i++)
            {
                drawCard(handZone, deckZone, discardZone);
            }
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
            for (Card card : handZone)
            {
                discardZone.push_back(card);
            }
            handZone = {};
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

void shuffle(std::vector<Card> &deck)
{
    for (auto index = 0; index < deck.size(); index++)
    {
        int newPosition = index + (rand() % (deck.size() - index));
        Card hold = deck.at(newPosition);
        deck.at(newPosition) = deck.at(index);
        deck.at(index) = hold;
    }
}

void drawCard(std::vector<Card> &handZone, std::vector<Card> &deckZone, std::vector<Card> &discardZone)
{
    // Reshuffle if deck is draw pile
    if (deckZone.empty())
    {
        deckZone = discardZone;
        discardZone = {};
        shuffle(deckZone);
    }

    // If draw pile is still empty, player doesn't draw anymore cards
    if (deckZone.empty())
    {
        return;
    }
    handZone.push_back(deckZone.back());
    deckZone.pop_back();
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

bool inhaleIteration(std::vector<Card> &handZone, std::vector<Card> &focusZone)
{
    int inputNum = -1;

    std::cout << "Focused Cards:" << std::endl;
    for (int i = 0; i < focusZone.size(); i++)
    {
        std::cout << focusZone.at(i).name << std::endl;
    }

    std::cout << "Hand:" << std::endl;
    std::cout << "(" << 0 << "): " << "End Inhale Phase" << std::endl;
    for (int i = 0; i < handZone.size(); i++)
    {
        std::cout << "(" << i + 1 << "): " << handZone.at(i).name << std::endl;
    }

    inputNum = pollUserInput();
    // User wishes to end the inhale phase, exit
    if (inputNum == 0)
    {
        return true;
    }

    // Check if input is within range
    if (inputNum < 0 || inputNum > handZone.size())
    {
        std::cerr << "Invalid input" << std::endl;
        return false;
    }

    // Undo padding for ease of use
    inputNum--;

    Card hold = handZone.at(inputNum);
    handZone.erase(handZone.begin() + inputNum);
    focusZone.push_back(hold);
    return false;
}

bool exhaleIteration(std::vector<Card> &handZone, std::vector<Card> &focusZone, std::vector<Card> &discardZone)
{
    int inputNum = -1;

    std::cout << "Focused Cards:" << std::endl;
    for (int i = 0; i < focusZone.size(); i++)
    {
        auto currentCard = focusZone.at(i);
        std::string imbuedMessage = "";

        imbuedMessage.append("(");
        imbuedMessage.append(std::to_string(currentCard.embuedColors.at(Red)));
        imbuedMessage.append("/");
        imbuedMessage.append(std::to_string(currentCard.cost.at(Red)));
        imbuedMessage.append(", ");
        imbuedMessage.append(std::to_string(currentCard.embuedColors.at(Green)));
        imbuedMessage.append("/");
        imbuedMessage.append(std::to_string(currentCard.cost.at(Green)));
        imbuedMessage.append(", ");
        imbuedMessage.append(std::to_string(currentCard.embuedColors.at(Blue)));
        imbuedMessage.append("/");
        imbuedMessage.append(std::to_string(currentCard.cost.at(Blue)));
        imbuedMessage.append(")");

        if (currentCard.isEmbued)
        {
            imbuedMessage.append(" (Ready!)");
        }

        std::cout << currentCard.name << ": " << imbuedMessage << std::endl;
    }

    std::cout << "Hand:" << std::endl;
    std::cout << "(" << 0 << "): " << "End Exhale Phase" << std::endl;
    for (int i = 0; i < handZone.size(); i++)
    {
        auto currentCard = handZone.at(i);
        std::string message = "";

        message.append("(");
        message.append(std::to_string(i + 1));
        message.append("): ");
        message.append(currentCard.name);
        message.append(": ");
        message.append("<");
        switch (currentCard.cardColor)
        {
        case Red:
            message.append("Red");
            break;
        case Green:
            message.append("Green");
            break;
        case Blue:
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
    if (inputNum < 0 || inputNum > handZone.size())
    {
        std::cerr << "Invalid input" << std::endl;
        return false;
    }

    // Undo padding for ease of use
    inputNum--;

    // Playing the Card and Imbuing the focused cards
    Card playedCard = handZone.at(inputNum);
    handZone.erase(handZone.begin() + inputNum);
    discardZone.push_back(playedCard);

    for (Card &card : focusZone)
    {
        // If full embued skip
        if (card.isEmbued)
        {
            continue;
        }

        card.embuedColors.at(playedCard.cardColor)++;
        card.isEmbued = card.embuedColors.at(Red) >= card.cost.at(Red) && card.embuedColors.at(Green) >= card.cost.at(Green) && card.embuedColors.at(Blue) >= card.cost.at(Blue);
    }

    return false;
}

bool playIteration(std::vector<Card> &focusZone, std::vector<Card> &discardZone)
{
    int inputNum = -1;

    std::cout << "Focused Cards:" << std::endl;
    std::cout << "(" << 0 << "): " << "End Exhale Phase" << std::endl;
    for (int i = 0; i < focusZone.size(); i++)
    {
        auto currentCard = focusZone.at(i);
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
    if (inputNum < 0 || inputNum > focusZone.size())
    {
        std::cerr << "Invalid input" << std::endl;
        return false;
    }

    // Undo padding for ease of use
    inputNum--;

    Card playedCard = focusZone.at(inputNum);
    focusZone.erase(focusZone.begin() + inputNum);
    playedCard.embuedColors = {0, 0, 0};
    playedCard.isEmbued = false;
    discardZone.push_back(playedCard);
    return false;
}

const void startUp()
{
    srand(time(0));
    CardManager::getInstance();   
}

const void shutDown()
{
    // CardManager::getInstance()->shutDown();
    
}