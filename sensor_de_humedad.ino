#include <LiquidCrystal.h>                                                //Incluye la libreria del lcd y en la siguiente linea se estbalecen los pines a usar.
LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);

#include <DHT.h>                                                         //Incluimos la libreria del sensor DHT
#define DHTPIN 9                                                         // Definimos el pin digital donde se conecta el sensor
#define DHTTYPE DHT11                                                    // Dependiendo del tipo de sensor
DHT dht(DHTPIN, DHTTYPE);                                                // Inicializamos el sensor DHT11

#define s_nivel A0                                                       //Definimos el pin a usar para el sensor de Nivel

void setup() {

  Serial.begin(9600);                                                     // Inicializamos comunicación serie
  lcd.begin(16,2);                                                        //Inicializamos y limpiamos el LCD
  lcd.clear();
  dht.begin();                                                            // Comenzamos el sensor DHT
  
}
 
void loop() {
   
  delay(5000);                                                             // Esperamos 5 segundos entre medidas
 
  
  float h = dht.readHumidity();                                           // Leemos la humedad relativa
  float t = dht.readTemperature();                                        // Leemos la temperatura en grados centígrados (por defecto)
  float f = dht.readTemperature(true);                                    // Leemos la temperatura en grados Fahreheit
 

  if (isnan(h) || isnan(t) || isnan(f)) {                                 // Comprobamos si ha habido algún error en la lectura
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
  
float nivel=analogRead(s_nivel);                                         //Leemos el sonsor de nivel


  float hif = dht.computeHeatIndex(f, h);                                // Calcular el índice de calor en Fahreheit
  float hic = dht.computeHeatIndex(t, h, false);                         // Calcular el índice de calor en grados centígrados
  
  lcd.setCursor(0,0);                                                    // imprimimos las Variables en el LCD
  lcd.print("HR:");
  lcd.setCursor(3,0);
  lcd.print(h,1);
  lcd.setCursor(7,0);
  lcd.print("%");
  lcd.setCursor(9,0);
  lcd.print("T:");
  lcd.setCursor(11,0);
  lcd.print(t,1);
  lcd.setCursor(14,0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("N:");
  float nivel_p=((nivel*100)/1023);
  lcd.setCursor(2,1);
  lcd.print(nivel_p);

  if (h>=95 || nivel_p>=2){                                            //En caso de que los sensores detecten valores que se salgan de los parametros
 
    Serial.println("H");                                               //Enviar caracter de control a la pc para enviar el correo
    lcd.clear();
    lcd.print("ALERTA");                                               //Mostrar el mensaje de alerta en el LCD

  }
   
  



    }
 
