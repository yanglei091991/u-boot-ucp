//******************** (C) COPYRIGHT 2019 SmartLogic*******************************
// FileName           : ucp_param.h
// Author             : lijian, jian.li@smartlogictech.com
// Date First Issued  : 2019-03-29 02:37:50 PM
// Last Modified      : 2019-04-11 11:26:54 AM
// Description        :
// ------------------------------------------------------------
// Modification History:
// Version    Date       Author    Modification Description
//
//**********************************************************************************

#ifndef __IO_UCP_H
#define __IO_UCP_H

typedef  unsigned char              UINT8;
typedef  unsigned short             UINT16;
typedef  unsigned int               UINT32;
typedef  unsigned long long         UINT64;


#define     BIT0                    (0x1<<0ul)
#define     BIT1                    (0x1<<1ul)
#define     BIT2                    (0x1<<2ul)
#define     BIT3                    (0x1<<3ul)
#define     BIT4                    (0x1<<4ul)
#define     BIT5                    (0x1<<5ul)
#define     BIT6                    (0x1<<6ul)
#define     BIT7                    (0x1<<7ul)
#define     BIT8                    (0x1<<8ul)
#define     BIT9                    (0x1<<9ul)
#define     BIT10                   (0x1<<10ul)
#define     BIT11                   (0x1<<11ul)
#define     BIT12                   (0x1<<12ul)
#define     BIT13                   (0x1<<13ul)
#define     BIT14                   (0x1<<14ul)
#define     BIT15                   (0x1<<15ul)
#define     BIT16                   (0x1<<16ul)
#define     BIT17                   (0x1<<17ul)
#define     BIT18                   (0x1<<18ul)
#define     BIT19                   (0x1<<19ul)
#define     BIT20                   (0x1<<20ul)
#define     BIT21                   (0x1<<21ul)
#define     BIT22                   (0x1<<22ul)
#define     BIT23                   (0x1<<23ul)
#define     BIT24                   (0x1<<24ul)
#define     BIT25                   (0x1<<25ul)
#define     BIT26                   (0x1<<26ul)
#define     BIT27                   (0x1<<27ul)
#define     BIT28                   (0x1<<28ul)
#define     BIT29                   (0x1<<29ul)
#define     BIT30                   (0x1<<30ul)
#define     BIT31                   (0x1<<31ul)

#define     S256B                    0x00000100
#define     S512B                    0x00000200
#define     S1KB                     0x00000400
#define     S2KB                     0x00000800
#define     S4KB                     0x00001000
#define     S8KB                     0x00002000
#define     S16KB                    0x00004000
#define     S32KB                    0x00008000
#define     S64KB                    0x00010000
#define     S128KB                   0x00020000
#define     S256KB                   0x00040000
#define     S512KB                   0x00080000
#define     S1MB                     0x00100000
#define     S2MB                     0x00200000
#define     S4MB                     0x00400000

#define     M3_SRAM_BASE            0x02000000
#define     SM0_BASE                0x04e60000
#define     SM1_BASE                0x04ee0000
#define     SM2_BASE                0x04f60000
#define     SM3_BASE                0x04fe0000
#define     SM4_BASE                0x047d0000
#define     SM5_BASE                0x020c0000
#define     DDR_BASE                0x10000000
#define     M3_SRAM_SIZE            S32KB
#define     SM0_SIZE                S512KB
#define     SM1_SIZE                S512KB
#define     SM2_SIZE                S512KB
#define     SM3_SIZE                S512KB
#define     SM4_SIZE                S16KB
#define     SM5_SIZE                S64KB



#endif  /* End of __IO_UCP_H */
