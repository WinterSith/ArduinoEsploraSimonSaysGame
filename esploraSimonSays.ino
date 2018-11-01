/*
 Esplora Simon Says   
 by Chad Painter
 */
#include <Esplora.h>

const int c_green = 1;
const int c_red = 2;
const int c_yellow = 3;
const int c_clear = 4;

const int c_green_pin = 1;
const int c_red_pin = 0;
const int c_yellow_pin = 7;
const int c_clear_pin = 16;

const int c_green_note = 262;
const int c_red_note = 294;
const int c_yellow_note = 330;
const int c_clear_note = 392;
const int c_error_note = 100;

const int c_max_rounds = 100;
int       v_current_round = 0;
int       v_playback_array[c_max_rounds];

boolean   v_player_turn = true;
boolean   v_playback_error = false;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins as output.
  pinMode(c_green_pin, OUTPUT);
  pinMode(c_red_pin, OUTPUT);
  pinMode(c_yellow_pin, OUTPUT);
  pinMode(c_clear_pin, OUTPUT);

  delay (4111);
  Serial.begin(9600);

  randomSeed(69);
}

// the loop function runs over and over again forever
void loop() {

  int i = 0;
  while (i <= c_max_rounds) {
     computer_play();
     human_play();
     if (!v_playback_error) {
         v_current_round++; }
     delay(1000);
     i++;
  }

}

///////////////////////////////////////////////////////////
// Functions Start Here                                  //
///////////////////////////////////////////////////////////
void human_play() {

  int i = 0;
  v_playback_error = false;
  v_player_turn = true;

  Serial.print("i before loop: ");
  Serial.println(i);
  Serial.print("v_current_round --------------> ");
  Serial.println(v_current_round);

  while (v_player_turn && !v_playback_error && i <= v_current_round) {
    
    check_green(v_playback_array, i);
    check_red(v_playback_array, i);
    check_yellow(v_playback_array, i);
    check_clear(v_playback_array, i);
    
    
  }

  Serial.print("i after loop: ");
  Serial.println(i);
  Serial.print("v_current_round --------------> ");
  Serial.println(v_current_round);

  if (v_playback_error) {
    digitalWrite(c_clear_pin, HIGH);
    digitalWrite(c_red_pin, HIGH);
    digitalWrite(c_green_pin, HIGH);
    digitalWrite(c_yellow_pin, HIGH);
    Esplora.tone(c_error_note);
    delay(5500);
    Esplora.noTone();
    digitalWrite(c_clear_pin, LOW);
    digitalWrite(c_red_pin, LOW);
    digitalWrite(c_green_pin, LOW);
    digitalWrite(c_yellow_pin, LOW);
    v_current_round = 0;
  }
}



void computer_play() {
   //Computer play
   
   int random_number = random(1,5);

   v_playback_array[v_current_round] = random_number;
   
   play_order(v_playback_array, v_current_round);
   
   Serial.print("random num ");
   Serial.println(random_number);
   Serial.print("Computer Play: v_playback_array = ");
   Serial.println(v_playback_array[v_current_round]);
   Serial.print("v_current_round= ");
   Serial.println(v_current_round);


}

void play_order(int p_play_order[], int p_how_many) {
  //Computer plays routine
    int i = 0;
    while (i <= p_how_many) { 
          if (p_play_order[i] == c_green) {
            digitalWrite(c_green_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
            Esplora.tone(c_green_note);
            delay(500);
            Esplora.noTone();
            delay(1000);
            digitalWrite(c_green_pin, LOW);
          }

          if (p_play_order[i] == c_red) {
            digitalWrite(c_red_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
            Esplora.tone(c_red_note);
            delay(500);
            Esplora.noTone();
            delay(1000);
            digitalWrite(c_red_pin, LOW);
          }

          if (p_play_order[i] == c_yellow) {
            digitalWrite(c_yellow_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
            Esplora.tone(c_yellow_note);
            delay(500);
            Esplora.noTone();
            delay(1000);
            digitalWrite(c_yellow_pin, LOW);
          }

          if (p_play_order[i] == c_clear) {
            digitalWrite(c_clear_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
            Esplora.tone(c_clear_note);
            delay(500);
            Esplora.noTone();
            delay(1000);
            digitalWrite(c_clear_pin, LOW);
          }    
          i++;
          delay(275);
   }
}  

void check_green(int p_play_order[], int &p_check_me) {
  //Green LED

  if (Esplora.readButton(SWITCH_UP) == LOW) {
     digitalWrite(c_green_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
     Esplora.tone(c_green_note);
     delay(500);
     Esplora.noTone();
     Serial.println("check green");
     Serial.println(p_check_me);
     digitalWrite(c_green_pin, LOW);
     if (p_play_order[p_check_me] != c_green) {
        v_player_turn = false;
        v_playback_error = true;
     }
     p_check_me++;
     delay(333);
  }
  else {
     digitalWrite(c_green_pin, LOW);    // turn the LED off by making the voltage LOW
  }
}

void check_red(int p_play_order[], int &p_check_me) {
  //RED LED

  if (Esplora.readButton(SWITCH_DOWN) == LOW) {
     digitalWrite(c_red_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
     Esplora.tone(c_red_note);
     delay(500);
     Esplora.noTone();
     Serial.print("check red:  p_check me value:  ");
     Serial.println(p_check_me);
     Serial.print("p_play_order[p_check_me]: ");
     Serial.println(p_play_order[p_check_me]);
     digitalWrite(c_red_pin, LOW);
     if (p_play_order[p_check_me] != c_red) {
        v_player_turn = false;
        v_playback_error = true;
     }
     p_check_me++;
     delay(333);
  }
  else {
     digitalWrite(c_red_pin, LOW);    // turn the LED off by making the voltage LOW
  }
}

void check_yellow(int p_play_order[], int &p_check_me) {
  //Yellow LED
  if (Esplora.readButton(SWITCH_RIGHT) == LOW) {
     digitalWrite(c_yellow_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
     Esplora.tone(c_yellow_note);
     Serial.println("check yellow");
     Serial.println(p_check_me);
     delay(500);
     Esplora.noTone();
     digitalWrite(c_yellow_pin, LOW);
     if (p_play_order[p_check_me] != c_yellow) {
        v_player_turn = false;
        v_playback_error = true;
     }
     p_check_me++;
     delay(333);
  }
  else {
     digitalWrite(c_yellow_pin, LOW);    // turn the LED off by making the voltage LOW
  }
}

void check_clear(int p_play_order[], int &p_check_me) {
  //clear LED
  if (Esplora.readButton(SWITCH_LEFT) == LOW) {
     digitalWrite(c_clear_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
     Esplora.tone(c_clear_note);
     Serial.println("check clear");
     Serial.println(p_check_me);
     delay(500);     
     Esplora.noTone();
     digitalWrite(c_clear_pin, LOW);
     if (p_play_order[p_check_me] != c_clear) {
        v_player_turn = false;
        v_playback_error = true;
     }
     p_check_me++;
     delay(333);
  }
  else {
     digitalWrite(c_clear_pin, LOW);    // turn the LED off by making the voltage LOW
  }
}
