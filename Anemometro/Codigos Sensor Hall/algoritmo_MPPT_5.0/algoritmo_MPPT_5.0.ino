//Primeira versão para rodar o sistema mais completo em ATMega2560
//Nesse algoritmo já tento implementar o conversor Boost com tensão de saída regulada em paralelo com o conversor Buck operando como MPPT  


//=====================================
//--------- frequência da CPU ---------
#define F_CPU 16000000


//=====================================
//----------- Bibliotecas -------------
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h> 
#include <Wire.h>
#include "ADS1X15.h"
#include <PID_v1.h>

//=====================================
//------ Mapeamento de Hardware -------
#define   pwm_mppt    (1<<PB5)
#define   pwm_boost_h (1<<PL3)
//#define   pwm_boost_l (1<<PL4)
#define   TSAMPLE     50000
#define   tempo_morto 3

//=====================================
//------ Definições importantes -------
#define   Freq_PWM_MPPT    31000   //frequência do PWM
#define   Freq_PWM_BOOST   35000   //frequência do PWM
//#define   Tempo_morto 8       //valor do tempo morto em ciclos do timer

ADS1115 ADS(0x48);

//===========================================================
//----------- Variaveis Globais -------------

float Tensao_fonte            = 0,
      Corrente_fonte          = 0,
      Tensao_BOOST            = 0,
      Corrente_BOOST          = 0,
      Tensao_filtrada         = 0,
      Corrente_filtrada       = 0,
      Tensao_filtrada_BOOST   = 0,
      Corrente_filtrada_BOOST = 0,
      Tensao_ref_k            = 0,
      Tensao_ref_fonte        = 0,
      Tensao_ref_maxima       = 0,
      Tensao_ref_minima       = 0,
      Tensao_ref_fonte_BOOST  = 0,
      Tensao_ref_maxima_BOOST = 0,
      Tensao_ref_minima_BOOST = 0,     
      Tensao_ref_k_BOOST      = 0;


unsigned long Tempo_anterior  = 0,
              Tempo_atual     = 0;

static unsigned int   PASSO_MPPT         = 1,
                      Maximo_ICR1        = 0,
                      Maximo_ICR5        = 0,
                      Tensao_circ_aberto = 44;


// ============================================================================
// --- Protótipo das Funções ---
void Algoritmo_MPPT();

void Desloca_vetor();

void Filtro_PB_tensao_MPPT();

void Filtro_PB_corrente_MPPT();

void Filtro_PB_tensao_BOOST();

void Filtro_PB_corrente_BOOST();

//PID controlador(&Tensao_ref_fonte, &OCR0A, &Tensao_ref_maxima, Kp, Ki, Kd, 1, 0);

// ============================================================================
// ------------------- Interrupções -------------------


//--------- Interrupção do algoritmo de controle do conversor Boost para estabilização da tensão no barramento CC ------------

ISR(TIMER2_OVF_vect) 
{
  static int contador = 0;

  contador++;

  if (contador == 10)
  {
    contador = 0;
  }

}


//---------Interrupção do algoritmo MPPT---------------

ISR(TIMER3_OVF_vect) 
{
  Algoritmo_MPPT(Corrente_filtrada, Tensao_filtrada);
}


//---------Interrupção da Máquina de estados---------------

ISR(TIMER4_OVF_vect) 
{
  static int contador1 = 0;

  contador1++;

  Serial.print(contador1);
  Serial.print(" ");
  if (contador1 == 99)
  {
    contador1 = 10;
  }
}



