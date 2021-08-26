SUITS = ["PINK", "BLUE", "GREEN", "YELLOW"]
ROCKET = "ROCKET"

from itertools import product
from random import shuffle


class Card:
    def __init__(self, suit, number):
        self.suit = suit
        self.number = number

    def __str__(self):
        return f"{self.number} {self.suit}"

    def __repr__(self):
        return str(self)

    def beats(self, other, current_suit):
        if self.suit == other.suit:
            return self.number > other.number
        if self.suit == ROCKET or self.suit == current_suit:
            return True
        if other.suit == ROCKET or other.suit == current_suit:
            return False


class Deck:
    def __init__(self):
        self.cards = [
            Card(suit, number) for suit, number in product(SUITS, range(1, 10))
        ] + [Card(ROCKET, number) for number in range(1, 5)]
        assert len(self.cards) == 40

    def shuffle(self):
        shuffle(self.cards)

    def deal(self, num_players):
        assert 2 <= num_players <= 5
        n = 40 // num_players
        return [self.cards[i : i + n] for i in range(0, 40, n)]


class Game:
    def __init__(self, num_players=4):
        self.num_players = num_players
        deck = Deck()
        deck.shuffle()
        self.player_hands = deck.deal(num_players)
        deck.shuffle()
        self.tasks = [card for card in deck.cards[:num_players]]

    def print_description(self):
        for i in range(self.num_players):
            print(f"Player {i} started with")
            print(
                ", ".join(
                    str(card)
                    for card in sorted(
                        self.player_hands[i], key=lambda c: c.suit + str(c.number)
                    )
                )
            )

    def is_winnable(self):
        fringe = [[]]
        while fringe:
            state = fringe.pop()
            leader = 0
            suit = None
            task = None
            win = True
            task_count = 0
            for i, card in enumerate(state):
                if card in self.tasks:
                    if task is None:
                        task = self.tasks.index(card)
                    else:
                        win = False
                if i % self.num_players == 0:
                    suit = card.suit
                    top_card = i
                else:
                    if card.beats(state[top_card], suit):
                        top_card = i
                if i % self.num_players == self.num_players - 1:
                    suit = None
                    leader = (leader + top_card) % self.num_players
                    if task is not None:
                        if task != leader:
                            win = False
                        else:
                            task_count += 1
                    task = None
                # if len(state) == 40:
                #     print(i, card, suit, leader)

            if not win:
                continue
            cards_not_yet_played = [
                card
                for card in self.player_hands[(leader + len(state)) % self.num_players]
                if card not in state
            ]
            cards = [card for card in cards_not_yet_played if card.suit == suit]
            # print(cards)
            if len(cards) == 0:
                cards = cards_not_yet_played

            if len(state) == 40:
                print(state)
                print(task_count)
                break
            for card in cards:
                fringe.append(state + [card])
        return True


game = Game()
print(game.player_hands)
game.print_description()
print(game.is_winnable())
