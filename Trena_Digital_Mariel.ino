/*MARIEL TRENA DIGITAL 2022*/

#include <HCSR04.h> /*Inclui a biblioteca do sensor HC SR04.*/
#define TRIGGER   9 /*Define os pinos do Arduino D8 e D9 como porta do ECHO e TRIGGER.*/
#define ECHO      8
UltraSonicDistanceSensor distanceSensor(TRIGGER, ECHO); /*Inicializa o sensor usando os pinos TRIGGER and ECHO.*/
#include <LiquidCrystal.h>  /*Inclui a biblioteca do sensor HC SR04*/
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); /* Define o objeto "lcd" para controlar o LCD nos pinos. 2 à 7 do Arduino.*/
// caracter bateria coracao
byte coracao[8] = {B00000,B00000,B01010,B01010,B00000,B10001,B01110,B00000};
//Configuracoes LCD 16x2  
int screenWidth = 16;  
int screenHeight = 2;  
//String para as 2 linhas 
//line1 = Scroll linha superior
String line1 = "Col Est Julia H de Souza. 7 x 7 metros. Mariel Martins"; 
// just some reference flags  
int stringStart, stringStop = 0;  
int scrollCursor = screenWidth;  
int tamanho =0;  
   

void setup () {
    Serial.begin(9600); /*Inicializa a porta serial do Arduino com 9600 de baud rate.*/
    lcd.begin(screenWidth,screenHeight);  
    // vai criar novo caracter bateria cheia
    lcd.createChar(1, coracao);

}

void loop () {
    int distancia = 0; /* Variável que armazenará as medidas do sensor.*/
    distancia = distanceSensor.measureDistanceCm(); /*Variável recebe o valor da função da biblioteca*/
    Serial.println(distancia); /*exibe na porta serial o valor de distancia medido*/
    lcd.setCursor(2, 1); /* Posiciona o cursor do display na coluna 2, linha 1 */
    lcd.print("Medida: "); /* Escreve a palavra "Medida: " na posição definida acima. */
    lcd.setCursor(9, 1); /* Posiciona o cursor do display na coluna 9, linha 1 */
    lcd.print(distancia); /* Escreve o valor da variável "distancia" na posição definida  acima.*/
    lcd.setCursor(12, 1); /* Posiciona o cursor do display na coluna 12, linha 1*/
    lcd.print("cm"); /* Escreve a unidade de medida "cm" na posição definida  acima.*/
    lcd.setCursor(0, 1); 
    lcd.write(1);
    lcd.setCursor(15, 1); 
    lcd.write(1);
    
  lcd.setCursor(scrollCursor, 0);  
  lcd.print(line1.substring(stringStart,stringStop));  
  lcd.setCursor(0, 1);  
  
  //Quanto menor o valor do delay, mais rapido o scroll  
  delay(250);  
  scroll_sup(); //Chama a rotina que executa o scroll  

  //Verifica o tamanho da string  
  tamanho = line1.length();  
  if (stringStart == tamanho)  
  {  
    stringStart = 0;  
    stringStop = 0;  
  }
    
}  
   
void scroll_sup()  
{  
  lcd.clear();  
  if(stringStart == 0 && scrollCursor > 0)
  {  
    scrollCursor--;  
    stringStop++;  
  } else if (stringStart == stringStop){  
    stringStart = stringStop = 0;  
    scrollCursor = screenWidth;  
  } else if (stringStop == line1.length() && scrollCursor == 0) {  
    stringStart++;  
  } else {  
    stringStart++;  
    stringStop++;  
  }  
}
