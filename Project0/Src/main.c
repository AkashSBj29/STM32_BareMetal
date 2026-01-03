// Where is the LED connected?
// Port: A
// Pin: 6
// AHB - Advanced High performance Bus
// APB - Advanced Peripheral Bus
//

#include <stdint.h>

#define PERIPH_BASE (0x40000000UL)
#define AHB1_BASE (PERIPH_BASE + 0x20000UL)
#define GPIOA_BASE (AHB1_BASE)
#define RCC_BASE (AHB1_BASE + 0x3800UL)
#define GPIO_AEN (1UL << 0)
#define LED_PIN_0 (1U<<6)

#define __IO volatile

typedef struct {
  volatile uint32_t __dummy__[12];
  volatile uint32_t AHB1_EN_R; // AHB1 peripheral clock register.
} RCC_TypeDef;

typedef struct {
  volatile uint32_t MODE_R; // GPIO port mode register.
  volatile uint32_t __dummy__[4];
  volatile uint32_t OD_R; // GPIO port output data register.
} GPIO_TypeDef;

#define RCC ((RCC_TypeDef*) RCC_BASE)
#define GPIO_A ((GPIO_TypeDef*) GPIOA_BASE)

int main(void) {
  // Enable clock access to GPIO_A
  RCC->AHB1_EN_R |= GPIO_AEN;

  // Set PA6 as output pin
  GPIO_A->MODE_R |=  (1U << 12);
  GPIO_A->MODE_R &= ~(1U << 13);

  while(1) {
    // Toggle PIN 6 on and off
    GPIO_A->OD_R ^= LED_PIN_0;
    for(int i = 0; i < 500000; ++i) {}
  }
}
