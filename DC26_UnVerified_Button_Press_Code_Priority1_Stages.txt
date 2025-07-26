
//DC26_LOADBOARD_Button Press Code
//W.McCaffrey, E.Tann, T.Huddleston
//DC2026 Testing 7/26/2025
//This code uses PB5 as button input and cycle X square waves
//This code has NOT been verified to work and tested. Modifications of this code are used for our test cases
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

	//PortB Mapping	
	//0x07 = BITS 0 1 2 
	//0X0F = BITS 0 1 2 3

    switch (state) {
      case 0:
        PORTB = 0x07;
        for (unsigned int i = 0; i < cyclesPerBurst; i++) {
          PORTC = 0x7F;
          PORTD = 0x7F;
	__asm__ __volatile__ ("nop");//Waits a clock cycle before doing anything
          PORTC = 0x00;
          PORTD = 0x00;
        }
        Serial.println("Test Case TC 6L01_01: PB=0x07 | PC=0x7F | PD=0x7F");
        break;

      case 1:
        PORTB = 0x07;
        for (unsigned int i = 0; i < cyclesPerBurst; i++) {
          PORTC = 0x7F;
          PORTD = 0x7F;
          PORTC = 0x00;
          PORTD = 0x00;
        }
        Serial.println("Test Case TC 6L01_02: PB=0x07 | PC=0x7F | PD=0x7F");
        break;

      case 2:
        PORTB = 0x07;
        for (unsigned int i = 0; i < cyclesPerBurst; i++) {
          PORTC = 0x7F;
          PORTD = 0x7F;
	__asm__ __volatile__ ("nop");//Waits a clock cycle before doing anything
          PORTC = 0x00;
          PORTD = 0x00;
        }
        Serial.println("Test Case TC 6L01_03: PB=0x07 | PC=0x7F | PD=0x7F");
        break;

      case 3:
        PORTB = 0x0F;
        for (unsigned int i = 0; i < cyclesPerBurst; i++) {
          PORTC = 0x7F;
          PORTD = 0x7F;
	__asm__ __volatile__ ("nop");//Waits a clock cycle before doing anything
          PORTC = 0x00;
          PORTD = 0x00;
        }
        Serial.println("Test Case TC 6L01_04: PB=0x0F | PC=0x7F | PD=0x7F");
        break;

      case 4:
        PORTB = 0x07;
        for (unsigned int i = 0; i < cyclesPerBurst; i++) {
          PORTC = 0x7F;
          PORTD = 0x7F;
          PORTC = 0x00;
          PORTD = 0x00;
        }
        Serial.println("Test Case TC 6L01_05: PB=0x0F | PC=0x7F | PD=0x7F");
        break;

      case 5:
        PORTB = 0x0F;
        for (unsigned int i = 0; i < cyclesPerBurst; i++) {
          PORTC = 0x7F;
          PORTD = 0x7F;
          PORTC = 0x00;
          PORTD = 0x00;
        }
        Serial.println("Test Case TC 6L01_06: PB=0x0F | PC=0x7F | PD=0x7F");
        break;
    }

    state++;
    if (state >= 6) state = 0;
  }

  if (!buttonState) {
    buttonWasPressed = false;
  }
}
