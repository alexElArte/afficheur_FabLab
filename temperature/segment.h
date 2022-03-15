/* Instruction pour l'utilisation de l'afficheur à leds du FabLab:
 *   - Insérez #include "segment.h" au tout début de votre code
 *   - Insérez init_display(); et enable_output(true); dans void setup()
 *   - Cela devrait ressembler à:
 *      
 *      #include "segment.h"
 *      
 *      ... // Some definitions
 *
 *      void setup() {
 *        init_display();
 *        enable_output(true);
 *
 *        ... // Some other code
 *      }
 *      ... // Rest of the code
 *    
 *    - Dans le fichier "segment.h" changez les variables pin_xxx pour que cela corresponde aux bons signaux que vous utilisez sur l'arduino
 *    - A chaque fois que vous voulez rafraichir ce qu'il y a d'affiché sur l'écran utilisez la fonction:  refresh_display()
 *    - Pour plus d'exemples allez sur https://github.com/alexElArte/afficheur_FabLab/blob/main/
*/

byte pin_clk = 13;
byte pin_lch = 12;
byte pin_en = 11;
byte pin_din = 10;

/*
   --A-- 
  |     |
  F     B   +-----+---+---+---+---+---+---+---+---+
  |     |   | Bit | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
   --G--    +-----+---+---+---+---+---+---+---+---+
  |     |   | Seg | - | A | B | C | D | E | F | G |
  E     C   +-----+---+---+---+---+---+---+---+---+
  |     |
   --D--
*/

const byte preset[16] {
  B01111110 /*'0'*/, B00110000 /*'1'*/,
  B01101101 /*'2'*/, B01111001 /*'3'*/,
  B00110011 /*'4'*/, B01011011 /*'5'*/,
  B01011111 /*'6'*/, B01110000 /*'7'*/,
  B01111111 /*'8'*/, B01111011 /*'9'*/,
  B01110111 /*'A'*/, B00011111 /*'b'*/,
  B01001110 /*'C'*/, B00111101 /*'d'*/,
  B01001111 /*'E'*/, B01000111 /*'F'*/
};

byte current[4] = {0, 0, 0, 0}; // All turned off, by default

/*
  Faster than function
*/
// Active les sorties de l'afficheur
#define enable_output(flag) digitalWrite(pin_en, !flag)
// Placer un caractère hexadecimal à un certain index
#define set_digit(index, value) current[index&3] = preset[value&0x0f]
// Placer un caractère spécial à un certain index (regarder le tableau pour les bits de l'afficheur)
#define set_custom(index, value) current[index&3] = value

/*void enable_output(bool flag) {
  digitalWrite(pin_en, !flag);
}
void set_digit(byte index, byte value) {
  current[3-index%4] = preset[value%16];
}
void set_custom(byte index, byte value) {
  current[3-index%4] = value;
}*/


// Affiche un entier positif
void set_int(unsigned int value, bool zeros=false) {
  set_digit(0, (value/1000));
  set_digit(1, (value/100)%10);
  set_digit(2, (value/10)%10);
  set_digit(3, value%10);
  if (zero) {
    if (value < 1000) {
      set_custom(0, 0);
      if (value < 100) {
        set_custom(1, 0);
        if (value < 10) set_custom(0, 0);
      }
    }
  }
}


// Utilisez cette fonction à chaque fois que vous voulez rafraichir l'afficheur
void refresh_display() {
  digitalWrite(pin_lch, LOW);
  for (byte i = 3; i < 4; i--) {
    shiftOut(pin_din, pin_clk, LSBFIRST, current[i]);  
  }
  digitalWrite(pin_lch, HIGH);
}

// Utilisez cette fonction une seule fois dans setup()
void init_display() {
  // Init the pins then the default states
  pinMode(pin_clk, OUTPUT);
  pinMode(pin_din, OUTPUT);
  pinMode(pin_lch, OUTPUT);
  pinMode(pin_en, OUTPUT);
  digitalWrite(pin_lch, HIGH);
  digitalWrite(pin_en, HIGH);
  refresh_display();
}