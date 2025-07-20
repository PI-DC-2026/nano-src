//DC26_LOADBOARD_2.6MHZ_SQUARE_WAVE_4CYCLES_BUTTON_PB5
//W.McCaffrey, E.Tann, T.Huddleston
//DC2026 Testing 7/18/2025
//Attempt to use PB5 as button input and cycle 4 square waves, only certain quadrants and 0xff current

volatile byte state = 0;

const int buttonPin = 12;                // PB4 (D12) as button input
const unsigned long debounceDelay = 200; // 200 ms debounce delay
unsigned long lastButtonPressTime = 0;
bool buttonWasPressed = false;

const unsigned int cyclesPerBurst = 4;  // 4 HIGH-LOW cycles per burst (~500 ns per burst)
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
  
        PORTB = 0x0D
      for (unsigned int i = 0; i < cyclesPerBurst; i++) {
    
        PORTC = 0x07;
        PORTD = 0x07;

        PORTC = 0x00;
        PORTD = 0x00;
      }
    }
  
  }

  if (!buttonState) {
    buttonWasPressed = false;
  }
}