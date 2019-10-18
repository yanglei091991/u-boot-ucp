#ifndef CONFIG_PLL_H
#define CONFIG_PLL_H
#include <stdint.h>

#define BIT12           (0x1 << 12ul)
#define BIT14           (0x1 << 14ul)
#define BIT16           (0x1 << 16ul)
#define BIT18           (0x1 << 18ul)

// config pll reg
#define CRG_BASE_ADDR   0x03670000
#define PLL1_CTRL       (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x05*4)))
#define PLL1_CONFIG0    (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x06*4)))

#define PLL3_CTRL       (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x0f*4)))
#define PLL3_CONFIG0    (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x10*4)))
#define PLL_SEL_CTRL    (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x14*4)))
#define SDIOCLK_CTRL    (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x5c*4)))

#endif // CONFIG_PLL_H
