#ifndef CONFIG_PLL_H
#define CONFIG_PLL_H
#include <stdint.h>

// config pll reg
#define CRG_BASE_ADDR   0x03670000

#define PLL1_CTRL       (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x05*4)))
#define PLL1_CONFIG0    (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x06*4)))
#define PLL1_CONFIG2    (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x08*4)))

#define PLL3_CTRL       (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x0f*4)))
#define PLL3_CONFIG0    (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x10*4)))
#define PLL3_CONFIG2    (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x12*4)))


#define PLL_SEL_CTRL    (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x14*4)))
#define SDIOCLK_CTRL    (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x5c*4)))
#define SRIOCLK_CTRL    (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x73*4)))
#define RFC_TUNINGCLK_CTRL     (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x63*4)))

#define DMA0CLK_CTRL           (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x6B*4)))
#define DMAS0CLK_CTRL          (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x2f*4)))
#define DMAS1CLK_CTRL          (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x30*4)))

#define APHCLK_CTRL            (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x28*4)))
#define CPHCLK_CTRL            (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x29*4)))

#define APSUB0PCLK_CTRL        (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x2a*4)))
#define APSUB1PCLK_CTRL        (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x2b*4)))
#define APSUB2PCLK_CTRL        (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x2c*4)))

#define CPAHBCLK_CTRL          (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x2d*4)))
#define CPAPBCLK_CTRL          (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x2e*4)))

#define TIMER00CLK_CTRL        (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x31*4)))
#define TIMER01CLK_CTRL        (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x32*4)))
#define TIMER02CLK_CTRL        (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x33*4)))
#define TIMER03CLK_CTRL        (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x34*4)))

#define UART0CLK_CTRL          (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x49*4)))
#define UART1CLK_CTRL          (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x4a*4)))
#define UART2CLK_CTRL          (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x4b*4)))
#define UART3CLK_CTRL          (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x4c*4)))

#define SSI0CLK_CTRL           (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x4f*4)))
#define SSI1CLK_CTRL           (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x50*4)))
#define SSI2CLK_CTRL           (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x51*4)))
#define SSI3CLK_CTRL           (*((volatile uint32_t *)(CRG_BASE_ADDR + 0x52*4)))


#endif // CONFIG_PLL_H
