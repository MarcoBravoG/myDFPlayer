#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySerial(10, 11); // TX, RX
DFRobotDFPlayerMini myDFPlayer;

const int buttonPin = 3; // Botón en pin 3
int lastButtonState = HIGH; // Estado anterior del botón
int songIndex = 1; // Para alternar entre las canciones

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  mySerial.begin(9600);
  
  if (!myDFPlayer.begin(mySerial)) {
    while (true); // Si no se detecta el módulo, detiene el programa
  }
  
  myDFPlayer.volume(20); // Ajusta el volumen (0-30)
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // Detectar cuando se presiona el botón
  if (buttonState == LOW && lastButtonState == HIGH) {
    myDFPlayer.play(songIndex); // Reproduce la canción correspondiente
    songIndex++; // Avanza a la siguiente canción
    if (songIndex > 3) songIndex = 1; // Reinicia el índice si supera 3
    delay(300); // Pequeño debounce
  }
  
  lastButtonState = buttonState;
}
