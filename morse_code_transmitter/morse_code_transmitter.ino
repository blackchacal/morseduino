/**
 * @Project: Morse code Emitter/Receiver
 * @Description: This project consists on a Morse code emitter and receiver modules.
 *               The goal is for the modules comunicate with each other using morse code
 *               IR light signals. The user sends some text through the serial port to
 *               the emitter module which encodes it to morse code and sends to the receiver
 *               via IR signals. The receiver then translates the signals back to text and 
 *               shows it through a LCD display.
 * 
 * @Module: Emitter
 * 
 * @Author: Ricardo Tonet <ribeiro.tonet@gmail.com> (github: https://github.com/blackchacal)
 */

/**
 * International Morse code is composed of five elements:
 *
 * 1. short mark, dot or "dit" (.): "dot duration" is one time unit long
 * 2. longer mark, dash or "dah" (_): three time units long
 * 3. inter-element gap between the dots and dashes within a character: one dot duration or one unit long
 * 4. short gap (between letters): three time units long
 * 5. medium gap (between words): seven time units long
 */

/**************************************************************
 * Constants and Variables                                    *
 **************************************************************/ 
 
// Constants
const unsigned int TIME_UNIT = 50; // one time unit: 50 ms
const unsigned int SOUND_FREQ = 880; // 440 Hz (Sol)

// Pins
int LedPin = 2;
int BuzzPin = 3;

// Vars
unsigned long time = 0;

/**************************************************************
 * Functions                                                  *
 **************************************************************/ 

String translateMessage(String msg) {
  String tmsg; // Translated message
  String charCode;
  unsigned int msgSize = msg.length();

  for (int i = 0; i < msgSize; i++) {
    charCode = convertCharacterToMorseCode(msg[i]);
    tmsg += charCode + "   ";
  }
  tmsg.trim();
  return tmsg;
}

void sendMessage(String msg) {
  Serial.println('"'+msg+'"');
  convertMorseCodeToSignal(msg);
}

String convertCharacterToMorseCode(char c) {
  String code;
  
  switch(c) {
    case 'a':
    case 'A':
      code = ".-";
      break;
    case 'b':
    case 'B':
      code = "-...";
      break;
    case 'c':
    case 'C':
      code = "-.-.";
      break;
    case 'd':
    case 'D':
      code = "-..";
      break;
    case 'e':
    case 'E':
      code = ".";
      break;
    case 'f':
    case 'F':
      code = "..-.";
      break;
    case 'g':
    case 'G':
      code = "--.";
      break;
    case 'h':
    case 'H':
      code = "....";
      break;
    case 'i':
    case 'I':
      code = "..";
      break;
    case 'j':
    case 'J':
      code = ".---";
      break;
    case 'k':
    case 'K':
      code = "-.-";
      break;
    case 'l':
    case 'L':
      code = ".-..";
      break;
    case 'm':
    case 'M':
      code = "--";
      break;
    case 'n':
    case 'N':
      code = "-.";
      break;
    case 'o':
    case 'O':
      code = "---";
      break;
    case 'p':
    case 'P':
      code = ".--.";
      break;
    case 'q':
    case 'Q':
      code = "--.-";
      break;
    case 'r':
    case 'R':
      code = ".-.";
      break;
    case 's':
    case 'S':
      code = "...";
      break;
    case 't':
    case 'T':
      code = "-";
      break;
    case 'u':
    case 'U':
      code = "..-";
      break;
    case 'v':
    case 'V':
      code = "...-";
      break;
    case 'w':
    case 'W':
      code = ".--";
      break;
    case 'x':
    case 'X':
      code = "-..-";
      break;
    case 'y':
    case 'Y':
      code = "-.--";
      break;
    case 'z':
    case 'Z':
      code = "--..";
      break;
    case '1':
      code = ".----";
      break;
    case '2':
      code = "..---";
      break;
    case '3':
      code = "...--";
      break;
    case '4':
      code = "....-";
      break;
    case '5':
      code = ".....";
      break;
    case '6':
      code = "-....";
      break;
    case '7':
      code = "--...";
      break;
    case '8':
      code = "---..";
      break;
    case '9':
      code = "----.";
      break;
    case '0':
      code = "-----";
      break;
    case ' ':
      code = "    ";
    default:
      code = "";
      break;
  }
  return code;
}

void convertMorseCodeToSignal(String code) {
  unsigned int codeSize = code.length();
  
  for (int i = 0; i < codeSize; i++) {
    sendDotDashSpace(code.charAt(i));
  }
}

/**
 * Converts Morse Code (dash-dot-space) into sound or light.
 */
void sendDotDashSpace(char c) {
  switch (c) {
    case '.':
      tone(BuzzPin, SOUND_FREQ, TIME_UNIT);
      sendLightSignal(TIME_UNIT);
      delay(TIME_UNIT);
      break;
    case '-':
      tone(BuzzPin, SOUND_FREQ, TIME_UNIT*3);
      sendLightSignal(TIME_UNIT*3);
      delay(TIME_UNIT);
      break;
    case ' ':
      delay(TIME_UNIT);
      break;
  }
}

/**
 * Sends morse code via LED (IR or Normal).
 */
void sendLightSignal(unsigned int timeUnit) {
  digitalWrite(LedPin, HIGH);
  delay(timeUnit);
  digitalWrite(LedPin, LOW);
}

/**************************************************************
 * Main Code                                                  *
 **************************************************************/ 

void setup() {
  Serial.begin(9600);

  pinMode(LedPin, OUTPUT);
  pinMode(BuzzPin, OUTPUT);
}

void loop() {
  String message;
  String morseMessage;
  
  while (Serial.available()) {
    // Get text message from serial port
    message = Serial.readString();
    Serial.print(message+": ");
    
    if (message.length() > 0) {
      // Translate text message to morse code message
      morseMessage = translateMessage(message);
    
      // Send morse code message to receiver
      sendMessage(morseMessage); 
    }
  }
}
