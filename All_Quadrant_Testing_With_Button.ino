// DC26_LOADBOARD_SQUARE_WAVE_4CYCLES_BUTTON_PB4
// W.McCaffrey, E.Tann, T.Huddleston, B. Dannan
// DC2026 Testing 6/15/2025
//Updated to button 12 to match hardwired design
//Byte Pattern Sequence setup to meet requirements
//UNTESTED AS OF 6/15/2025

const int buttonPin = 12;                // PB4 (D12) for button
const unsigned long debounceDelay = 200; // 200 ms debounce
unsigned long lastButtonPressTime = 0;
bool buttonWasPressed = false;

const unsigned int cyclesPerBurst = 4;
int patternIndex = 0;  // Current pattern step

// Define quadrant masks
enum Quadrant {
  Q1 = 1 << 0,
  Q2 = 1 << 1,
  Q3 = 1 << 2,
  Q4 = 1 << 3
};

// Predefined sequence of quadrant activations
const byte patternSequence[] = {
  Q1,
  Q2,
  Q3,
  Q1 | Q2,
  Q1 | Q3,
  Q2 | Q3,
  Q4,
  Q4 | Q1,
  Q4 | Q2,
  Q4 | Q2 // repeated
};

const int totalPatterns = sizeof(patternSequence) / sizeof(patternSequence[0]);

void setup() {
  // Configure PB4 (D12) as button input with pull-up
  DDRB &= ~(1 << 4);         // Input
  PORTB |= (1 << 4);         // Pull-up

  // Configure PB0–PB3 (Q1–Q4) as outputs
  DDRB |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);

  // Configure PC0–PC7 (Q1, Q2) as outputs
  DDRC = 0xFF;

  // Configure PD0–PD7 (Q3, Q4) as outputs
  DDRD = 0xFF;

  // Initialize all outputs to LOW
  PORTB &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3));
  PORTC = 0x00;
  PORTD = 0x00;
}

void loop() {
  bool buttonState = !(PINB & (1 << 4)); // Button press is LOW
  unsigned long currentTime = millis();

  if (buttonState && !buttonWasPressed && (currentTime - lastButtonPressTime > debounceDelay)) {
    buttonWasPressed = true;
    lastButtonPressTime = currentTime;

    // Run current pattern burst
    runPattern(patternSequence[patternIndex]);

    // Move to next pattern in sequence
    patternIndex = (patternIndex + 1) % totalPatterns;
  }

  if (!buttonState) {
    buttonWasPressed = false;
  }
}

void runPattern(byte quadrantMask) {
  for (int i = 0; i < cyclesPerBurst; i++) {
    activateQuadrants(quadrantMask, HIGH);
    activateQuadrants(quadrantMask, LOW);
  }
}

void activateQuadrants(byte mask, bool state) {
  // Always start clean
  PORTB &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3));
  PORTC = 0x00;
  PORTD = 0x00;

  if (state) {
    if (mask & Q1) {
      PORTB |= (1 << 0);   // PB0
      PORTC = 0xFF;        // PC0–PC7
    }
    if (mask & Q2) {
      PORTB |= (1 << 1);   // PB1
      PORTC = 0xFF;        // PC0–PC7
    }
    if (mask & Q3) {
      PORTB |= (1 << 2);   // PB2
      PORTD = 0xFF;        // PD0–PD7
    }
    if (mask & Q4) {
      PORTB |= (1 << 3);   // PB3
      PORTD |= 0b00111111; // PD0–PD5
    }
  }
}
