// algoritmo para usar sensor magnético com interrupção

// OLED 0.96" Display:
#include <Adafruit_GFX.h>  // Include core graphics library for the display.
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display.
Adafruit_SSD1306 display(128, 64);  // Create display.
#include <Fonts/FreeMonoBold18pt7b.h>  // Add a custom font.

// ============================================================================
//--------- frequência da CPU ---------
#define F_CPU 16000000

// ============================================================================
// --- Bibliotecas ---
#include <avr/io.h>                            //biblioteca de entradas e saídas padrão
#include <util/delay.h>                        //biblioteca delay
#include <avr/interrupt.h>	                   //biblioteca para interrupções 

// ============================================================================
//----------- Bibliotecas -------------
#include <Wire.h>

// ============================================================================
// --- Variáveis Globais ---
unsigned counter       = 0x00;                 //contador de pulsos
int pulsosPorRevolucao = 3,                    //total de imãs
    rpm                   ,
    freqAngular           ;

const byte numReadings = 200;

// Variables for smoothing tachometer:
unsigned long period; 
unsigned long readings[numReadings];           // The input.
unsigned long readIndex;                       // The index of the current reading.
unsigned long total;                           // The running total.
unsigned long average;                         // The RPM value after applying the smoothing.

// ============================================================================
// --- Interrupções ---
ISR(INT0_vect)
{
  //Serial.println( float(TCNT1) );
  period = TCNT1;
  TCNT1  = 0x00;                               //reinicia valor do timer1
  counter ++;

} //end ISR INT0


void setup() {  
  //Configuração das Interrupções
  cli();                                       //Desabilita interrupções

  DDRD &= ~(1<<PD2);                           //configura PD2 como entrada  *registrador fica setado como zero

  PORTD |= (1<<PD2);                           //habilita pull-up interno de PD
  
  TCCR1B = 0x00;                               //desliga timer1                   (guardara o valor de uma volta)
  EICRA |= (1<<ISC01) | (1<<ISC00);            //interrupção externa por borda de subida inicialmente
  EIMSK |= (1<<INT0);                          //habilita interrupção externa
  TCCR1B |= (1<<CS12) | (0<<CS11) | (1<<CS10); //habilita clock/1024(From prescaler)
  
  sei();                                       //Habilita as interrupções
  
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Setup ready");

  // OLED 0.96" Display:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C.
  display.clearDisplay();               // Clear the buffer.
  display.setTextColor(WHITE);          // Set color of the text to white.
  display.setRotation(0);               // Set orientation. Goes from 0, 1, 2 or 3.
  display.setTextWrap(false);           // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
                                        // To override this behavior (so text will run off the right side of the display - useful for
                                        // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
                                        // with setTextWrap(true).
  display.dim(0);                       // Set brightness (0 is maximum and 1 is a little dim).
  delay(100);
}

void loop() {
  total = total - readings[readIndex];  // Advance to the next position in the array.
  readings[readIndex] = period;         // Takes the value that we are going to smooth.
  Serial.println(readings[readIndex]);
  total = total + readings[readIndex];  // Add the reading to the total.
  readIndex = readIndex + 1;            // Advance to the next position in the array.

  if (readIndex >= numReadings)         // If we're at the end of the array:
  {
    readIndex = 0;                      // Reset array index.
  }
  // Calculate the average:
  average = total / numReadings;        // The average value it's the smoothed result.

  // OLED 0.96" Display:
  // Convert variable into a string, so we can change the text alignment to the right:
  // It can be also used to add or remove decimal numbers.
  char string[10];                      // Create a character array of 10 characters
  // Convert float to a string:
  dtostrf(average, 6, 0, string);       // (<variable>,<amount of digits we are going to use>,<amount of decimal digits>,<string name>)

  display.clearDisplay();  // Clear the display so we can refresh.
  display.setFont(&FreeMonoBold18pt7b);  // Set a custom font.
  display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0.
  display.setCursor(0, 25);  // (x,y).
  display.println("RPM:");  // Text or value to print.

  // Print variable with right alignment:
  display.setCursor(0, 60);  // (x,y).
  display.println(string);  // Text or value to print.

  // Print a comma for the thousands separator:
  // if(average > 999)  // If value is above 999:
  // {
  //   // Draw line (to show a comma):
  //   display.drawLine(63, 60, 61, 65, WHITE);  // Draw line (x0,y0,x1,y1,color).
  // }

  display.display();  // Print everything we set previously.
  
  delay(100);
}
