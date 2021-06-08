//libreria del sensor
#include <DHT.h>
#include <SPI.h>
#include <SD.h>

// Definimos el pin digital
#define DHTPIN 2
// tipo de sensor
#define DHTTYPE DHT11
// Inicia el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

bool valorpin10 = digitalRead(10);

struct sensor {
  uint32_t horas, minutos, segundos;  //4
  uint16_t  grados, humedad;   //2
  String nom1, nom2;
} se;

int segundosencendido = 0, horas = 0, minutos = 0, segundos = 0;
int Save = 0;
int cont = 0;
const int ModSlct = 4;

void setup() {
  // Inicia comunicación serie
  Serial.begin(9600);
  SD.begin(ModSlct); // Iniciamos el módulo SD
  pinMode(ModSlct, OUTPUT); // Definimos el módulo SD como salida
  dht.begin();  // Comenzamos el sensor DHT
}

void loop() {

  { segundosencendido = millis() / 1000;
    se.horas = segundosencendido / 3600; 
    se.minutos = segundosencendido / 60 - horas * 60; 
    se.segundos = segundosencendido - minutos * 60;
  }
  { delay (200);

    //Leemos la humedad relativa            //Leemos la temperatura en grados
    se.humedad = dht.readHumidity();         se.grados = dht.readTemperature();

    se.nom1 = "TEMPERATURA: ";
    se.nom2 = "HUMEDAD: ";

    if (valorpin10 != digitalRead(10)) //Evitamos que el pulsador haga más de una pulsación al apretar
    {
      if (valorpin10 == 1)
      {
        Save++; //Aumentamos la variable save para hacer el guardado posteriormente
        cont++;   //cada vez que apretemos el pulsador para guardar sume uno,
      }

      valorpin10 = digitalRead(10); // Con esto volvemos a poner el pulsador como al principio ( preparado para ser pulsado)

    }
    if (Save == 1) //Si save es 1 hace lo que hay dentro del if, al apretar el pulsador suma 1, entonces siempre entrara.
    {


      File dataFile = SD.open("DHT11.txt", FILE_WRITE); //Crea el archivo DHT11 o si ya existe escribe dentro de el (Podeis cambiarlo)

      if (dataFile)
      {
        //Lo que viene a continuación es lo que aparecerá dentro de la tarjeta SD.
        dataFile.print(se.nom2); dataFile.print(se.humedad); dataFile.println("%");
        Serial.print(se.nom2); Serial.print(se.humedad); Serial.println ("%");

        dataFile.print(se.nom1); dataFile.print(se.grados);  dataFile.println("°C");
        Serial.print(se.nom1); Serial.print(se.grados); Serial.println ("°C");
        dataFile.print (se.horas); dataFile.print(":");  dataFile.print (se.minutos); dataFile.print(":"); dataFile.print (se.segundos); dataFile.println("\n");
        Serial.print (se.horas); Serial.print(":");  Serial.print (se.minutos); Serial.print(":"); Serial.println (se.segundos); Serial.print("\n");
        // Lo que viene ahora lo he puesto para que nos aparezca en el serial para hacer la demostración.
        Serial.println("Datos escritos"); Serial.println("Exitoso");



        dataFile.close();
        Save = 0;

      }
    }
  }
}
