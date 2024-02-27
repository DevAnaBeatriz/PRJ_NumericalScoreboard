#include "LedControl.h"
#define MAX_DEVICES  1  // Numero de modulos utilizados  
#define DATA_PIN        12  // Ligacoes ao Arduino MD_MAX72xx
#define CS_PIN            10  // Ligacoes ao Arduino MD_MAX72xx
#define CLK_PIN          11  // Ligacoes ao Arduino MD_MAX72xx



LedControl Placar = LedControl(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);



int v_but1, v_but2;      // Armazenam o valor dos botoes
int placar;                   // Variável do placar atual
int placar_ant;            // Variável do placar anterior
int delaytime = 100;   // Tempo
int brilho = 15;          // Brilho dos displays



byte CARACTER [10][8]  = {
         {B00000000,
B00000000,
B01111110,
B10000001,
B10000001,
B01111110,
B00000000,
B00000000}, // 0
         {B00000000,
B00000000,
B10000001,
B11111111,
B10000000,
B00000000,
B00000000,
B00000000}, // 1
         {B00000000,
B11000010,
B10100001,
B10010001,
B10001110,
B00000000,
B00000000,
B00000000}, // 2
         {B00000000,
B00000000,
B01000010,
B10000001,
B10011001,
B01100110,
B00000000,
B00000000}, // 3
         {B00000000,
B00000000,
B00011100,
B00010010,
B00010001,
B11111111,
B00000000,
B00000000}, // 4
         {B00000000,
B00000000,
B01001111,
B10001001,
B10001001,
B01110001,
B00000000,
B00000000}, // 5
         {B00000000,
B00000000,
B01111110,
B10001001,
B10001001,
B01110000,
B00000000,
B00000000}, // 6
         {B00000000,
B00000000,
B00000011,
B00000001,
B00001001,
B11111111,
B00001000,
B00000000}, // 7
         {B00000000,
B00000000,
B01110110,
B10001001,
B10001001,
B01110110,
B00000000,
B00000000}, // 8
         {B00000000,
B00000000,
B01001110,
B10010001,
B10010001,
B01111110,
B00000000,
B00000000}, // 9
    
};



void setup() {
      Serial.begin(9600);
      pinMode(8, INPUT_PULLUP);       // Inicializa pino botão aumenta
      pinMode(9, INPUT_PULLUP);       // Inicializa pino botaão diminui
      Placar.shutdown(0, false);          // Inicializa os displays
      Placar.setIntensity(0, brilho);     // Ajusta o brilho de cada display
      Placar.clearDisplay(0);               // Apaga os display
      MostrarCaracter(0, 0);              // Mostra 0 (zero) no display
}



void loop() {



 // Verifica se o botao de aumentar foi acionado



 v_but1 = digitalRead(8);  // Le botão aumentar
  if  (v_but1 == 0)   {
       placar = placar + 1;
       if  (placar >= 10) { placar = 9; }



      if  (placar_ant != placar)     {
            MostrarCaracter(placar, 0); //Chama a rotina que atualiza o display
            v_but1 = digitalRead(8);
            placar_ant = placar;
       }
      
       while (digitalRead(8) == 0) {
            delay(delaytime);
       }
}



// Verifica se o botao de diminuir foi acionado



 v_but2 = digitalRead(9);  // Le botão diminuir
  if  (v_but2 == 0)   {
       placar = placar - 1;
       if  (placar <= 0) { placar = 0;  }



      if  (placar_ant != placar)     {
            MostrarCaracter(placar, 0); //Chama a rotina que atualiza o display
            v_but2 = digitalRead(9);
            placar_ant = placar;
       }



      while (digitalRead(9) == 0) {
            delay(delaytime);
       }
  }
}



// Rotina Mostra número no display



void MostrarCaracter(int numero, int tela) {



   for  (int i = 0; i < 8; i++)  {
          Placar.setRow(tela, i, CARACTER[numero][i]);
    }
  
}
