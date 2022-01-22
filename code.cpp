#include <DHT.h>
#define DHTTYPE DHT22


//bomba
int relayPin1 = 13;
int relayPin2 = 12; 
//

int rainPin = A3;
int luz =0;

int DHTPIN = 3;
DHT dht(DHTPIN, DHTTYPE);

void setup(){

 pinMode(rainPin, INPUT);

//bomba 
 pinMode(relayPin1, OUTPUT);
 pinMode(relayPin2, OUTPUT);
//

 Serial.println("Iniciando...\n");
 dht.begin();
 Serial.begin(9600);
}

void loop() {

  luz = analogRead(0);

  //Imprimimos por monitor serie el valor 
  Serial.print("\nLuz: ");
  Serial.println(luz);


  float h = dht.readHumidity(); //Leemos la Humedad
  float t = dht.readTemperature(); //Leemos la temperatura en grados Celsius

  //--------Enviamos las lecturas por el puerto serial-------------
  Serial.print("Humedad en el aire: ");
  Serial.print(h);
  Serial.print(" %");
  Serial.print("\nTemperatura: ");
  Serial.print(t);
  Serial.print(" ºC ");
  
  // lectura de la entrada analoga pin en A0:
  int sensoraguaseca = analogRead(rainPin);
  Serial.print("\n");
  Serial.println(sensoraguaseca);

  
  if(sensoraguaseca < 100 or t > 30 or luz > 200 or h > 100){
    Serial.println(" – CONDICIONES  APTAS PARA EL REGADO");
    Serial.println("pump stop!");
    
    //bomba
    digitalWrite(relayPin1, LOW);
    digitalWrite(relayPin2, LOW);
    //  
  }
  else {
    Serial.println(" – CONDICIONES NO APTAS PARA EL REGADO");
    Serial.println("pump start!");
    //bomba
    digitalWrite(relayPin1, HIGH);
    digitalWrite(relayPin2, HIGH); 
    //
  }
  delay(2000);
}