//=============================================================
//--------- Função principal ----------
void setup()
{


  //define as saidas PWM
  DDRB  |=  pwm_mppt;
  DDRL  |=  pwm_boost_h;
  //DDRL  |=  pwm_boost_l;

  //incializamos os bits do PWM em LOW
  PORTB  &=  ~pwm_mppt;
  PORTL  &=  ~pwm_boost_h;
  //PORTL  &=  ~pwm_boost_l;
  

 
  //configuração do PWM do timer1
  TCCR1A  = 0b10101010;   //configura o PWM no modo Phase Correct com Interrupt Flag Set ICR1 habilitada
  TCCR1B  = 0b00011001;   //Pre Scaler 1:1

  Maximo_ICR1 = (F_CPU / (1 + Freq_PWM_MPPT));       // define o valor máximo da Interrupt Flag Set ICR1 para a frequência do PWM escolhida
  Tensao_ref_maxima  = Maximo_ICR1 * 0.60;           // limita o valor máximo do dutty cicle do PWM em 65%. Ganho máximo G(D) de 4,00x na tensão de entrada do conversor 
  Tensao_ref_minima  = Maximo_ICR1 * 0.10;           // limita o valor mínimo do dutty cicle do PWM em 05%. Ganho mínimo G(D) de 1,43x na tensão de entrada do conversor
  Tensao_ref_fonte   = Maximo_ICR1 * 0.30;
  Tensao_ref_k       = Tensao_ref_fonte + 1;
  
  ICR1 = Maximo_ICR1; //atribui o valor máximo de contagem calculado à flag ICR1


  //configuração do PWM do timer5
  TCCR5A  = 0b10101010;   //configura o PWM no modo Phase Correct com Interrupt Flag Set ICR5 habilitada
  TCCR5B  = 0b00011001;   //Pre Scaler 1:1

  Maximo_ICR5 = (F_CPU / (1 + Freq_PWM_BOOST));       // define o valor máximo da Interrupt Flag Set ICR5 para a frequência do PWM escolhida
  Tensao_ref_maxima_BOOST  = Maximo_ICR5 * 0.60;      // limita o valor máximo do dutty cicle do PWM em 65%. Ganho máximo G(D) de 4,00x na tensão de entrada do conversor 
  Tensao_ref_minima_BOOST  = Maximo_ICR5 * 0.05;      // limita o valor mínimo do dutty cicle do PWM em 05%. Ganho mínimo G(D) de 1,43x na tensão de entrada do conversor
  Tensao_ref_fonte_BOOST   = Maximo_ICR5 * 0.10;
  Tensao_ref_k_BOOST       = Tensao_ref_fonte + 1;
  
  ICR5 = Maximo_ICR5; //atribui o valor máximo de contagem calculado à flag ICR5

  OCR5A = 50;
  OCR5B = 256;
  
  //Configuração das Interrupções.
  cli();                  //desliga interrupções

  //Configuração das interrupções por estouro do TIMER2 (8bits) para rodar o algoritmo de comando do conversor Boost
  TCCR2B = 0b00000111;    //prescaler 1:1024
  TIMSK2 = 0b00000001;    //habilita o estouro do TIMER2 como fonte de interrupção do
  TCNT2  = 204;           //inicia Timer2 para contar a partir de 204 e estabelecer uma frequencia de ~300Hz

  //Configuração das interrupções por estouro do TIMER3 (16bits) para rodar o algoritmo MPPT do conversor Buck  
  TCCR3B = 0b00000101;    //prescaler 1:1024
  TIMSK3 = 0b00000001;    //habilita o estouro do TIMER3 como fonte de interrupção
  TCNT3  = 60327;         //inicia Timer3 para contar a partir de 6327 e estabelecer uma frequencia de ~3Hz
 
  //Configuração das interrupções por estouro do TIMER4 (16bits) para rodar o algoritmo da máquina de estados que verifica os limites seguros deoperação.
  TCCR4B = 0b00000101;    //prescaler 1:1024
  TIMSK4 = 0b00000001;    //habilita o estouro do TIMER4 como fonte de interrupção
  TCNT4 = 64792;          //inicia Timer4 para contar a partir de 64792 e estabelecer uma frequencia de 21Hz
  
  sei();



  Wire.begin();
  Serial.begin(115200);

  ADS.begin();
  ADS.setGain(1);      // 4.096V volt
  ADS.setDataRate(7);  // 0 = slow   4 = medium   7 = fast
  ADS.setMode(1);      // continuous mode
  ADS.readADC(0);      // first read to trigger
  
  // set the thresholds to Trigger RDY pin
  ADS.setComparatorThresholdLow(0x0000);
  ADS.setComparatorThresholdHigh(0x0200);
  ADS.setComparatorQueConvert(0);             // enable RDY pin !!
  ADS.setComparatorLatch(0);

  //conrtrolador.SetMode(AUTOMATIC);

} //FIM DA FUNÇÃO PRINCIPAL


//---------- LOOP INFINITO ----------
void loop()
{ //INÍCIO DO LOOP INFINITO

  ADS.setGain(1);
  float voltage = 0.0,
        f       = ADS.toVoltage(1);   // voltage factor

  static int  cont = 0;


  Tensao_fonte = ((ADS.readADC(0) * f ) - 0.0031) * 250;       // calculo baseado na relação de 4mV/V na saída do sensor de tensão
  Tensao_filtrada = Filtro_PB_tensao_MPPT(Tensao_fonte);
  
  Corrente_fonte = ((ADS.readADC(1) * f ) - 1.4562) / 0.0187 ;       // calculo baseado na relação de 18.7mV/A na saída do sensor de corrente
  Corrente_filtrada = Filtro_PB_corrente_MPPT(Corrente_fonte);

  Tensao_BOOST = ((ADS.readADC(2) * f ) - 0.0095) * 250;       // calculo baseado na relação de 4mV/V na saída do sensor de tensão
  Tensao_filtrada_BOOST = Filtro_PB_tensao_BOOST(Tensao_BOOST);
  
  Corrente_BOOST = ((ADS.readADC(3) * f ) - 1.52) / 0.0187 ;       // calculo baseado na relação de 18.7mV/A na saída do sensor de corrente
  Corrente_filtrada_BOOST = Filtro_PB_corrente_BOOST(Corrente_BOOST);


  //delay(4);

} //FIM DO LOOP INFINITO





//===========================================================
//--------- Desenvolvimento das Funções ----------


