#include <Card.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>

using std::cout;
using std::endl;

struct GameState {
  GameState() {
    cards = getAllCards();
    // deterministic shuffling
    std::mt19937 g(0);
    std::shuffle(cards.begin(), cards.end(), g);
    hand0EndHand1Begin = cards.begin() + 10;
    hand1EndHand2Begin = hand0EndHand1Begin + 10;
    hand2EndHand3Begin = hand1EndHand2Begin + 10;
    hand3EndPlayedBegin = hand2EndHand3Begin + 10;
    playerToMove = 0;
  }
  GameState(GameState &other, Card cardPlayed, int playerToMove): playerToMove(playerToMove) {
    hand0EndHand1Begin = std::copy_if(
        other.cards.begin(), other.hand0EndHand1Begin, cards.begin(),
        [&cardPlayed](const Card &c) { return c == cardPlayed; });
    hand1EndHand2Begin = std::copy_if(
        other.hand0EndHand1Begin, other.hand1EndHand2Begin, hand0EndHand1Begin,
        [&cardPlayed](const Card &c) { return c == cardPlayed; });
    hand2EndHand3Begin = std::copy_if(
        other.hand1EndHand2Begin, other.hand2EndHand3Begin, hand1EndHand2Begin,
        [&cardPlayed](const Card &c) { return c == cardPlayed; });
    hand3EndPlayedBegin = std::copy_if(
        other.hand2EndHand3Begin, other.hand3EndPlayedBegin, hand2EndHand3Begin,
        [&cardPlayed](const Card &c) { return c == cardPlayed; });
    *(cards.end()-1) = cardPlayed;
  }
  std::array<Card, 40> cards;
  std::array<Card, 40>::iterator hand0EndHand1Begin;
  std::array<Card, 40>::iterator hand1EndHand2Begin;
  std::array<Card, 40>::iterator hand2EndHand3Begin;
  std::array<Card, 40>::iterator hand3EndPlayedBegin;
  int playerToMove;
};

void playGame() { auto startGameState = GameState(); }

void playGame(GameState &gs) {
  const auto begin = gs.playerToMove == 0
                         ? gs.cards.begin()
                         : gs.playerToMove == 1
                               ? gs.hand0EndHand1Begin
                               : gs.playerToMove == 2 ? gs.hand1EndHand2Begin
                                                      : gs.hand2EndHand3Begin;
  const auto end = gs.playerToMove == 0
                       ? gs.hand0EndHand1Begin
                       : gs.playerToMove == 1
                             ? gs.hand1EndHand2Begin
                             : gs.playerToMove == 2 ? gs.hand2EndHand3Begin
                                                    : gs.hand3EndPlayedBegin;

  const int trickSize = (gs.cards.end() - gs.hand3EndPlayedBegin) % 4;

  CardSuit playableSuit;
  if (trickSize == 0) {
    playableSuit = CardSuit::Any;
  } else {
    playableSuit = getCardSuit(*(gs.cards.end() - trickSize));
    if (std::find_if(begin, end, [playableSuit](Card c){ return suitMatches(c, playableSuit); }) == end) {
      playableSuit = CardSuit::Any;
    }
  }

  for (auto cardIt = begin; cardIt != end; cardIt++) {
    if (suitMatches(*cardIt, playableSuit)) {
      auto newGameState = GameState(gs, *cardIt);
      playGame(newGameState);
    }
  }
}

int main() {
  auto startState = GameState();
  playGame(startState);
  return 0;
}
