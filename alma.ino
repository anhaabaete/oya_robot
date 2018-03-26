/**
 * Programa que controla as funcionalidades do Robot C.o.L.a.2
 * Desenvolvido pelo projeto Oya Que Legal
 * Eng: Tiago Neves
 * Prof: Elaine S. Santana
 * Autor: Tiago Neves 
 */

#include <LedControl.h>
#include <Ultrasonic.h>
#include <Servo.h>

//variaveis

  Servo pescoso;
  Servo pesEsq;
  Servo pesDir;

  //sonar
  const int sonar_vcc =  13;
  const int sonar_trg = 12;
  const int sonar_ech = 11;

  //boca
  const int boca_esq = 5;
  const int boca_dir = 6;

  //matrizes
  const int olhos_din = 10;
  const int olhos_cs  = 9;
  const int olhos_clk = 8;

  //servo pescoco (eng ferro)
  const int pescoco_vcc = 4;
  const int pescoco_dat = A0;

  //servo pe esquedo
  const int peEsq_vcc = 5;
  const int peEsq_dat = A1;

  //servo pe direito
  const int peDir_vcc = 3;
  const int peDir_dat = A2;

  //configuracoes
  bool sonar_ligado = false;
  


//animacao olhos

//configura led matrizes 8x8 olhos
LedControl olhos = LedControl(olhos_din, olhos_clk, olhos_cs,2);

/******************
 * olho piscando
 ******************/
const byte ani_pisca_dir[][8] = {
{
  B01111000,
  B11111100,
  B11111110,
  B11111111,
  B11001111,
  B11001111,
  B11111111,
  B01111110
},{
  B01111000,
  B11111100,
  B11111100,
  B11111100,
  B11001100,
  B11001100,
  B11111100,
  B01111100
},{
  B01110000,
  B11110000,
  B11110000,
  B11110000,
  B11000000,
  B11000000,
  B11110000,
  B01110000
},{
  B01000000,
  B11000000,
  B11000000,
  B11000000,
  B11000000,
  B11000000,
  B11000000,
  B01000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},{
  B01110000,
  B11110000,
  B11110000,
  B11110000,
  B11000000,
  B11000000,
  B11110000,
  B01110000
},{
  B01111000,
  B11111100,
  B11111110,
  B11111111,
  B11001111,
  B11001111,
  B11111111,
  B01111110
}};
const int ani_pisca_dir_len = sizeof(ani_pisca_dir)/8;

const byte ani_pisca_esq[][8] = {
{
  B01111110,
  B11111111,
  B11001111,
  B11001111,
  B11111111,
  B11111110,
  B11111100,
  B01111000
},{
  B01111100,
  B11111100,
  B11001100,
  B11001100,
  B11111100,
  B11111100,
  B11111100,
  B01111000
},{
  B01110000,
  B11110000,
  B11000000,
  B11000000,
  B11110000,
  B11110000,
  B11110000,
  B01110000
},{
  B01000000,
  B11000000,
  B11000000,
  B11000000,
  B11000000,
  B11000000,
  B11000000,
  B01000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},{
  B01110000,
  B11110000,
  B11000000,
  B11000000,
  B11110000,
  B11110000,
  B11110000,
  B01110000
},{
  B01111110,
  B11111111,
  B11001111,
  B11001111,
  B11111111,
  B11111110,
  B11111100,
  B01111000
}};
const int ani_pisca_esq_len = sizeof(ani_pisca_esq)/8;


void pisca() {
  for (int i=0;i<ani_pisca_esq_len;i++) {
    for (int j = 0; j < 8; j++) {
      olhos.setRow(0, j, ani_pisca_esq[i][j]);
      olhos.setRow(1, j, ani_pisca_dir[i][j]);
    }
    delay(50);
  }
  
}

void olhosAbertos() {
    for (int j = 0; j < 8; j++) {
      olhos.setRow(0, j, ani_pisca_esq[0][j]);
      olhos.setRow(1, j, ani_pisca_dir[0][j]);
    }
}

/**********************
 * FIM do olho piscando
 **********************/

/******************
 * olho procura
 ******************/

 const byte ani_proc_esq[][8] = {
{
  B01111110,
  B11111111,
  B11001111,
  B11001111,
  B11111111,
  B11111110,
  B11111100,
  B01111000
},{
  B01111110,
  B11111111,
  B11111111,
  B11111111,
  B11001111,
  B11001110,
  B11111100,
  B01111000
},
{
  B01111110,
  B11111111,
  B11001111,
  B11001111,
  B11111111,
  B11111110,
  B11111100,
  B01111000
},
{
  B01001110,
  B11001111,
  B11111111,
  B11111111,
  B11111111,
  B11111110,
  B11111100,
  B01111000
},{
  B01111110,
  B11111111,
  B11001111,
  B11001111,
  B11111111,
  B11111110,
  B11111100,
  B01111000
}};
const int ani_proc_esq_LEN = sizeof(ani_proc_esq)/8;

