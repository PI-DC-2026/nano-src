
//DC26_LOADBOARD_Button Press Code
//W.McCaffrey, E.Tann, T.Huddleston
//DC2026 Testing 7/26/2025
//This code uses PB5 as button input and cycle X square waves
//This code has been verified to work and tested. Modifications of this code are used for our test cases
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
  
        PORTB = 0x07 //This sets PB active. This can be adjusted to change the clocks drive
	//0x07 = BITS 0 1 2 
	//0X0F = BITS 0 1 2 3
      for (unsigned int i = 0; i < cyclesPerBurst; i++) {
    
        PORTC = 0x7F;
        PORTD = 0x7F;

        PORTC = 0x00;
        PORTD = 0x00;

//This code does the port read and writes this way to go as fast as possible. Each write takes 62.5ns, and having 4 commands in a cycle lets us reach 2.3MHz for a wave. Any additional code will slow this down.
//this is effectively assembly code as the PORTX = X command is 2 cycles
      }
    }
  
  }

  if (!buttonState) {
    buttonWasPressed = false;
  }
}