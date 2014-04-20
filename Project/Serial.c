

/******************************************************************************/
/* SERIAL.C: Low Level Serial Routines                                        */
/******************************************************************************/
#include "LPC17xx.H"                     // LPC23xx definitions
#define UART0        1                      // Use UART 0 for printf

  // If UART 0 is used for printf
#ifdef UART0
  #define UxFDR  U0FDR
  #define UxLCR  U0LCR
  #define UxDLL  U0DLL
  #define UxDLM  U0DLM
  #define UxLSR  U0LSR
  #define UxTHR  U0THR
  #define UxRBR  U0RBR
  // If UART 1 is used for printf
#elif defined(UART1)
  #define UxFDR  U1FDR
  #define UxLCR  U1LCR
  #define UxDLL  U1DLL
  #define UxDLM  U1DLM
  #define UxLSR  U1LSR
  #define UxTHR  U1THR
  #define UxRBR  U1RBR
#endif

void init_serial (void)  {               // Initialize Serial Interface
  #ifdef UART0
    PINSEL0 = (PINSEL0&(~0x0F))|0x50;    // Enable TxD0 and RxD0
  #elif defined (UART1)
    PINSEL0 |= 0x40000000;               // Enable TxD1
    PINSEL1 |= 0x00000001;               // Enable RxD1
  #endif
	UxFDR    = 0;                          // Fractional divider not used
	UxLCR    = 0x83;                       // 8 bits, no Parity, 1 Stop bit
//	UxDLL    = 78;			//kk		// 9600 Baud Rate @ 12.0 MHZ PCLK
	UxDLL    = 13;                         // 57600 Baud Rate @ 12.0 MHZ PCLK
	UxDLM    = 0;                          // High divisor latch = 0
	UxLCR    = 0x03;                       // DLAB = 0
}

//---Implementation of sendchar (also used by printf function to output data)
int sendchar (int ch) 	// Write character to Serial Port
{                 
   while (!(UxLSR & 0x20));
  return (UxTHR = ch);
}

//---------      -----------
int getkey (void)  	   // Read character from Serial Port
{                     
  while (!(UxLSR & 0x01));
  return (UxRBR);
}
 

