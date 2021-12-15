/*
   ICTP - Mosquito WingBeat Sound Classification
   Wio Built-in Microphone Test
   MRovai @26Nov21
*/
#define AUDIO_IN_PIN WIO_MIC
#define FREQUENCY_HZ  16000
#define INTERVAL_MS   (1000 / (FREQUENCY_HZ + 1))
static unsigned long last_interval_ms = 0;
int16_t analogValue;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("ICTP - Mosquito WingBeat Sound Classification");
  Serial.println("Wio Terminal - Built-in Microphone Test");
  Serial.println(" ");
  
  pinMode(AUDIO_IN_PIN, INPUT);

  Serial.println("Open the Serial Plotter to view the corresponding waveform");
  Serial.println(" ");
}

void loop() {
 if (millis() > last_interval_ms + INTERVAL_MS) {
    last_interval_ms = millis();
    
    // read raw mic data from device
    analogValue = analogRead(AUDIO_IN_PIN);
 
    Serial.println(analogValue); 
  }
}
