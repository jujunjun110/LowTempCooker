int thermoPin = 0;
int relayPin = 13;
int loopDurationSec = 3;
float cookingModeList[][3] = {{62.0, 64.0}, {40.0, 41.0}, {66.0, 68.0}};
int cookingMode = 0; // 0: Beef, 1: Salmon, 2: Egg

float temp_low;
float temp_high;
int pastSecs = 0;
int pastMinutes = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("Cooking Start!");
  pinMode(relayPin, OUTPUT);
  temp_low = cookingModeList[cookingMode][0];
  temp_high = cookingModeList[cookingMode][1];
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
