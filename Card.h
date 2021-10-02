#include <array>

enum class Card {
  Red1,
  Red2,
  Red3,
  Red4,
  Red5,
  Red6,
  Red7,
  Red8,
  Red9,
  Blue1,
  Blue2,
  Blue3,
  Blue4,
  Blue5,
  Blue6,
  Blue7,
  Blue8,
  Blue9,
  Green1,
  Green2,
  Green3,
  Green4,
  Green5,
  Green6,
  Green7,
  Green8,
  Green9,
  Yellow1,
  Yellow2,
  Yellow3,
  Yellow4,
  Yellow5,
  Yellow6,
  Yellow7,
  Yellow8,
  Yellow9,
  Rocket1,
  Rocket2,
  Rocket3,
  Rocket4,
};

enum class CardSuit {
	Red,
	Blue,
	Green,
	Yellow,
	Rocket,
	Any,
};


std::array<Card, 40> getAllCards() {
  return std::array<Card, 40>{
      Card::Rocket1, Card::Rocket2, Card::Rocket3, Card::Rocket4, Card::Red1,
      Card::Red2,    Card::Red3,    Card::Red4,    Card::Red5,    Card::Red6,
      Card::Red7,    Card::Red8,    Card::Red9,    Card::Blue1,   Card::Blue2,
      Card::Blue3,   Card::Blue4,   Card::Blue5,   Card::Blue6,   Card::Blue7,
      Card::Blue8,   Card::Blue9,   Card::Green1,  Card::Green2,  Card::Green3,
      Card::Green4,  Card::Green5,  Card::Green6,  Card::Green7,  Card::Green8,
      Card::Green9,  Card::Yellow1, Card::Yellow2, Card::Yellow3, Card::Yellow4,
      Card::Yellow5, Card::Yellow6, Card::Yellow7, Card::Yellow8, Card::Yellow9,
  };
}

bool suitMatches(Card c, CardSuit cs) {
  switch (cs) {
  case CardSuit::Rocket:
    return Card::Rocket1 <= c && c <= Card::Rocket4;
  case CardSuit::Red:
    return Card::Red1 <= c && c <= Card::Red9;
  case CardSuit::Blue:
    return Card::Blue1 <= c && c <= Card::Blue9;
  case CardSuit::Green:
    return Card::Green1 <= c && c <= Card::Green9;
  case CardSuit::Yellow:
    return Card::Yellow1 <= c && c <= Card::Yellow9;
  case CardSuit::Any:
    return true;
  }
}

CardSuit getCardSuit(Card c) {
  if (Card::Red1 <= c && c <= Card::Red9) {
    return CardSuit::Red;
  } else if (Card::Blue1 <= c && c <= Card::Blue9) {
    return CardSuit::Blue;
  } else if (Card::Green1 <= c && c <= Card::Green9) {
    return CardSuit::Green;
  } else if (Card::Yellow1 <= c && c <= Card::Yellow9) {
    return CardSuit::Yellow;
  } else {
    return CardSuit::Rocket;
  }
}
std::array<Card, 4>::iterator winner(const std::array<Card, 4> &cards, CardSuit cs) {
	if (cs == CardSuit::Rocket) {
		return std::max_element(cards.begin(), cards.end());
	}
}