void Algoritmo_MPPT(float corrente, float tensao) 
{
  //variaveis locais da função
  static float  deltaV              = 0,
                tensao_anterior     = 0,
                potencia_anterior   = 0,
                potencia_fonte      = 0;

  int           Incializacao_MPPT   = 0;
  
  //Calculo do valor atual da potência a partir da variação da tensão 
  potencia_fonte = corrente * tensao;
  //deltaV = tensao - tensao_anterior;
  deltaV = Tensao_ref_k - Tensao_ref_fonte;

  if((tensao > (Tensao_circ_aberto - 3)) && (Incializacao_MPPT == 0))
    {
      Tensao_ref_fonte = Tensao_ref_fonte - 2;
    }
  else
    {
      Incializacao_MPPT = 1;
    }
  
  //Algoritmo MPPT

  if(potencia_fonte == potencia_anterior)
  {
    Tensao_ref_k = Tensao_ref_fonte;
  }
  else
  {
    if(potencia_fonte > potencia_anterior)
    {
      if(deltaV > 0) 
      {
        Tensao_ref_k = Tensao_ref_fonte += PASSO_MPPT;
      }
      else 
      {
        Tensao_ref_k = Tensao_ref_fonte -= PASSO_MPPT;
      }
      //Serial.println("Laço 2");
    }
    else
      {
        if(deltaV > 0) 
        {
          Tensao_ref_k = Tensao_ref_fonte -= PASSO_MPPT;
        }
        else
        {
          Tensao_ref_k = Tensao_ref_fonte += PASSO_MPPT;
        }
        //Serial.println("Laço 3");
      }
  }
  
  OCR1A = Tensao_ref_fonte; //- tempo_morto;
  //OCR1B = Tensao_ref_fonte; //+ tempo_morto;
 
  ///*
  Serial.print(tensao);
  Serial.print("V ");

  Serial.print(corrente);
  Serial.print("A ");

  Serial.print(potencia_fonte);
  Serial.print("W ");

  Serial.print(Tensao_filtrada_BOOST);
  Serial.print("V ");

  Serial.print(Corrente_filtrada_BOOST);
  Serial.println("A ");
  //Serial.println(Tensao_ref_fonte);
  //*/

  //Limites para estabelecer a saturação do volores máximos do MPPT
  if(Tensao_ref_fonte > Tensao_ref_maxima) Tensao_ref_fonte = Tensao_ref_maxima;
  else if(Tensao_ref_fonte < Tensao_ref_minima) Tensao_ref_fonte = Tensao_ref_minima;

  //Armazenamento dos volores presentes nas variaveis de valores do passado
  tensao_anterior = tensao;
  potencia_anterior = potencia_fonte;   // Armazena o valor de potência calculado anteriormente
  
}


void Desloca_vetor(float *vetorAddr, int tam, float valor)
{
  for(int k = tam - 1; k > 0; k--)
  {
    *(vetorAddr + k) = *(vetorAddr + k - 1);
  }
  *vetorAddr = valor;
}


float Filtro_PB_tensao_MPPT(float x)
{
  static float  y_pass1[2] = {0,0},
                x_pass1[2] = {0,0};

  const float   a = 0.45,
                b = 0.50;
  
  float y = ((a + b) * y_pass1[0]) - (a * b * y_pass1[1]) + ((1 - a - b + (a * b)) * x_pass1[1]);

  Desloca_vetor(y_pass1, 2, y);
  Desloca_vetor(x_pass1, 2, x);
  
  return y;
}


float Filtro_PB_corrente_MPPT(float x)
{
  static float  y_pass2[2] = {0,0},
                x_pass2[2] = {0,0};

  const float   a = 0.65,
                b = 0.70;
  
  float y = ((a + b) * y_pass2[0]) - (a * b * y_pass2[1]) + ((1 - a - b + (a * b)) * x_pass2[1]);

  Desloca_vetor(y_pass2, 2, y);
  Desloca_vetor(x_pass2, 2, x);
  
  return y;
}



float Filtro_PB_tensao_BOOST(float x)
{
  static float  y_pass3[2] = {0,0},
                x_pass3[2] = {0,0};

  const float   a = 0.45,
                b = 0.50;
  
  float y = ((a + b) * y_pass3[0]) - (a * b * y_pass3[1]) + ((1 - a - b + (a * b)) * x_pass3[1]);

  Desloca_vetor(y_pass3, 2, y);
  Desloca_vetor(x_pass3, 2, x);
  
  return y;
}


float Filtro_PB_corrente_BOOST(float x)
{
  static float  y_pass4[2] = {0,0},
                x_pass4[2] = {0,0};

  const float   a = 0.65,
                b = 0.70;
  
  float y = ((a + b) * y_pass4[0]) - (a * b * y_pass4[1]) + ((1 - a - b + (a * b)) * x_pass4[1]);

  Desloca_vetor(y_pass4, 2, y);
  Desloca_vetor(x_pass4, 2, x);
  
  return y;
}
