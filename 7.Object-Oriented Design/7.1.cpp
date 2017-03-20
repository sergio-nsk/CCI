// Deck of Cards: Design the data structures for a generic deck of cards. Explain how you would
// subclass the data structures to implement blackjack.

#include <type_traits>
#include <array>
#include <algorithm>
#include <vector>

enum class Suit
{
    Club,    // ♣
    Heart,   // ♥
    Diamond, // ♦
    Spade    // ♠
};

// Standard 52 cards deck
enum class Value
{
    Ace = 1,
    Jack = 11,
    Queen = 12,
    King = 13
};

class Card
{
public:
    Card(int faceValue, Suit suit) : _faceValue(faceValue), _suit(suit)
    {
    }
    virtual ~Card()
    {
    }

    virtual int value() const
    {
        return _faceValue;
    }

    Suit suit() const
    {
        return _suit;
    }

    bool isAvailable() const
    {
        return _isAvailable;
    }

    void markUnavailable()
    {
        _isAvailable = false;
    }

protected:
    int _faceValue;
    Suit _suit;

private:
    bool _isAvailable = true;
};

template<typename T, typename = std::enable_if<std::is_base_of<Card, T>::value>>
class Deck
{
    std::vector<T> cards;
    int firstNotDealt = 0;

public:
    Deck()
    {
        cards.reserve(52);
        /// fill cards
    }

    void shuffle()
    {
        std::shuffle(cards.begin() + firstNotDealt, cards.end());
    }

    int remainingCards() const
    {
        return cards.size() - firstNotDealt;
    }

    std::vector<T> dealHand(int count)
    {
        if (remainingCards() < count)
            return nullptr;
        std::vector<T> handCards(&cards[firstNotDealt], &cards[firstNotDealt] + count);
        firstNotDealt += count;
        return handCards;
    }

    T dealCard()
    {
        if (remainingCards() < 1)
            return T();
        return cards[firstNotDealt++];
    }
};

template<typename T, typename = std::enable_if<std::is_base_of<Card, T>::value>>
class Hand
{
    std::vector<T> cards;

public:
    int score()
    {
        return std::accumulate(cards.begin(), cards.end(), 0, [](int &sum, T &card) { return sum + card.value(); });
    }

    void addCard(T &card)
    {
        cards.push_back(card);
    }

    void addCards(std::vector<T> &&dealtCards)
    {
        cards.insert(cards.end(), std::make_move_iterator(dealtCards.begin()), std::make_move_iterator(dealtCards.end()));
    }
};

class BlackJackCard : public Card
{
public:
    BlackJackCard(int value, Suit suit) : Card(value, suit)
    {
    }

    virtual int value() const override
    {
        if (isAce())
            return 1;
        else if (_faceValue >= 11 && _faceValue <= 13)
            return 10;
        else
            return _faceValue;
    }

    int minValue() const
    {
        if (isAce())
            return 1;
        else
            return value();
    }

    int maxValue() const
    {
        if (isAce())
            return 11;
        else
            return value();
    }

    bool isAce() const
    {
        return _faceValue == 1;
    }
    bool isFaceCard() const
    {
        return _faceValue >= 11 && _faceValue <= 13;
    }
};

int main()
{
    Deck<BlackJackCard> deck;
    Hand<BlackJackCard> hand;
    hand.score();
}

