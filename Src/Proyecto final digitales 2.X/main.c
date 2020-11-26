/*
/////////////////// DATOS DEL PROGRAMA ////////////////////

//  TTITULO: Led Blinkng
//  MICRO:PIC16F15244
//  ESTUDIANTES: David Felipe Enciso Noy
//  Profesor: Harold F MURCIA
//  FECHA: 24 de noviembre de 2020

///////////// CONFIGURACION del MCU ////////////////// */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <conio.h>


#pragma config FEXTOSC = OFF    // External Oscillator Mode Selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINTOSC_1MHZ    // Power-up Default Value for COSC bits->HFINTOSC (1 MHz)
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; I/O function on RA4
#pragma config VDDAR = HI    // VDD Range Analog Calibration Selection bit->Internal analog systems are calibrated for operation between VDD = 2.3V - 5.5V

// CONFIG2
#pragma config MCLRE = EXTMCLR    // Master Clear Enable bit->If LVP = 0, MCLR pin is MCLR; If LVP = 1, RA3 pin function is MCLR
#pragma config PWRTS = PWRT_OFF    // Power-up Timer Selection bits->PWRT is disabled
#pragma config WDTE = OFF    // WDT Operating Mode bits->WDT disabled; SEN is ignored
#pragma config BOREN = ON    // Brown-out Reset Enable bits->Brown-out Reset Enabled, SBOREN bit is ignored
#pragma config BORV = LO    // Brown-out Reset Voltage Selection bit->Brown-out Reset Voltage (VBOR) set to 1.9V
#pragma config PPS1WAY = ON    // PPSLOCKED One-Way Set Enable bit->The PPSLOCKED bit can be cleared and set only once in software
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset

// CONFIG4
#pragma config BBSIZE = BB512    // Boot Block Size Selection bits->512 words boot block size
#pragma config BBEN = OFF    // Boot Block Enable bit->Boot Block is disabled
#pragma config SAFEN = OFF    // SAF Enable bit->SAF is disabled
#pragma config WRTAPP = OFF    // Application Block Write Protection bit->Application Block is not write-protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block is not write-protected
#pragma config WRTC = OFF    // Configuration Registers Write Protection bit->Configuration Registers are not write-protected
#pragma config WRTSAF = OFF    // Storage Area Flash (SAF) Write Protection bit->SAF is not write-protected
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/Vpp pin function is MCLR. MCLRE Configuration bit is ignored.

// CONFIG5
#pragma config CP = OFF    // User Program Flash Memory Code Protection bit->User Program Flash Memory code protection is disabled



///////////// DEFINICIONES  //////////////////
#define _XTAL_FREQ 1000000
#define LED0_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LED0_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LED0_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LED0_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)


///////////// VARIABLES GLOBALES  //////////////////

int resultHigh,resultLow;
uint16_t Leer; 
uint16_t dutyValue;

///////////// DECLARACI�N DE FUNCIONES Y PROCEDIMIENTOS ///////////////////
void PIN_MANAGER_Initialize(void)
{
     LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    // TRISx registers
    TRISA = 0x3B;
    TRISB = 0xF0;
    TRISC = 0xFF;

    // ANSELx registers
    ANSELC = 0xFF;
    ANSELB = 0xF0;
    ANSELA = 0x33;

    // WPUx registers
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    // ODx registers
    ODCONA = 0x04;
    ODCONB = 0x00;
    ODCONC = 0x00;

    // SLRCONx registers
    SLRCONA = 0x37;
    SLRCONB = 0xF0;
    SLRCONC = 0xFF;

    // INLVLx registers
    INLVLA = 0x3F;
    INLVLB = 0xF0;
    INLVLC = 0xFF;

    // TRISx registers
    TRISA2 = 0;          // Definiendo puerto A2 como salida digital
    TRISC2 = 1;// Definiendo puerto C2 como entada digital
    ANSELAbits.ANSA5 = 1;// Definiendo entrada como analoga
    ANSELAbits.ANSA1 = 1;   //Definiendo entrada como analoga
    RA2PPS = 0x00;                                                              // RA2->PWM3:PWM3OUT; 
}



void OSCILLATOR_Initialize(void)
{
    OSCEN = 0x00;                                                               // MFOEN disabled; LFOEN disabled; ADOEN disabled; HFOEN disabled;
    OSCFRQ = 0x00;                                                              // HFFRQ0 1_MHz
    OSCTUNE = 0x00;
}

void TMR2_Initialize()
{
    T2CLKCON = 0x01;                                                            // T2CS FOSC/4;  
    T2HLT = 0x00;                                                               // T2PSYNC Not Synchronized; T2MODE Software control; T2CKPOL Rising Edge; T2CKSYNC Not Synchronized; 
    T2RST = 0x00; 
    T2PR = 249;  
    T2TMR = 0x00;
    PIR1bits.TMR2IF = 0;                                                        // Clearing IF flag.
    T2CON = 0b10000000;                                                               // T2CKPS 1:1; T2OUTPS 1:1; TMR2ON on; 
}

 void PWM3_Initialize(void)
 {     
    PWM3CON = 0x90;                                                             // PWM3POL active_low; PWM3EN enabled; 
    PWM3DCH = 0x3E;    
    PWM3DCL = 0x40;   
 }
 
void ADC (void)
{
 // Configure ADC
               
  
    
    ADCON1 = 0b10010000; //FM = 1 justificado a la derecha , CLOCK SELECT Fosc/8, PREF = 00 
    
    
    
    
}

void leer(void){
      if(resultHigh==0){
          Leer=resultLow;
      }
      else if(resultHigh==1){
          Leer=256+resultLow;
      }
      else if(resultHigh==2){ 
          Leer=512+resultLow;
      }
      else{
          Leer=768+resultLow;
      }
}

void calcular()
{
    if(Leer<=491)
    {
    LED0_SetHigh();
    }   
    else
    {
     LED0_SetLow();
    }
    
    
       
   
}

void Read_adc(void){
     ADCON0= 0b00010101;  
     ADCON0bits.GO = 1; // Start conversion
     while (ADCON0bits.GO); // Wait for conversion done
     resultHigh = ADRESH; // Read result
     resultLow = ADRESL; // Read result
     
     
     ADCON0= 0b00000101;
     ADCON0bits.GO = 1; // Start conversion
     while (ADCON0bits.GO); // Wait for conversion done
     resultHigh = ADRESH; // Read result
     resultLow = ADRESL; // Read result
    
}

 
  void PWM3_LoadDutyValue(uint16_t dutyValue)
 {     
     PWM3DCH = (dutyValue & 0x03FC)>>2;                                         // Writing to 8 MSBs of PWM duty cycle in PWMDCH register     
     PWM3DCL = (dutyValue & 0x0003)<<6;                                         // Writing to 2 LSBs of PWM duty cycle in PWMDCL register
 }
/////////////  INICIO DEL PROGRAMA PRINCIPAL //////////////////////////


void main(void)
{
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    
    PWM3_Initialize();
  
    PWM3_LoadDutyValue;
    
  
    while(1)
    {
        
      ADC();
      Read_adc();
      leer();
      calcular();
      TMR2_Initialize();
      
      __delay_ms(200);
      Read_adc();
      
      
    }
}
