int ledPin = 3;
int dotDelay = 300;

const int greenLEDPin = 9;
const int redLEDPin = 11;
const int blueLEDPin = 10;

const int lightPin = 12;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;


//Morse code recorded for letters
char* letters[] = {
".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R 
"...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};// S-Z


void setup() {
  Serial.begin(9600);
//pinMode(ledPin,OUTPUT); 

  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  Serial.println("Type in any sentence you want to transfer into Morse code: ");
}

void loop() {
  //Serial.println(switchState);
 

  if (Serial.available()){

    String sentence = Serial.readString();
    sentence = toUpperCase(sentence); //change all the characters into capitalized letters
    int len = sizeof(sentence);
    char characters[len];

    sentence.toCharArray(characters, len);
    char ch;

    // for (int i = 0; i < len; i++){
    //   ch = characters[i]; // read a single letter if (ch >= 'a' && ch <= 'z')
    //   Serial.println(ch);
    // }

    for (int i = 0; i < len; i++){
      ch = characters[i]; // read a single letter if (ch >= 'a' && ch <= 'z')
      Serial.println(ch);
      if (ch >= 'A' && ch <= 'Z') {
        flashSequence(letters[ch - 'A']); 
      }else if (ch == ' ') {
        delay(dotDelay * 4);
      }
      digitalWrite(lightPin, HIGH);
      delay(dotDelay*1.25);
      digitalWrite(lightPin, LOW);
    }
  }
}

void flashSequence(char* sequence){
  int i = 0;
  while(sequence[i] != NULL){
    flashMorse(sequence[i]);
    i++;
  }
  delay(dotDelay *4);
}

void flashMorse(char morseCode){

  if(morseCode == '.'){ //short note
    digitalWrite(redLEDPin, HIGH); //turn the light on
    digitalWrite(greenLEDPin, LOW); //turn the light off
    digitalWrite(blueLEDPin, LOW); //turn the light off
    delay(dotDelay);

    digitalWrite(blueLEDPin, LOW); //turn the light off
  }else{ //else if it's '-'
    digitalWrite(redLEDPin, LOW); //turn the light off
    digitalWrite(greenLEDPin, HIGH); //turn the light on
    digitalWrite(blueLEDPin, LOW); //turn the light off
    delay(dotDelay * 3);
    digitalWrite(greenLEDPin, LOW); //turn the light on
  }
  digitalWrite(redLEDPin, LOW); //turn the light off
  digitalWrite(greenLEDPin, LOW); //turn the light off
  digitalWrite(blueLEDPin, LOW); //turn the light off

  //digitalWrite(ledPin, LOW); //turn the light off
  delay(dotDelay);

}
