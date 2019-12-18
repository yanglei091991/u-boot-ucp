
根据需求修改makefile里的几个宏
UART：       注掉boot时关掉串口打印
SOC_PLL_CFG：PLL初始化,在FPGA板上时关掉
SOC_CLK_CFG:  在FPGA板上时关掉,soc时打开(SPI0时钟配置为1M)

======
soc测试时
#CFLAGS    += -DUART
CFLAGS    += -DSOC_PLL_CFG -DSOC_CLK_CFG

======
FPGA测试时
CFLAGS    += -DUART
#CFLAGS    += -DSOC_PLL_CFG -DSOC_SPI_1M
======

spi0 nand flash启动时，没有用spi0_ssn,用GPIO--CDATA[2]/AP_GPIOB20
来做为spi的片选。



