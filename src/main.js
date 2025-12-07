let deckId = null;
let playerHand = [];
let computerHand = [];
let playerScore = 0;
let computerScore = 0;
let currentTrick = { player: null, computer: null }; // Cards played in current trick
let requestedSuit = null; // The suit that was requested for this trick
let isPlayerTurn = true; // Who starts/leads the trick
let tricksWon = { player: 0, computer: 0 }; // Tracks tricks won in current round

// Set up deal button event listener
document.getElementById("deal").addEventListener("click", dealCards);

// Set up player card click listeners
document.getElementById("player-hand").addEventListener("click", (e) => {
  if (e.target.tagName === "IMG") {
    const cardIndex = Array.from(e.target.parentElement.children).indexOf(
      e.target
    );
    handlePlayerCardClick(cardIndex);
  }
});

/**
 * Fetches a new shuffled deck from the Deck of Cards API
 * @returns {Promise<string>} The deck ID
 */
async function fetchNewDeck() {
  try {
    const response = await fetch(
      "https://deckofcardsapi.com/api/deck/new/shuffle/?deck_count=1"
    );
    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`);
    }
    const data = await response.json();
    if (!data.success) {
      throw new Error("Failed to create a new deck");
    }
    deckId = data.deck_id;
    console.log("New deck created with ID:", deckId);
    return deckId;
  } catch (error) {
    console.error("Error fetching new deck:", error.message);
    throw error;
  }
}

/**
 * Draws cards from the deck
 * @param {number} count - Number of cards to draw
 * @returns {Promise<Array>} Array of card objects
 */
async function drawCards(count) {
  try {
    if (!deckId) {
      throw new Error("No deck available. Please create a deck first.");
    }
    const response = await fetch(
      `https://deckofcardsapi.com/api/deck/${deckId}/draw/?count=${count}`
    );
    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`);
    }
    const data = await response.json();
    if (!data.success) {
      throw new Error("Failed to draw cards");
    }
    return data.cards;
  } catch (error) {
    console.error("Error drawing cards:", error.message);
    throw error;
  }
}

/**
 * Sorts cards by suit and rank (highest to lowest within each suit)
 */
function sortCards(cards) {
  const suitOrder = { SPADES: 0, HEARTS: 1, DIAMONDS: 2, CLUBS: 3 };
  const valueOrder = {
    ACE: 14,
    KING: 13,
    QUEEN: 12,
    JACK: 11,
    10: 10,
    9: 9,
    8: 8,
    7: 7,
    6: 6,
    5: 5,
    4: 4,
    3: 3,
    2: 2,
  };

  return cards.sort((a, b) => {
    // First sort by suit
    const suitDiff = suitOrder[a.suit] - suitOrder[b.suit];
    if (suitDiff !== 0) return suitDiff;
    // Then sort by value (highest to lowest)
    return valueOrder[b.value] - valueOrder[a.value];
  });
}

/**
 * Deals cards to player and computer
 */
async function dealCards() {
  try {
    // Fetch a new deck if we don't have one
    if (!deckId) {
      await fetchNewDeck();
    }
    // Draw 10 cards
    const cards = await drawCards(10);
    // Split cards between player and computer (alternating)
    playerHand = [];
    computerHand = [];
    for (let i = 0; i < cards.length; i++) {
      if (i % 2 === 0) {
        playerHand.push(cards[i]);
      } else {
        computerHand.push(cards[i]);
      }
    }

    // Sort player's cards
    playerHand = sortCards(playerHand);

    console.log("Player hand:", playerHand);
    console.log("Computer hand:", computerHand);
    // Update the UI
    updateHands();
    // Remove opacity from hands to show cards are dealt
    document.getElementById("player-hand").style.opacity = "1";
    document.getElementById("computer-hand").style.opacity = "1";

    // Reset trick state
    currentTrick = { player: null, computer: null };
    requestedSuit = null;
    tricksWon = { player: 0, computer: 0 };
    clearPlayedCards();

    // Player goes first
    isPlayerTurn = true;
    console.log("Player's turn to lead. Click a card to play it.");
  } catch (error) {
    console.error("Error dealing cards:", error.message);
  }
}

/**
 * Updates the card images in the UI
 */
function updateHands() {
  const playerHandDiv = document.getElementById("player-hand");
  const computerHandDiv = document.getElementById("computer-hand");
  // Update player hand
  const playerImages = playerHandDiv.querySelectorAll("img");
  playerHand.forEach((card, index) => {
    if (playerImages[index]) {
      playerImages[index].src = card.image;
      playerImages[index].alt = `${card.value} of ${card.suit}`;
      playerImages[index].style.cursor = "pointer";
      playerImages[index].style.opacity = "1";
      playerImages[index].style.visibility = "visible";
    }
  });
  // Show card backs with opacity for empty slots in player hand
  for (let i = playerHand.length; i < 5; i++) {
    if (playerImages[i]) {
      playerImages[i].src = "https://deckofcardsapi.com/static/img/back.png";
      playerImages[i].alt = "Card back";
      playerImages[i].style.opacity = "0.3";
      playerImages[i].style.visibility = "visible";
      playerImages[i].style.cursor = "default";
    }
  }
  // Update computer hand (show card backs)
  const computerImages = computerHandDiv.querySelectorAll("img");
  computerHand.forEach((card, index) => {
    if (computerImages[index]) {
      computerImages[index].src =
        "https://deckofcardsapi.com/static/img/back.png";
      computerImages[index].alt = "Card back";
      computerImages[index].style.opacity = "1";
      computerImages[index].style.visibility = "visible";
    }
  });
  // Show card backs with opacity for empty slots in computer hand
  for (let i = computerHand.length; i < 5; i++) {
    if (computerImages[i]) {
      computerImages[i].src = "https://deckofcardsapi.com/static/img/back.png";
      computerImages[i].alt = "Card back";
      computerImages[i].style.opacity = "0.3";
      computerImages[i].style.visibility = "visible";
    }
  }
}

/**
 * Handles when player clicks a card to play it
 */
function handlePlayerCardClick(cardIndex) {
  if (cardIndex >= playerHand.length) return;
  if (!isPlayerTurn && requestedSuit !== null) {
    // Computer already played, player must respond
    playPlayerCard(cardIndex);
  } else if (isPlayerTurn && requestedSuit === null) {
    // Player leads by choosing suit
    playPlayerCard(cardIndex);
  }
}

/**
 * Player plays a card
 */
function playPlayerCard(cardIndex) {
  const card = playerHand[cardIndex];

  // If responding to a requested suit, validate the play
  if (requestedSuit !== null && !isPlayerTurn) {
    const hasRequestedSuit = playerHand.some((c) => c.suit === requestedSuit);
    if (hasRequestedSuit && card.suit !== requestedSuit) {
      console.log("You must play a card of the requested suit!");
      return;
    }
  }

  // If player is leading, set the requested suit
  if (requestedSuit === null) {
    requestedSuit = card.suit;
    console.log(`Player requests ${requestedSuit}`);
  }

  // Play the card
  currentTrick.player = card;
  playerHand.splice(cardIndex, 1);
  updateHands();
  displayPlayedCard(card, "player");

  // If computer hasn't played yet, make computer play
  if (currentTrick.computer === null) {
    setTimeout(() => computerPlay(), 1000);
  } else {
    // Both played, resolve trick
    setTimeout(() => resolveTrick(), 1000);
  }
}

/**
 * Computer plays a card
 */
function computerPlay() {
  let cardToPlay;

  if (requestedSuit === null) {
    // Computer leads - pick a random card
    cardToPlay = computerHand[Math.floor(Math.random() * computerHand.length)];
    requestedSuit = cardToPlay.suit;
    console.log(`Computer requests ${requestedSuit}`);
  } else {
    // Computer responds to requested suit
    const cardsOfSuit = computerHand.filter((c) => c.suit === requestedSuit);
    if (cardsOfSuit.length > 0) {
      // Try to play a higher card if possible
      const sortedSuit = sortCards(cardsOfSuit);
      cardToPlay = sortedSuit[0]; // Play highest card of suit
    } else {
      // No card of requested suit, play any card
      cardToPlay = computerHand[0];
    }
  }

  // Play the card
  currentTrick.computer = cardToPlay;
  const cardIndex = computerHand.indexOf(cardToPlay);
  computerHand.splice(cardIndex, 1);
  updateHands();
  displayPlayedCard(cardToPlay, "computer");

  // If player hasn't played yet, wait for player
  if (currentTrick.player === null) {
    // Player's turn to respond
    return;
  } else {
    // Both played, resolve trick
    setTimeout(() => resolveTrick(), 1000);
  }
}

/**
 * Display a played card in the center area
 */
function displayPlayedCard(card, player) {
  // Swap positions: player cards on right, computer cards on left
  const cardDiv =
    player === "player"
      ? document.getElementById("computer-card")
      : document.getElementById("player-card");
  const img = cardDiv.querySelector("img");
  img.src = card.image;
  img.alt = `${card.value} of ${card.suit}`;
  cardDiv.style.opacity = "1";
}

/**
 * Determines the winner of the current trick
 */
function resolveTrick() {
  const playerCard = currentTrick.player;
  const computerCard = currentTrick.computer;

  let winner;

  // Get value rankings
  const valueOrder = {
    ACE: 14,
    KING: 13,
    QUEEN: 12,
    JACK: 11,
    10: 10,
    9: 9,
    8: 8,
    7: 7,
    6: 6,
    5: 5,
    4: 4,
    3: 3,
    2: 2,
  };

  // Check if both cards are of the requested suit
  const playerHasRequestedSuit = playerCard.suit === requestedSuit;
  const computerHasRequestedSuit = computerCard.suit === requestedSuit;

  if (playerHasRequestedSuit && !computerHasRequestedSuit) {
    winner = "player";
  } else if (!playerHasRequestedSuit && computerHasRequestedSuit) {
    winner = "computer";
  } else if (playerHasRequestedSuit && computerHasRequestedSuit) {
    // Both have requested suit, compare values
    if (valueOrder[playerCard.value] > valueOrder[computerCard.value]) {
      winner = "player";
    } else {
      winner = "computer";
    }
  } else {
    // Neither has requested suit - whoever led wins
    winner = isPlayerTurn ? "player" : "computer";
  }

  console.log(`${winner} wins the trick!`);

  // Track tricks won
  tricksWon[winner]++;

  // Winner leads next trick
  isPlayerTurn = winner === "player";

  // Clear the trick
  setTimeout(() => {
    clearPlayedCards();
    currentTrick = { player: null, computer: null };
    requestedSuit = null;

    // Check if round is over (no more cards)
    if (playerHand.length === 0) {
      endRound();
    } else {
      // Start next trick
      if (!isPlayerTurn) {
        computerPlay();
      }
    }
  }, 2000);
}

/**
 * Clear played cards from the center area
 */
function clearPlayedCards() {
  document.getElementById("player-card").style.opacity = "0";
  document.getElementById("computer-card").style.opacity = "0";
}

/**
 * End the current round and award points
 */
function endRound() {
  console.log(
    `Round over! Player tricks: ${tricksWon.player}, Computer tricks: ${tricksWon.computer}`
  );

  // Award point to winner of last trick
  if (tricksWon.player > tricksWon.computer) {
    playerScore++;
  } else if (tricksWon.computer > tricksWon.player) {
    computerScore++;
  }

  // Update score display
  document.getElementById(
    "score"
  ).textContent = `${playerScore}-${computerScore}`;

  // Reset for next round
  tricksWon = { player: 0, computer: 0 };
  isPlayerTurn = true;

  // Check if game is won
  if (playerScore >= 3) {
    console.log("Player wins the game!");
    alert("You win the game!");
  } else if (computerScore >= 3) {
    console.log("Computer wins the game!");
    alert("Computer wins the game!");
  }
}
