/*
   ICTP - Mosquito WingBeat Sound Classification
   Built-in Microphone Test
   Based on Harvard University tinyMLx - Built-in Microphone Test
   MRovai @25Nov21
*/

#include <PDM.h>

// PDM buffer
short sampleBuffer[256];
volatile int samplesRead;

bool record = true;
bool commandRecv = false;

// PDM microphone in mono mode with 16 kHz sample rate
#define SAMPLE_RATE 8000
#define MODE 1 // mono

void setup() {
  Serial.begin(115200);
  while (!Serial);  
  Serial.println("ICTP - Mosquito WingBeat Sound Classification");
  Serial.println("Arduino Nano 33 BLE Sense - Built-in Microphone Test");
  Serial.println(" ");
    
  PDM.onReceive(onPDMdata);
  // Initialize PDM microphone 
  if (!PDM.begin(MODE, SAMPLE_RATE)) {
    Serial.print("Failed to start PDM with Sample Rate [KHz]: ");
    Serial.println(SAMPLE_RATE / 1000);
    while (1);
  }
  Serial.print("PDM initialized with Sample Rate [KHz]: ");
  Serial.println(SAMPLE_RATE / 1000);
  Serial.println("Open the Serial Plotter to view the corresponding waveform");
  Serial.println(" ");
}

void loop() {

  // display the audio if applicable
  if (samplesRead) {
    // print samples to serial plotter
    if (record) {
      for (int i = 0; i < samplesRead; i++) {
        Serial.println(sampleBuffer[i]);
      }
    }
    // clear read count
    samplesRead = 0;
  } 
}

void onPDMdata() {
  // query the number of bytes available
  int bytesAvailable = PDM.available();

  // read data into the sample buffer
  PDM.read(sampleBuffer, bytesAvailable);

  samplesRead = bytesAvailable / 2;
}
