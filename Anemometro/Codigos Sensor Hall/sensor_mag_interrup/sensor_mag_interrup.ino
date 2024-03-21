// algoritmo para usar sensor magnético com interrupção

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
// --- Mapeamento de Hardware ---
//#define    hall    (1<<PD2)

// ============================================================================
// --- Variáveis Globais ---
unsigned counter       = 0x00;                 //contador de pulsos
int pulsosPorRevolucao = 3,                    //total de imãs
    rpm                   ,
    freqAngular           ;

float   periodo1,                         //tempo entre uma volta completa
        periodo2,                         //tempo entre uma volta completa
        periodo3,                         //tempo entre uma volta completa
        periodoM;                         //tempo entre uma volta completa
uint16_t  overFlowTime;                         //tempo para verificar os pulsos

// ============================================================================
// --- Interrupções ---
ISR(INT0_vect)
{
  counter ++;
  // Serial.print("Counter");
  // Serial.println(counter);

  if(counter == 1){                            //começa a contar o tempo para uma volta                      
    //Serial.println("1");  
    //Serial.println(TCNT1);                       
    TCCR1B |= (1<<CS12) | (0<<CS11) | (1<<CS10);  //habilita clock/1024(From prescaler)
  }
  else if(counter == 2){
    TCCR1B = 0x00;                             //desliga timer1
    periodo1 = TCNT1;                          //salva tempo de uma volta em µs x 2
    //periodo1 >>= 1;                            //divide por 2 o valor anterior
    //periodo1 = periodo1/2;
    TCCR1B |= (1<<CS12) | (0<<CS11) | (1<<CS10);  //habilita clock/1024(From prescaler)
    //Serial.println("2");
  }
  else if(counter == 2){
    TCCR1B = 0x00;                             //desliga timer1
    periodo2 = TCNT1;                          //salva tempo de uma volta em µs x 2
    //periodo2 >>= 1;                            //divide por 2 o valor anterior
    //periodo2 = periodo2/2;
    TCCR1B |= (1<<CS12) | (0<<CS11) | (1<<CS10);  //habilita clock/1024(From prescaler)
    //Serial.println("3");
  }
  else{
    //Serial.println("4");
    TCCR1B = 0x00;                                  //desliga timer1
    periodo3  = TCNT1;                              //salva tempo de uma volta em µs x 2
    //periodo3 >>= 1;                               //divide por 2 o valor anterior
    //periodo3 = periodo3/2;
    periodoM = (periodo1 + periodo2 + periodo3) * 100000 ;
    //periodoM = periodoM * 1000000;                //converte de µs para s
    //Serial.println(periodoM);              
    float freq;
    freq = (1 / periodoM ) ;                   //converte de µs para s
    //Serial.print("Freq: ");
    Serial.println(freq);
    //Serial.println("hz");
    //Serial.println("---------------------------------");
    TCNT1  = 0x00;                                   //reinicia valor do timer1
    counter = 0;
  }
} //end ISR INT0


void setup() {  
  //Configuração das Interrupções.
  cli();                                       //Desabilita interrupções

  DDRD &= ~(1<<PD2);                           //configura PD2 como entrada  *registrador fica setado como zero

  PORTD |= (1<<PD2);                           //habilita pull-up interno de PD
  
  //TCNT0  = 0x01FF;                               //inicia Timer0 
  //TCCR0B = 0x04;                               //configura o prescaler para 1:256 (guardara o valor de overflow)
  TCCR1B = 0x00;                               //desliga timer1                   (guardara o valor de uma volta)
  //TIMSK0 = 0x01;                             //habilita interrupção por overflow do Timer0
  EICRA |= (1<<ISC01) | (1<<ISC00);            //interrupção externa por borda de subida inicialmente
  EIMSK |= (1<<INT0);                          //habilita interrupção externa
  
  sei();                                       //Habilita as interrupções
  
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Setup ready");
  delay(100);
}

void loop() {
  //sens_RPM(periodo);
  //delay(100);
}


// ============================================================================
// Calcula RPM conforme sensor
void sens_RPM(unsigned int periodo)
{
  unsigned int pulse;
  Serial.println(periodo);
  // pulse = periodo/1000000;                      //converte de µs para s
   
 	// freqAngular = (2*3.14) / pulse;
  // Serial.print("Frequencia angular: ");
  // Serial.println(freqAngular);

  // rpm = 60 / pulse;
  // Serial.println("RPM: ");
  // Serial.println(rpm);
} 

