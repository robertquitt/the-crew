#include <array>
#include <iostream>

enum class Card {
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
  Pink1,
  Pink2,
  Pink3,
  Pink4,
  Pink5,
  Pink6,
  Pink7,
  Pink8,
  Pink9,
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
	Blue,
	Green,
	Pink,
	Yellow,
	Rocket,
	Any,
};


std::array<Card, 40> getAllCards() {
  return std::array<Card, 40>{
      Card::Rocket1, Card::Rocket2, Card::Rocket3, Card::Rocket4, Card::Pink1,
      Card::Pink2,    Card::Pink3,    Card::Pink4,    Card::Pink5,    Card::Pink6,
      Card::Pink7,    Card::Pink8,    Card::Pink9,    Card::Blue1,   Card::Blue2,
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
  case CardSuit::Pink:
    return Card::Pink1 <= c && c <= Card::Pink9;
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
  switch((int)c/9) {
	  case 0:
		  return CardSuit::Blue;
	  case 1:
		  return CardSuit::Green;
	  case 2:
		  return CardSuit::Pink;
	  case 3:
		  return CardSuit::Yellow;
	  case 4:
		  return CardSuit::Rocket;
  }
}
std::string cardSuitToString(CardSuit cs) {
	switch (cs) {
	case CardSuit::Blue:
		return "B";
	case CardSuit::Green:
		return "G";
	case CardSuit::Pink:
		return "P";
	case CardSuit::Yellow:
		return "Y";
	case CardSuit::Rocket:
		return "R";
	case CardSuit::Any:
		return "Any";
	}
}
std::string cardToString(Card c) {
	CardSuit cs = getCardSuit(c);
	Card card1;
	std::string suit;
	switch (cs) {
	case CardSuit::Blue:
		card1 = Card::Blue1;
		suit = "B";
		break;
	case CardSuit::Green:
		card1 = Card::Green1;
		suit = "G";
		break;
	case CardSuit::Pink:
		card1 = Card::Pink1;
		suit = "P";
		break;
	case CardSuit::Yellow:
		card1 = Card::Yellow1;
		suit = "Y";
		break;
	case CardSuit::Rocket:
		card1 = Card::Rocket1;
		suit = "R";
		break;
	}
	int number = (int)c - (int)card1 + 1;
	return suit + std::to_string(number);
}
