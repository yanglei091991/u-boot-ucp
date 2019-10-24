#include <stdint.h>

#define BIT12           (0x1 << 12ul)

// config pll reg
#define CRG_BASE_ADDR   0x03670000
#define RST_CTRL2       (*((volatile uint32_t *) (CRG_BASE_ADDR + 0x56*4)))
void reset_cpu(uint32_t addr)
{
    RST_CTRL2 |= BIT12;
}

