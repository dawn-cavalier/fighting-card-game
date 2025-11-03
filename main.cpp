#include <string>
#include <vector>
#include <iostream>

// TODO: Replace with SDL Random
#include <random>

#include "./enums/GameState.enum.cpp"

struct Card
{
    std::string name;
    unsigned int damage;
    unsigned int block;
    unsigned int evade;
};

/**
 * @brief   Shuffles the given deck.
 *
 * @param   deck
 */
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

/**
 * @brief Request and converts user's input into a number.
 *
 * @return int
 */
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
    return inputNum;
}

/**
 * @brief   Executes one interation of the inhale phase and returns if the phase should end.
 *
 * @param   handZone
 * @param   focusZone
 * @return  true
 * @return  false
 */
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
/**
 * @brief   Executes one interation of the exhale phase and returns if the phase should end.
 *
 * @param   handZone
 * @param   focusZone
 * @param   discardZone
 * @return  true
 * @return  false
 */
bool exhaleIteration(std::vector<Card> &handZone, std::vector<Card> &focusZone, std::vector<Card> &discardZone)
{
    int inputNum = -1;

    std::cout << "Focused Cards:" << std::endl;
    for (int i = 0; i < focusZone.size(); i++)
    {
        std::cout << focusZone.at(i).name << std::endl;
    }

    std::cout << "Hand:" << std::endl;
    std::cout << "(" << 0 << "): " << "End Exhale Phase" << std::endl;
    for (int i = 0; i < handZone.size(); i++)
    {
        std::cout << "(" << i + 1 << "): " << handZone.at(i).name << std::endl;
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

    Card hold = handZone.at(inputNum);
    handZone.erase(handZone.begin() + inputNum);
    discardZone.push_back(hold);
    return false;
}

/**
 * @brief Executes one interation of the play phase and returns if the phase should end.
 * 
 * @param focusZone 
 * @param discardZone 
 * @return true 
 * @return false 
 */
bool playIteration(std::vector<Card> &focusZone, std::vector<Card> &discardZone)
{
    int inputNum = -1;

    std::cout << "Focused Cards:" << std::endl;
    std::cout << "(" << 0 << "): " << "End Exhale Phase" << std::endl;
    for (int i = 0; i < focusZone.size(); i++)
    {
        std::cout << "(" << i + 1 << "): " << focusZone.at(i).name << std::endl;
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

    Card hold = focusZone.at(inputNum);
    focusZone.erase(focusZone.begin() + inputNum);
    discardZone.push_back(hold);
    return false;
}

int main()
{
    // TODO: Replace
    srand(time(0));

    std::vector<Card> masterDeck = {};
    std::vector<Card> drawZone = {};
    std::vector<Card> discardZone = {};
    std::vector<Card> handZone = {};
    std::vector<Card> focusZone = {};

    // TODO: Move to a card list file
    Card block = {"Block", 0, 1, 0};
    Card bash = {"Bash", 2, 1, 0};
    Card feint = {"Feint", 0, 0, 1};
    Card punch = {"Punch", 1, 0, 0};
    Card bigPunch = {"Punch", 3, 0, 0};

    GameState state = GameSetUp;
    // Start of Game Loop
    bool running = true;
    while (true)
    {
        switch (state)
        {
        case GameSetUp:
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
            state = FightStart;
            break;
        case GameShutDown:
            running = false;
            break;
        case FightStart:
            drawZone = masterDeck;
            // Shuffle
            shuffle(drawZone);
            state = FightTurnStart;
            break;
        case FightTurnStart:
            for (auto i = 0; i < 5; i++)
            {
                // Reshuffle if deck is draw pile
                if (drawZone.empty())
                {
                    drawZone = discardZone;
                    discardZone = {};
                    shuffle(drawZone);
                }

                // If draw pile is still empty, player doesn't draw anymore cards
                if (drawZone.empty())
                {
                    break;
                }
                handZone.push_back(drawZone.back());
                drawZone.pop_back();
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
            state = FightTurnEnd;
            break;
        case FightTurnEnd:
            std::cout << "Press 0 to end fight" << std::endl;
            if (pollUserInput() == 0)
            {
                state = GameShutDown;
            }
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
    /// Start of turn
    // Inhale
    // This should be the game loop with a state machine inside it

    // Exhale
    std::cout << "Exhale Phase" << std::endl;
    /// !Playing cards that are not charged discards them
    // Discard
    std::cout << "Discard Phase" << std::endl;

    return 0;
}