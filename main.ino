#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const int trigPin = 9; 
const int echoPin = 10;
const unsigned char buttonPin = 4;

const unsigned char NOTE_C4 = 60;
const unsigned char NOTE_D4 = 62;
const unsigned char NOTE_E4 = 64;
const unsigned char NOTE_F4 = 65;
const unsigned char NOTE_G4 = 67;
const unsigned char NOTE_A4 = 69;
const unsigned char NOTE_B4 = 71;

const unsigned char OCTAVE = 12; //an Octave

const unsigned char KEY_START = 4;//the keyboard starts at 4cm
const unsigned char KEY_END = 32;//the keyboard ends at 32cm


void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buttonPin, INPUT);
  Serial.begin(115200); // Starts the serial communication
}

void loop() {
  play();
}

/* function name: read_keyboard_value()
 * precondition: none
 * postcondition: return where on the keyboard is touched(Here I used Ultrasonic sensor so it's distance)
 * ****change this function to your sensor accordingly****
 */
long read_keyboard_value()
{
  long duration;
  long distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  distance = constrain(distance,0,KEY_START + KEY_END); //The length of the keyboard is 36cm, but I made 0-4 and 32-36 a silent zone.
  
  return distance;
  }

/* function name: get_pitch()
 * precondition: read_keyboard_value() gets a valid distance, or other value. And check_button() returns a valid multiplier
 * postcondition: return the corresponding midi value
 */
char get_pitch(long keyboard_value){
  long midivalue;
  char multiplier = 0;
  if(keyboard_value >= KEY_START && keyboard_value <= KEY_END){
    midivalue = (keyboard_value - KEY_START)/((KEY_END - KEY_START)/7) + 1;
    multiplier = check_button();
    switch(midivalue){
          case 1:
            return NOTE_C4 + OCTAVE * multiplier;
            break;
          case 2:
            return NOTE_D4 + OCTAVE * multiplier;
            break;
          case 3:
            return NOTE_E4 + OCTAVE * multiplier;
            break;
          case 4:
            return NOTE_F4 + OCTAVE * multiplier;
            break;
          case 5:
            return NOTE_G4 + OCTAVE * multiplier;
            break;
          case 6:
            return NOTE_A4 + OCTAVE * multiplier;
            break;
          case 7:
            return NOTE_B4 + OCTAVE * multiplier;
            break;
          }
    }else{
      return 0;
    }
  }

/* function name:check_button()
 * precondition: none
 * postcondition: return a multiplier to decide how many octaves do the pitch rises or falls.
 * Here, when button is pressed, the pitch rise for one octave.
 */
char check_button(){
  char multiplier = 0;
  unsigned char state = 0;
   state = digitalRead(buttonPin);
   if(state == 0){
      multiplier = 0;
      delayMicroseconds(1);
    }
   if(state == 1){
      multiplier = 1;
      delayMicroseconds(1);
    }
    return multiplier;
    //change the value of the multiplier to raise or reduce octaves to the note
  }

/* function name: play()
 * debounce the sensor and send MIDI throught the MIDI-USB cable
 */
void play(){
    unsigned char pitch;
    unsigned static char last_pitch;
    pitch = get_pitch(read_keyboard_value());
    if(pitch != 0){
      if(pitch != last_pitch){
        last_pitch = pitch;
        delayMicroseconds(5);
        pitch = get_pitch(read_keyboard_value());
        if(pitch == last_pitch){
            MIDI.sendNoteOn(pitch, 100, 1);
            delay(150);                   
            MIDI.sendNoteOff(pitch, 0, 1);     
            delay(100);
          }
        }
      }
  last_pitch = pitch;
}

  