const byte ani_proc_dir[][8] = {
{
  B01111000,
  B11111100,
  B11111110,
  B11111111,
  B11001111,
  B11001111,
  B11111111,
  B01111110
},{
  B01111000,
  B11111100,
  B11111110,
  B11111111,
  B11111111,
  B11111111,
  B11001111,
  B01001110
},{
  B01111000,
  B11111100,
  B11111110,
  B11111111,
  B11001111,
  B11001111,
  B11111111,
  B01111110
},
{
  B01111000,
  B11111100,
  B11001110,
  B11001111,
  B11111111,
  B11111111,
  B11111111,
  B01111110
},{
  B01111000,
  B11111100,
  B11111110,
  B11111111,
  B11001111,
  B11001111,
  B11111111,
  B01111110
}};
const int ani_proc_dir_LEN = sizeof(ani_proc_dir)/8;

void olho_procura() {
  for (int i=0;i<ani_proc_dir_LEN;i++) {
    for (int j = 0; j < 8; j++) {
      olhos.setRow(0, j, ani_proc_esq[i][j]);
      olhos.setRow(1, j, ani_proc_dir[i][j]);
    }
    delay(200);
  }
  
}

/**
 * funcao que rederiza qualquer frame das animacoes
 */
void rederizaOlho(const byte* imagemEsq, const byte* imagemDir) {
  for (int i = 0; i < 8; i++) {
    olhos.setRow(0, i, imagemEsq[i]);
    olhos.setRow(1, i, imagemDir[i]);
  }
 
}

void olhaProLado() {
  rederizaOlho(ani_proc_esq[1],ani_proc_dir[1]);
}


/*
 * SENSOR ultrasonico
 */
Ultrasonic ultrasonic(sonar_trg, sonar_ech);

bool verificaCaminho() {
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.print("Distâcia a frente: ");  Serial.print(cmMsec); Serial.print("\n");
  if(cmMsec<20 && cmMsec>0.10) {
    return false;
  }
  return true;
}



/*
 * Boca Funcoes
 */

 void abreBoca(int qnt) {
  analogWrite(boca_esq, qnt);
  analogWrite(boca_dir, qnt);
 }

 void fechaBoca() {
  analogWrite(boca_esq, LOW);
  analogWrite(boca_dir, LOW);
 }

/*
 * FIM Funcoes BOCA
 */

 

/*
* funcoes PESCOSO
*/

void pescosoverifica() {

    pesEsq.detach();
    pesDir.detach();
     delay(3000);
     
    digitalWrite(sonar_vcc,LOW);
    fechaBoca();
    pescoso.attach(pescoco_dat);

    rederizaOlho(ani_proc_esq[1],ani_proc_dir[1]);
    for (int pos = 90; pos <= 150; pos++) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      pescoso.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }

    abreBoca(30);
    rederizaOlho(ani_proc_esq[3],ani_proc_dir[3]);
    for (int pos = 150; pos >= 30; pos--) { // goes from 180 degrees to 0 degrees
      pescoso.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
      
    }

    rederizaOlho(ani_proc_esq[1],ani_proc_dir[1]);
    for (int pos = 30; pos <= 90; pos++) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      pescoso.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }

    olhosAbertos();
    pescoso.detach();
    digitalWrite(sonar_vcc,HIGH);
    abreBoca(1);
    delay(2000);
    desviar();
    
}



/**
 * funcoes dos pes
 */


 
void desviar() {
  olhaProLado();
  
  delay(2000);

  pesEsq.attach(peEsq_dat);
  pesDir.attach(peDir_dat);

  pesEsq.write(170);
  pesDir.write(170);

  delay(7000);

  pesEsq.write(1);
  pesDir.write(170);

  delay(700);
  
}

void andar1cm() {
  pesEsq.attach(peEsq_dat);
  pesDir.attach(peDir_dat);
  
  pesEsq.write(1);
  pesDir.write(1);


  

}




/**
 * FIM funcoes dos pes
 */


void setup() {
  olhos.shutdown(0,false);  // Wake up displays
  olhos.shutdown(1,false);
  olhos.setIntensity(0,0.5);  // Set intensity levels
  olhos.setIntensity(1,0.5);
  olhos.clearDisplay(0);  // Clear Displays
  olhos.clearDisplay(1);
  Serial.begin(9600);
  pinMode(sonar_vcc,OUTPUT);
  digitalWrite(sonar_vcc,HIGH);
  pescoso.attach(pescoco_dat);
  pesEsq.attach(peEsq_dat);
  pesDir.attach(peDir_dat);
  pinMode(boca_esq,OUTPUT);
  pinMode(boca_dir,OUTPUT);
  abreBoca(1);
  randomSeed(analogRead(0)); //humanizacao
}



void loop() {
  pescoso.write(90);

  pescoso.detach();
  olhosAbertos();
  
  if (!verificaCaminho()) {
    pescosoverifica();
    desviar();
  } else {
    andar1cm();
  }
  
  int rnd = random(300);
  Serial.print("Humanização: "); Serial.print(rnd); Serial.print("\n");
  if (rnd==99) {
      pisca();
      olho_procura();
  } else if (rnd==33) {
      olho_procura();
  } else if(rnd==177) {
      pisca();
  } 
  
}
