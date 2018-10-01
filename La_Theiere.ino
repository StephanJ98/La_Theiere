#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);
byte ledvert = 2;
byte ledrouge = 3;
byte bouton1 = 6; //Gauche
byte bouton2 = 5; //Centre
byte bouton3 = 4; //Droite
boolean gauche;
boolean centre;
boolean droite;
int cont = 0;
int taille = 5; //Changer aussi ligne 22
typedef struct{
  int code;
  String nom;
  unsigned long tic;
  unsigned long til;
  unsigned long ti;
  String tipe;
  int grames;
  int temp;
}thes;
thes the[5]; //Changer aussi ligne 10

void setup() {
  pinMode(ledvert, OUTPUT);
  pinMode(ledrouge, OUTPUT);
  pinMode(bouton1, INPUT);
  pinMode(bouton2, INPUT);
  pinMode(bouton3, INPUT);
  gauche = false;
  centre = false;
  droite = false;
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Allumage en");
  lcd.setCursor(5,1);
  lcd.print("cours");
  delay(2000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("La Theiere");
  lcd.setCursor(2,1);
  lcd.print("Version  1.1");
  delay(2000);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print(" Choisir le");
  lcd.setCursor(4,1);
  lcd.print(" Bouton");
  delay(1200);
  lcd.clear();
  
  the[0].code = 0; 
  the[0].nom = "Vert Chine";
  the[0].tic = 12000;  // 2 min
  the[0].til = 300000; // 5 min
  the[0].ti = 240000;  // 4 min
  the[0].tipe = "Vert";
  the[0].grames = 5;
  the[0].temp = 75;

  the[1].code = 1;
  the[1].nom = "Vert Japon";
  the[1].tic = 60000; // 1 min
  the[1].til = 180000;// 3 min
  the[1].ti = 120000; // 2 min
  the[1].tipe = "Vert";
  the[1].grames = 6;
  the[1].temp = 75;

  the[2].code = 2;
  the[2].nom = "Noir Chine";
  the[2].tic = 240000;  // 4 min
  the[2].til = 360000;  // 6 min
  the[2].ti = 300000;   // 5 min
  the[2].tipe = "Noir";
  the[2].grames = 6;
  the[2].temp = 90;

  the[3].code = 3;
  the[3].nom = "Darjeeling Aut";
  the[3].tic = 240000;  // 4 min
  the[3].til = 360000;  // 6 min
  the[3].ti = 300000;   // 5 min
  the[3].tipe = "Noir";
  the[3].grames = 10;
  the[3].temp = 90;

  the[4].code = 4;
  the[4].nom = "Pu Erh";
  the[4].tic = 240000;  // 4 min
  the[4].til = 360000;  // 6 min
  the[4].ti = 300000;   // 5 min
  the[4].tipe = "Pu Erh";
  the[4].grames = 6;
  the[4].temp = 95;
}

void loop() {
  reset();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Gauche   Droite");
  lcd.setCursor(0,1);
  lcd.print(" Info   Compteur");
  delay(2000);
  do{
    if(digitalRead(bouton1) == HIGH){
      gauche = true;
    }
    if(digitalRead(bouton3) == HIGH){
      droite = true;
    }
    delay(1000);
  }while(gauche == false && droite == false);
  if(gauche == true){ //Info
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("Info");
    lcd.setCursor(3,1);
    lcd.print("Selectionne");
    delay(2000);
    for(int i = 0; i <= (taille - 1); i++){
      info(i);
    }
  }
  else if(droite == true ){ //Compteur
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Compteur");
    lcd.setCursor(3,1);
    lcd.print("Selectionne");
    delay(2000);
    reset();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gauche   Droite");
    lcd.setCursor(0,1);
    lcd.print("   -1      +1");
    delay(1000);
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Centre");
    lcd.setCursor(7,1);
    lcd.print("OK");
    reset();
    do{
      if(digitalRead(bouton2) == HIGH){
        centre = true;
      }
      delay(1000);
    }while(centre == false);
    reset();
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("PRET");
    delay(2000); 
    do{
      reset();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Code:");
      lcd.setCursor(6,0);
      lcd.print(cont + 1);
      lcd.setCursor(10,0);
      lcd.print((the[cont].ti / 60000));
      lcd.setCursor(12,0);
      lcd.print("min");
      lcd.setCursor(0,1);
      lcd.print(the[cont].nom);
      //delay(2000);
      do{
        reset();
        if(digitalRead(bouton1) == HIGH){
          gauche = true;
        }
        if(digitalRead(bouton2) == HIGH){
          centre = true;
        }
        if(digitalRead(bouton3) == HIGH){
          droite = true;
        }
        if(gauche == true){ //-1
          cont--;
        }
        if(droite == true){ //+1
          cont++;
        }
        if(cont > cant()){
          cont--;
        }
        if(cont < 0){
          cont++;
        }
        //delay(2000);
      }while((gauche == false) && (centre == false) && (droite == false));
      centre = false;
      delay(2000);
      if(digitalRead(bouton2) == HIGH){
          centre = true;
        }
    }while(centre == false); //Repeter jusqu'à presser le bouton confirmer.
    reset();
    compteur(cont);
    cont = 0;
    delay(1500);
  }
}
void info(int code){// Montre les infor sur le thé choisi sur les deux lignes du lcd 16x02
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(code);
  lcd.setCursor(2,0);
  lcd.print(the[code].nom);
  lcd.setCursor(0,1);
  lcd.print((the[code].ti / 60000));
  lcd.setCursor(2,1);
  lcd.print("min");
  lcd.setCursor(7,1);
  lcd.print(the[code].temp);
  lcd.setCursor(10,1);
  lcd.print("C");
  lcd.setCursor(12,1);
  lcd.print(the[code].grames);
  lcd.setCursor(14,1);
  lcd.print("gr");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(code);
  lcd.setCursor(2,0);
  lcd.print(the[code].nom);
  lcd.setCursor(0,1);
  lcd.print("Tipe:");
  lcd.setCursor(7,1);
  lcd.print(the[code].tipe);
  delay(1500);
}
void compteur(int code){//Compte le temps d'infusion de du thé choisi , selon le mode selectione , et allume la ledvert quand le temps es ecoule
  lcd.clear();
  digitalWrite(ledrouge,HIGH);
  lcd.setCursor(0,0);
  lcd.print("Choisir le");
  lcd.setCursor(0,1);
  lcd.print("Bouton");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Court      Long");
  lcd.setCursor(0,1);
  lcd.print("     Normal");
  delay(4000);
  if(digitalRead(bouton1) == HIGH){ //Court
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("..ATTENDEZ..");
    lcd.setCursor(5,1);
    lcd.print(the[code].tic / 60000);
    lcd.setCursor(7,1);
    lcd.print("min");
    delay(the[code].tic);
  }
  if(digitalRead(bouton2) == HIGH){ // Normal
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("..ATTENDEZ..");
    lcd.setCursor(5,1);
    lcd.print(the[code].ti / 60000);
    lcd.setCursor(7,1);
    lcd.print("min");
    delay(the[code].ti);
  }
  if(digitalRead(bouton3) == HIGH){ // Long
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("..ATTENDEZ..");
    lcd.clear();
    lcd.setCursor(5,1);
    lcd.print(the[code].til / 60000);
    lcd.setCursor(7,1);
    lcd.print("min");
    delay(the[code].til);
  }
  digitalWrite(ledrouge,LOW);
  digitalWrite(ledvert,HIGH);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("...PRET...");
  delay(1000);
  do{
    delay(1000);
  }while(digitalRead(bouton1) == LOW && digitalRead(bouton2) == LOW && digitalRead(bouton3) == LOW);
  digitalWrite(ledvert,LOW);
}
int cant(){//montre la cantite de thé registres
  return taille - 1;
}
void reset(){
  gauche = false;
  centre = false;
  droite = false;
}
