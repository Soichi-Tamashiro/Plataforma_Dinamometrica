
//----------------------------------------------------------------
// Valores de Calibración de galas
//----------------------------------------------------------------
float loadA = 10; //  kg
int analogvalA = 200; // analog reading taken with load A on the load cell

float loadB = 30; // kg 
int analogvalB = 600; // analog reading taken with load B on the load cell

//----------------------------------------------------------------
// Inicializacion de variables
//----------------------------------------------------------------
float analogValueAverage = 0;
// Especificamos cuan seguido se hacen las lecturas
long time = 0; // 
int timeBetweenReadings = 200; // We want a reading every 200 ms;
L = 300;  // Tamaño de plataforma largo
A = 30;   // Tamaño de plataforma ancho
W = 80;   // Peso de una Persona
X = 150;  // Distancia del plano medio sagital del cuerpo
void setup() {
  
  Serial.begin(9600);
}

void loop() {
  //----------------------------------------------------------------
  // Lectura de galgas
  //----------------------------------------------------------------
  int analogValue1_1 = ReadVoltage(36);
  int analogValue1_2 = ReadVoltage(39);
  
  Impresion de valores
  if(millis() > time + timeBetweenReadings){
    float W1 = analogToLoad(analogValue1_1);
    float W2 = analogToLoad(analogValue1_2);
    XG=(L*W1-X*(W1+W2))W // Para medir el ZG y YG es necesario cambiar de posicion a la person y anotar los valores
    Serial.println("El centro de gravedad es ",XG)
    time = millis();
  }
}
//----------------------------------------------------------------
//  Funcion para incrementar precision
//----------------------------------------------------------------
double ReadVoltage(byte pin){
  double reading = analogRead(pin); // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095
  if(reading < 1 || reading > 4095) return 0;
  // return -0.000000000009824 * pow(reading,3) + 0.000000016557283 * pow(reading,2) + 0.000854596860691 * reading + 0.065440348345433;
  return -0.000000000000016 * pow(reading,4) + 0.000000000118171 * pow(reading,3)- 0.000000301211691 * pow(reading,2)+ 0.001109019271794 * reading + 0.034143524634089;
}
//----------------------------------------------------------------
//  Funcion que convierte el valor analogico a peso
//----------------------------------------------------------------
float analogToLoad(float analogval){

  // using a custom map-function, because the standard arduino map function only uses int
  float load = mapfloat(analogval, analogvalA, analogvalB, loadA, loadB);
  return load;
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
