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

uint16_t  periodo;                             //tempo entre uma volta completa
uint16_t  overFlowTime;                        //tempo para verificar os pulsos
// ============================================================================
// --- Interrupções ---
ISR(INT0_vect)
{
  counter ++;

  if(counter == 1)                             //começa a contar o tempo para uma volta
  {                                           
    TCCR1B |= (1<<CS11);                       //habilita contagem com PS 1:8
  }
  if(counter == 2 || counter == 3)
  {
    return;
  }
  else
  {
    TCCR1B = 0x00;                             //desliga timer1
    periodo  = TCNT1;                          //salva tempo de uma volta em µs x 2
    periodo >>= 1;                             //divide por 2 o valor anterior
    TCNT1  = 0x00;                             //reinicia valor do timer1
  }
} //end ISR INT0

ISR(TIMER0_OVF_vect)                           //Rotina de interrupção
{
	if(cnt==49)                                  //Total de 200ms            
	{
	 
	} //end if cnt

} //end ISR Timer0

void setup() {  
  //Configuração das Interrupções.
  cli();                                       //Desabilita interrupções

  DDRD &= ~(1<<DDD2);                          //configura PD2 como entrada  *registrador fica setado como zero

  PORTD |= (1<<PORTD2);                        //habilita pull-up interno de PD
  
  TCNT0  = 0x00;                               //inicia Timer0 
  TCCR0B = 0x04;                               //configura o prescaler para 1:256 (guardara o valor de overflow)
  TCCR1B = 0x00;                               //desliga timer1                   (guardara o valor de uma volta)
  TIMSK0 = 0x01;                               //habilita interrupção por overflow do Timer0
  EICRA |= (1<<ISC01) | (1<<ISC00);            //interrupção externa por borda de subida inicialmente
  EIMSK |= (1<<INT0);                          //habilita interrupção externa
  
  sei();                                       //Habilita as interrupções
  
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  sens_RPM(periodo);
}


// ============================================================================
// Calcula RPM conforme sensor
void sens_RPM(uint16_t pulse)
{
  pulse = periodo/1000000                      //converte de µs para s
   
 	freqAngular = (2*3.14) / pulse;
  Serial.print("Frequencia angular: ");
  Serial.println(freqAngular);

  rpm = 60 / pulse;
  Serial.print("RPM: ");
  Serial.println(rpm);
} 

