char User1[] = "A";
char User2[] = "B";
#include <LiquidCrystal.h>

const int rs = 5, en = 6, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int avaliableButton_1 = 0;
int avaliable_1 = 0;
int browseState_1 = 0;
int backState_1 = 0;
int emojiChoice_1 = 4; //begining of the list of the emojis.

int avaliableButton_2 = 0;
int avaliable_2 = 0;
int browseState_2 = 0;
int backState_2 = 0;
int emojiChoice_2 = 4; //begining of the list of the emojis.

byte userAvatar[8] = {
    0b00000,
    0b01110,
    0b11111,
    0b01110,
    0b00100,
    0b11111,
    0b11111,
    0b11111
  };

byte heart[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};

  byte brokenHeart[8] = {
    0b00000,
    0b01010,
    0b11011,
    0b11101,
    0b11011,
    0b01110,
    0b00100,
    0b00000
  };

byte sadFace[8] = {
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b01110,
    0b10001,
    0b00000,
    0b00000
  };

byte happyFace[8] = {
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b11111,
    0b10001,
    0b01110,
    0b00000
  };

byte sickFace[8] = {
    0b01010,
    0b10001,
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b01110,
    0b10001
  };

byte neutralFace[8] = {
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b11111,
    0b00000,
    0b00000
  };

byte smile[8] = {
   0b00000,
   0b00000,
   0b01010,
   0b00000,
   0b10001,
   0b01110,
   0b00000,
   0b00000
};

byte angryFace[8] = {
   0b10001,
   0b01010,
   0b00000,
   0b01010,
   0b00000,
   0b01110,
   0b10001,
   0b00000
};

byte anxious[8]= {
   0b00000,
   0b00000,
   0010010,
   0100000,
   0100000,
   0000000,
   0111000,
   1000001
};

void setup() {
  Serial.begin(9600);

  pinMode(3, INPUT);
  pinMode(2, INPUT);

  pinMode(12, INPUT);
  pinMode(13,INPUT);

  lcd.begin(16, 2);

  //assign emojis
  byte* emojiNames [] = {userAvatar, heart, brokenHeart, neutralFace,
                        happyFace, sickFace,sadFace,angryFace,
                        anxious};
  for(int i = 1; i < 9;i++){
     lcd.createChar(i, emojiNames[i-1]);
  }

  // lcd.createChar(1, userAvatar);
  // lcd.createChar(2, heart);
  // lcd.createChar(3, brokenHeart);
  // lcd.createChar(4, sadFace);

  lcd.setCursor(0,0);
  lcd.write(1);
  lcd.print(User1);
  lcd.write(3);

  int position = 16 - sizeof(User2);
  lcd.setCursor(position-1, 0);
  lcd.write(3);
  lcd.print(User2);
  lcd.write(1);

  lcd.setCursor(0,1);
  lcd.write(emojiChoice_1);
  lcd.setCursor(15,1);
  lcd.write(emojiChoice_2);

}

void loop(){
 // CheckBothAvaliable();
  CheckSameEmoji();


  lcd.setCursor(sizeof(User1),0);

  avaliableButton_1 = digitalRead(3);
  browseState_1 = digitalRead(2);
  backState_1 =  digitalRead(4);

  avaliableButton_2 = digitalRead(13);
  browseState_2 = digitalRead(12);
  backState_2 =  digitalRead(11);

  //Serial.println(avaliableButton_1);
  if(avaliableButton_1 == HIGH){
    lcd.setCursor(sizeof(User1),0);
    if(avaliable_1 == 0){
       avaliable_1 = 1;
       lcd.write(2);
     }else{
       avaliable_1 = 0;
       lcd.write(3);
     }
    // CheckBothAvaliable();
    avaliableButton_1 = 0;
  }
  if(browseState_1 == HIGH){
    lcd.setCursor(0,1);
    lcd.print("");
    emojiChoice_1++;
    if(emojiChoice_1 > 8) emojiChoice_1 = 4;
    lcd.write(emojiChoice_1);
    browseState_1 = 0;
    delay(100);
    lcd.setCursor(0,1);
    lcd.print("");//reset to none
  }

    if(backState_1 == HIGH){
    lcd.setCursor(0,1);
    lcd.print("");
    emojiChoice_1 = emojiChoice_1-1 ;
    if(emojiChoice_1 < 4) emojiChoice_1 = 8;
    lcd.write(emojiChoice_1);
    browseState_1 = 0;
    delay(100);
    lcd.setCursor(0,1);
    lcd.print("");//reset to none
  }


  if(avaliableButton_2 == HIGH){
    int position = 16 - sizeof(User2);
    lcd.setCursor(position-1,0);
    if(avaliable_2 == 0){
       avaliable_2 = 1;
       lcd.write(2);
     }else{
       avaliable_2 = 0;
       lcd.write(3);
     }
   
    avaliableButton_2 = 0;
  }
  if(browseState_2 == HIGH){
    lcd.setCursor(15,1);
    lcd.print("");
    emojiChoice_2++;
    if(emojiChoice_2 > 8) emojiChoice_2 = 4;
    lcd.write(emojiChoice_2);
    browseState_2 = 0;
    delay(100);
    lcd.setCursor(15,1);
    lcd.print("");//reset to none
  }

  if(backState_2 == HIGH){
    lcd.setCursor(15,1);
    lcd.print("");
    emojiChoice_2 = emojiChoice_2-1 ;
    if(emojiChoice_2 < 4) emojiChoice_2 = 8;
    lcd.write(emojiChoice_2);
    browseState_2 = 0;
    delay(100);
    lcd.setCursor(15,1);
    lcd.print("");//reset to none
  }
  
  delay(100);
}

// void CheckBothAvaliable(){
//   if(avaliable_2 == 1 && avaliable_1 == 1) {
//     lcd.setCursor(2,1);
//     lcd.print("Let's talk!!");
//     delay(100);
   
//     lcd.print("            ");
//   }
  
// }
void CheckSameEmoji(){
  if(emojiChoice_1 == emojiChoice_2){ 
    if(emojiChoice_1 == 4){//plain face
      lcd.setCursor(7,1);
      lcd.print("-_-");
    }
    if(emojiChoice_1 == 5){//happy face
      lcd.setCursor(3,1);
      lcd.print("Slay PURRR");
    }
    if(emojiChoice_1 == 6){//sick face
      lcd.setCursor(5,1);
      lcd.print("L beta");
    }
    if(emojiChoice_1 == 7){//sad face
      lcd.setCursor(2,1);
      lcd.print("yikes (>x<)");
    }
     if(emojiChoice_1 == 8){//angry face
      lcd.setCursor(2,1);
      lcd.print("-( .\ _ /. )-");
    }
  }else{
    lcd.setCursor(2,1);
    lcd.print("             ");
  }

}
