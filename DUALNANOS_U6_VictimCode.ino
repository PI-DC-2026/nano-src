//DC26_LOADBOARD_Button Press Code
//W.McCaffrey, E.Tann, T.Huddleston
//DC2026 Testing 12/29/2025
//This code uses PB5 as b      utton input and cycle X square waves
//DUAL NANO CASE, setup for single shot button working
//CONFIRMED WORKING, VICTIM CASE


volatile byte state = 0;

const int buttonPin = 12;                // PB4 (D12) as button input
const unsigned long debounceDelay = 200; // 200 ms debounce delay
unsigned long lastButtonPressTime = 0;
bool buttonWasPressed = false;

const unsigned int cyclesPerBurst = 4;  // 4 HIGH-LOW cycles per burst (~500 ns per burst)
void setup() {
    // Set PB5 (D12) as input
  DDRB &= ~(1 << 5);  // PB5 as input
  //PORTB |= (1 << 4);  // Enable pull-up resistor on PB4
  DDRC = 0xFF;  // Set all PC0–PC7 as outputs
  DDRD = 0xFF;  // Set all PD0–PD7 as outputs
  DDRB |= 0x0F;
   Serial.begin(9600);
  Serial.println("Ready");
}

void loop() {
  bool buttonState = (PINB & (1 << 5)) == 0;  // Button pressed = LOW on PB4
  unsigned long currentTime = millis();

  if (buttonState && !buttonWasPressed && (currentTime - lastButtonPressTime > debounceDelay)) {
    buttonWasPressed = true;
    lastButtonPressTime = currentTime;
  
        PORTB = 0x08; //This sets PB active. This can be adjusted to change the clocks drive
        //0X08, BITS 3 ONLY, VICTIM
	//0x07 = BITS 0 1 2 which is all aggressors not victim
	//0X0F = BITS 0 1 2 3 which is all aggressors and victim 

      for (unsigned int i = 0; i < cyclesPerBurst; i++) {
    
        //PORTC = 0x3F;
        PORTD = 0x2F;
         __asm__ __volatile__("nop\n\t");
         //this is for 1.67MHz, remove it if you want 2.1MHz
//for 530KHz
        __asm__ __volatile__(
 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
  "nop\n\t""nop\n\t""nop\n\t""nop\n\t"
);

        PORTC = 0x00;
        PORTD = 0x00;
        __asm__ __volatile__("nop\n\t");
         //__asm__ __volatile__("nop\n\t");
//For 530kHz
      __asm__ __volatile__(
 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
  "nop\n\t""nop\n\t""nop\n\t""nop\n\t"
);

//48MHz nano has a 20.83 clock cycle, portX takes 2 clock cycles
//This code does the port read and writes this way to go as fast as possible. Each write takes 62.5ns, and having 4 commands in a cycle lets us reach 2.3MHz for a wave. Any additional code will slow this down.
//this is effectively assembly code as the PORTX = X command is 2 cycles
      }
    }

  if (!buttonState) {
    buttonWasPressed = false;
  }
}