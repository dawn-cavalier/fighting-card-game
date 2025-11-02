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

/**
 * @brief Shuffles the given deck.
 *
 * @param deck
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
    drawZone = masterDeck;
    // Shuffle
    shuffle(drawZone);

    /// Start of turn
    // Draw hand
    for (auto i = 0; i < 5; i++)
    {
        // Reshuffle if deck is draw pile
        if (drawZone.empty())
        {
            drawZone = discardZone;
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

    // Inhale
    // Could we make the inputs into an enum
    std::string input = "";
    int inputNum = -1;
    std::cout << "Inhale Phase" << std::endl;
    // This should be the game loop with a state machine inside it
    while (true)
    {
        std::cout << "(" << 0 << "): " << "End Inhale Phase" << std::endl;
        for (int i = 0; i < handZone.size(); i++)
        {
            std::cout << "(" << i + 1 << "): " << handZone.at(i).name << std::endl;
        }

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

        if (inputNum == 0)
        {
            break;
        }

        std::cout << handZone.at(inputNum - 1).name << std::endl;
    }

    // Exhale
    std::cout << "Exhale Phase" << std::endl;
    /// !Playing cards that are not charged discards them
    // Discard
    std::cout << "Discard Phase" << std::endl;

    return 0;
}