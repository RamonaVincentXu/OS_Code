#ifndef __BOOT_ASM_H__
#define __BOOT_ASM_H__

/* Assembler macros to create x86 segments */

/* Normal segment */
// 定义了一个空段描述符 
#define SEG_NULLASM                                             \
    .word 0, 0;                                                 \
    .byte 0, 0, 0, 0


//  以type,base,lim为参数定义一个段描述符, 其中的0xC0=(1100)2, 其
//  中的第一个1对应于段描述符中的G位,置1表示段界限以4KB为单位
//  第二个1对应于段描述符的D位,置1表示这是一个保护模式下的段描述符
//  具体的关于段描述符的格式定义在mmu.h中 

// The 0xC0 means the limit is in 4096-byte units
// and (for executable segments) 32-bit mode.


//lim右移12位后（缩小）和0xffff按位与，保留低16位；如此类比
#define SEG_ASM(type,base,lim)                                  \
    .word (((lim) >> 12) & 0xffff), ((base) & 0xffff);          \
    .byte (((base) >> 16) & 0xff), (0x90 | (type)),             \
        (0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)


/* Application segment type bits */
#define STA_X       0x8     // Executable segment
#define STA_E       0x4     // Expand down (non-executable segments)
#define STA_C       0x4     // Conforming code segment (executable only)
#define STA_W       0x2     // Writeable (non-executable segments)
#define STA_R       0x2     // Readable (executable segments)
#define STA_A       0x1     // Accessed

#endif /* !__BOOT_ASM_H__ */

