let deckId = null;

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

let playerHand = [];
let computerHand = [];

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

    console.log("Player hand:", playerHand);
    console.log("Computer hand:", computerHand);

    // Update the UI
    updateHands();

    // Remove opacity from hands to show cards are dealt
    document.getElementById("player-hand").style.opacity = "1";
    document.getElementById("computer-hand").style.opacity = "1";
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
    }
  });

  // Update computer hand (show card backs)
  const computerImages = computerHandDiv.querySelectorAll("img");
  computerHand.forEach((card, index) => {
    if (computerImages[index]) {
      computerImages[index].src =
        "https://deckofcardsapi.com/static/img/back.png";
      computerImages[index].alt = "Card back";
    }
  });
}

// Set up deal button event listener
document.getElementById("deal").addEventListener("click", dealCards);
