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
#define    hall    (1<<PD2)

// ============================================================================
// --- Variáveis Globais ---
unsigned counter = 0x00;                       // contador de pulsos
uint16_t  ptime = 0;                           // tempo entre uma volta completa

// ============================================================================
// --- Interrupções ---
ISR(INT0_vect)
{
  if(!(TCCR1B&(1<<CS11)))                      //timer1 desligado?
  {                                            //sim
    TCCR1B |= (1<<CS11);                       //habilita contagem com PS 1:8
	  //EICRA &= ~(1<<ISC00);                      //configura interrupção externa para borda de descida
  }
  
  else
  {
    TCCR1B = 0x00;                             //desliga timer1
    ptime  = TCNT1;                            //salva largura de pulso em µs x 2
    TCNT1  = 0x00;                             //reinicia valor do timer1
    EICRA |= (1<<ISC00);                       //configura interrupção externa para borda de subida  
    ptime >>= 1;
  }
	
} //end ISR INT0

ISR(TIMER0_OVF_vect)                         //Rotina de interrupção
{
	
	//base de tempo de 1ms
	TCNT0 = 0x06;                              //reinicializa Timer0
	counter++;
	
	if(cnt==80)
	{
	  //base de tempo de 80ms 
	  cnt = 0;
	  PORTC |=  hall;
	  _delay_us(10);
	  PORTC &= ~hall;	
	 
	} //end if cnt

} //end ISR Timer0

void setup() {  
  //Configuração das Interrupções.
  
  cli();                                       //desliga interrupções

  DDRD &= ~(1<<DDD2);                          //configura PD2 como entrada  *registrador fica setado como zero

  PORTD |= (1<<PORTD2);                        //habilita pull-up interno de PD
  
  TCNT0  = 0x00;                               //inicia Timer0 
  TCCR0B = 0x04;                               //configura o prescaler para 1:256
  TIMSK0 = 0x01;                               //habilita interrupção por overflow do Timer0
  EICRA |= (1<<ISC01) | (1<<ISC00);            //interrupção externa por borda de subida inicialmente
  EIMSK |= (1<<INT0);                          //habilita interrupção externa
  
  sei();                                       //habilita as interrupções
  
  Wire.begin();
  Serial.begin(115200);
}

void loop() {
  sens_RPM();
}


// ============================================================================
// Calcula RPM conforme sensor
void sens_RPM(uint16_t pulse, int gval, int yval, int rval)
{

   
 	
} 

