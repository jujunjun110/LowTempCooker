int relayPin = 13;
int thermoPin = 0;
int loopDurationSec = 3;
float temp_low = 67.0; // 温度の下限
float temp_high = 69.0; // 温度の上限

int pastSecs = 0;
int pastMinutes = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("Cooking Start!");
  pinMode(relayPin, OUTPUT);
}

void loop(){
  float temperature = getTemperature();
  Serial.println(temperature);
  
  turnPotIfNeeded(temperature);
  printTimeIfNeeded();

  pastSecs += loopDurationSec;
  delay(loopDurationSec * 1000); 
}

float getTemperature () {
  float analogInput; // 0〜203
  float temp_c = 0; // 摂氏( ℃ )
  analogInput = analogRead(thermoPin);
  temp_c = (500 * analogInput) / 1024; // 入力値を摂氏に換算
  return temp_c;  
}

void turnPotIfNeeded (float temp) {
  if (temp < 0.0 || temp > 100.0) {
    Serial.println("invalid temp. data omitted");
    digitalWrite(relayPin, LOW);
    return;
  }  
  if (temp < temp_low) {
    digitalWrite(relayPin, HIGH);
  }
  if (temp > temp_high) {
    digitalWrite(relayPin, LOW);
  }   
}

void printTimeIfNeeded() {
  int newPastMinutes = pastSecs / 60;
  if (newPastMinutes > pastMinutes) {
    pastMinutes = newPastMinutes;
    Serial.println("\n" + String(pastMinutes) + " minutes have passed.\n");
  } 
}
