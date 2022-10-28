#ifndef __BOOT_ASM_H__
#define __BOOT_ASM_H__

/* Assembler macros to create x86 segments */

/* Normal segment */
// ������һ���ն������� 
#define SEG_NULLASM                                             \
    .word 0, 0;                                                 \
    .byte 0, 0, 0, 0


//  ��type,base,limΪ��������һ����������, ���е�0xC0=(1100)2, ��
//  �еĵ�һ��1��Ӧ�ڶ��������е�Gλ,��1��ʾ�ν�����4KBΪ��λ
//  �ڶ���1��Ӧ�ڶ���������Dλ,��1��ʾ����һ������ģʽ�µĶ�������
//  ����Ĺ��ڶ��������ĸ�ʽ������mmu.h�� 

// The 0xC0 means the limit is in 4096-byte units
// and (for executable segments) 32-bit mode.


//lim����12λ����С����0xffff��λ�룬������16λ��������
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

