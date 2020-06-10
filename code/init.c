#include "init.h"

void gpio_init (void)
{
    //Enable peripheral clocks for various ports and subsystems
    //Bit 4: Port C Bit3: Port B Bit 2: Port A
    RCC->APB2ENR |=  RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPAEN;
		GPIOC->CRH |= GPIO_CRH_MODE8;
		GPIOC->CRH &= ~GPIO_CRH_CNF8;
}

void motorDriverInit()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_TIM1EN | 	RCC_APB2ENR_IOPAEN;
	
	//PB10 to PB13: General purpose output push-pull, max speed 50 MHz
	//0x--3333--
	GPIOB->CRH |= GPIO_CRH_MODE10 | GPIO_CRH_MODE11 | GPIO_CRH_MODE12 | GPIO_CRH_MODE13;
	GPIOB->CRH &= ~GPIO_CRH_CNF10 & ~GPIO_CRH_CNF11 & ~GPIO_CRH_CNF12 & ~GPIO_CRH_CNF13;
	
	//PA8: Alternate function output Push-pull, max speed 50 MHz
	//0x-------B
	GPIOA->CRH = 0x44444444;	//GPIOA->CRH is giving 0x88844444 for some reason -- resetting it
	GPIOA->CRH |= GPIO_CRH_MODE8 | GPIO_CRH_CNF8_1;
	GPIOA->CRH &= ~GPIO_CRH_CNF8_0;
}

void pwmInit()
{
	TIM1->CR1 |= TIM_CR1_CEN; // Enable Timer1 
	TIM1->CR2 |= TIM_CR2_OIS1; // Output Idle State for Channel 1 OC1=1 when MOE=0 • 
	TIM1->EGR |= TIM_EGR_UG; // Reinitialize the counter  
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE;       //PWM mode 1, Preload Enable, Fast Enable 
	//TIM1->CCMR2 not used for this application  
	TIM1->CCER |= TIM_CCER_CC1E; //Enable CH1 output on PA8 
	TIM1->PSC = 0x095F; //Divide 24 MHz by 2400 , PSC_CLK = 10000 Hz, 1 count = 0.1 ms 
	TIM1->ARR = 100; //  100 counts = 10 ms 
	TIM1->CCR1 = 10; // 10 counts = 1 ms= 10% duty cycle  
	TIM1->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSI; //Main Output Enable, Force Idle Level First 
	TIM1->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // Enable Timer
}

 void obstacleSensorInit()
 {
	 RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN;
	 
	 RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	 
	 //PC13: General purpose output push-pull, max speed 50 MHz
	 //0x--3-----
	 //Trigger pin	//front
	 GPIOC->CRH |= GPIO_CRH_MODE13;
	 GPIOC->CRH &= ~GPIO_CRH_CNF13;
	 
	 //PB6: left
	 //PB7: right
	 GPIOB->CRL |= GPIO_CRL_MODE6 | GPIO_CRL_MODE7;
	 GPIOB->CRL &= ~GPIO_CRL_CNF6 & ~GPIO_CRL_CNF7;
	
	 //GPIOC->CRH &= 0xFF3FFFF;

	 
	 //PA9, PA15, PD2: Input with pull-up / pull-down
	 //0x------4--
	 //No need to code it since it is in reset state
	 //Echo pin
	 //GPIOD->CRL &= 0xFFFFF4FF;
	 
	 
	 //FOR TESTING: REMOVE LATER
	 //GPIOA->CRH |= GPIO_CRH_MODE11 | GPIO_CRH_MODE10 | GPIO_CRH_MODE12;
	 //GPIOA->CRH &= ~GPIO_CRH_CNF11 & ~GPIO_CRH_CNF10 & ~GPIO_CRH_CNF12;
	 
 }

void lineFollowerInit()
{
	
	//All are inputs, no need to initialize anything
	//I1: PA15
	//I2: PB6
	//I3: PB7
	//I4: PA4
	//I5: PB15
	
	//configure clock for AFIOEN and ADC1EN
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN;
		
	// configure 1 and 2 as 0000 -- analog input mode
	
	GPIOA->CRL &= ~GPIO_CRL_CNF1 & ~GPIO_CRL_MODE1 & ~GPIO_CRL_CNF2 & ~GPIO_CRL_MODE2 & ~GPIO_CRL_CNF3 & ~GPIO_CRL_MODE3;
	GPIOA->BSRR &= ~GPIO_BRR_BR1 & ~GPIO_BRR_BR2 & ~GPIO_BRR_BR3;  
	
	
	//GPIOA->CRL &= (GPIO_CRL_CNF2 | GPIO_CRL_MODE2 | GPIO_CRL_CNF1 | GPIO_CRL_MODE1 | GPIO_CRL_CNF3 | GPIO_CRL_MODE3)&0;
	
	//turn on ADC
	ADC1->CR2 = 0x1;
}