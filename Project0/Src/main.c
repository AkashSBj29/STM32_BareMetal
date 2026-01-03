// Where is the LED connected?
// Port: A
// Pin: 6
// AHB - Advanced High performance Bus
// APB - Advanced Peripheral Bus

#define PERIPH_BASE (0x40000000UL)
#define AHB1_BASE (PERIPH_BASE + 0x20000UL)
#define GPIOA_BASE (AHB1_BASE)
#define RCC_BASE (AHB1_BASE + 0x3800UL)
#define AHB1EN_BASE_R (*(volatile unsigned int*)(RCC_BASE + 0x30UL))
#define GPIO_AEN (1UL << 0)
#define GPIO_A_MODE_R (*(volatile unsigned int*)(GPIOA_BASE + 0x0UL))
#define GPIO_A_OD_R (*(volatile unsigned int*)(GPIOA_BASE + 0x14UL))
#define LED_PIN_0 (1U<<6)

int main(void) {
  // Enable clock access to GPIO_A
  AHB1EN_BASE_R |= GPIO_AEN;

  // Set PA6 as output pin
  GPIO_A_MODE_R |=  (1U << 12);
  GPIO_A_MODE_R &= ~(1U << 13);

  while(1) {
    // Toggle PIN 6 on and off
    GPIO_A_OD_R ^= LED_PIN_0;
    for(int i = 0; i < 500000; ++i) {}
  }
}
