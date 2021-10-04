#include <Card.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <vector>

using std::cout;
using std::endl;

struct GameState {
  std::vector<Card> pile;
  std::array<std::set<Card>, 4> hands;
  int playerToMove;
  int trickSize;
  CardSuit currentCardSuit;

  GameState() : playerToMove(0), trickSize(0), currentCardSuit(CardSuit::Any) {
    auto allCards = getAllCards();
    std::mt19937 g(0);
    std::shuffle(allCards.begin(), allCards.end(), g);
    auto it = allCards.begin();
    for (auto &hand : hands) {
      hand = std::set<Card>(it, it + 10);
      it = it + 10;
    }
  }
};

struct Action {
  Card cardPlayed;
  int player;
  CardSuit cs;
  Action(Card cardPlayed, int player, CardSuit cs)
      : cardPlayed(cardPlayed), player(player), cs(cs) {}
};

struct Solver {
  GameState gs;
  std::vector<Action> actions;
  GameState solutionGameState;
  std::vector<Action> solutionActions;
  int counter;
  bool run;
  std::chrono::time_point<std::chrono::steady_clock> start;


  Solver() : counter(0), run(true) {
    start = std::chrono::steady_clock::now();
  }

  void solve() {
    if (!run) {
      return;
    }
    counter++;
    /* if (counter > 40) { */
    /*   run = false; */
    /* } */
    if (counter % 1000000 == 0) {
      auto callTime = std::chrono::steady_clock::now();
      cout << "seconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(callTime - start).count()/1000.0 << endl;
      cout << "counter: " << counter << endl;
      printState();
    }

    std::array<Card, 10> possibleCards;
    auto possibleCardsEnd = possibleCards.begin();
    getPossibleCards(possibleCards, possibleCardsEnd);
    for (auto possibleCardsIt = possibleCards.begin();
         possibleCardsIt != possibleCardsEnd; possibleCardsIt++) {
      perform(*possibleCardsIt);
      solve();
      unperform();
    }
  }

  void printState() {
    cout << "    printState()" << endl;
    cout << "currentCardSuit: " << cardSuitToString(gs.currentCardSuit) << endl;
    cout << "hands=[";
    for (const auto &hand : gs.hands) {
      cout << "[";
      for (Card c : hand) {
        cout << cardToString(c);
        if (c != *hand.rbegin()) {
          cout << ",";
        }
      }
      cout << "]";
      if (hand != gs.hands.back()) {
        cout << ",";
      }
    }
    cout << "]" << endl;
    cout << "pile=[";
    for (Card c : gs.pile) {
      cout << cardToString(c);
      if (c != gs.pile.back()) {
        cout << ", ";
      }
    }
    cout << "]" << endl;
    cout << "trickSize: " << gs.trickSize << endl;
    cout << "actions=[";
    for (Action a : actions) {
      cout << "{" << cardToString(a.cardPlayed) << "," << a.player << "}";
      if (a.cardPlayed != actions.back().cardPlayed) {
        cout << ", ";
      }
    }
    cout << "]" << endl;
  }
  void getPossibleCards(std::array<Card, 10> &possibleCards,
                        std::array<Card, 10>::iterator &possibleCardsEnd) {
    const auto &hand = gs.hands.at(gs.playerToMove);
    possibleCardsEnd = std::copy_if(
        hand.begin(), hand.end(), possibleCardsEnd,
        [this](Card c) { return suitMatches(c, gs.currentCardSuit); });

    if (possibleCardsEnd == possibleCards.begin()) {
      possibleCardsEnd = std::copy(hand.begin(), hand.end(), possibleCardsEnd);
    }
  }

  void perform(const Card c) {
    auto &hand = gs.hands.at(gs.playerToMove);
    hand.erase(c);
    gs.pile.push_back(c);
    actions.emplace_back(c, gs.playerToMove, gs.currentCardSuit);
    if (gs.currentCardSuit == CardSuit::Any) {
      gs.currentCardSuit = getCardSuit(c);
    }
    if (gs.trickSize == 3) {
      int winner = 0; // TODO
      gs.playerToMove = winner;
      gs.currentCardSuit = CardSuit::Any;
    } else {
      gs.playerToMove = (gs.playerToMove + 1) % 4;
    }
    gs.trickSize = (gs.trickSize + 1) % 4;
  }

  void unperform() {
    Action a = actions.back();
    auto &hand = gs.hands.at(a.player);
    hand.insert(a.cardPlayed);
    gs.playerToMove = a.player;
    gs.currentCardSuit = a.cs;
    gs.trickSize = (gs.trickSize+3)%4;
    gs.pile.pop_back();
    actions.pop_back();
  }
};

int main() {
  Solver solver;
  solver.solve();
  cout << solver.counter << endl;
  /* solver.printState(); */
  return 0;
}
