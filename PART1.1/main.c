#define MYWAIT 1000000
int main(void)
{
 volatile unsigned int *GPIOA_MODER = (unsigned int*) (0x40020000 + 0x00);
 volatile unsigned int *GPIOA_ODR = (unsigned int*) (0x40020000 + 0x14);
 volatile unsigned int *GPIOC_MODER = (unsigned int*) (0x40020800 + 0x00);
 volatile unsigned int *GPIOC_IDR = (unsigned int*) (0x40020800 + 0x10);
 volatile unsigned int *RCC_AHB1ENR = (unsigned int*) (0x40023800 + 0x30);
 *RCC_AHB1ENR |= 0x05U;
 *GPIOA_MODER = *GPIOA_MODER | 0x400;
 *GPIOC_MODER = *GPIOC_MODER | 0x000;
 unsigned int button;
 while (1){
	 button=(*GPIOC_IDR & (0x01 << 13)) >> 13;
	 if(button==0){
		 *GPIOA_ODR |= 0x20;
	 } else{
		 *GPIOA_ODR &= ~0x20;
	 }
}
}
