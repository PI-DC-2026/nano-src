//DC26_LOADBOARD_2.6MHZ_SQUARE_WAVE_4CYCLES_BUTTON_PB5
//W.McCaffrey, E.Tann, T.Huddleston
//DC2026 Testing 6/6/2025
//Attempt to use PB5 as button input and cycle 4 square waves

volatile byte state = 0;

const int buttonPin = 12;                // PB4 (D12) as button input
const unsigned long debounceDelay = 200; // 200 ms debounce delay
unsigned long lastButtonPressTime = 0;
bool buttonWasPressed = false;

const unsigned int cyclesPerBurst = 4;  // 4 HIGH-LOW cycles per burst (~500 ns per burst)
uint8_t currentCombo = 0;  // Tracks PB0-PB3 combo (0 to 15)
void setup() {
  // Set PB4 (D12) as input
  DDRB &= ~(1 << 4);  // PB4 as input
  PORTB |= (1 << 4);  // Enable pull-up resistor on PB4

  DDRC = 0xFF;  // Set all PC0–PC7 as outputs
  DDRD = 0xFF;  // Set all PD0–PD7 as outputs
  DDRB |= 0x0F;
   Serial.begin(9600);
  Serial.println("Ready");
}

void loop() {
  bool buttonState = (PINB & (1 << 4)) == 0;  // Button pressed = LOW on PB4
  unsigned long currentTime = millis();

  if (buttonState && !buttonWasPressed && (currentTime - lastButtonPressTime > debounceDelay)) {
    buttonWasPressed = true;
    lastButtonPressTime = currentTime;
  
    //PORTB &= ~0x0F;       // Clear bits 0-3
  
    // Run 4 bursts of 4 cycles each at 2.6 MHz square wave
    for (int pass = 0; pass < 16; pass++) {

      PORTB &= ~0x0f;
      PORTB = pass;
      for (unsigned int i = 0; i < cyclesPerBurst; i++) {
      
    
        PORTC = 0x07;
        PORTD = 0x07;

        PORTC = 0x00;
        PORTD = 0x00;
      }
    }
     currentCombo = (currentCombo + 1) & 0x0F;
  }

  if (!buttonState) {
    buttonWasPressed = false;
  }
}