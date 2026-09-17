typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define HW_IOREG 0x04000000
#define HW_REG_BASE HW_IOREG        // alias
#define REG_BG0CNT_OFFSET 0x008
#define REG_BG1CNT_OFFSET 0x00a
#define REG_G2_BG0CNT_BGPLTTSLOT_MASK 0x2000
#define REG_DB_BG0CNT_OFFSET 0x1008
#define REG_DB_BG1CNT_OFFSET 0x100a

typedef enum NNSG2dBGSelect {
    NNS_G2D_BGSELECT_MAIN0,
    NNS_G2D_BGSELECT_MAIN1,
    NNS_G2D_BGSELECT_MAIN2,
    NNS_G2D_BGSELECT_MAIN3,
    NNS_G2D_BGSELECT_SUB0,
    NNS_G2D_BGSELECT_SUB1,
    NNS_G2D_BGSELECT_SUB2,
    NNS_G2D_BGSELECT_SUB3,
    NNS_G2D_BGSELECT_NUM
} NNSG2dBGSelect;
typedef enum NNSG2dBGExtPlttSlot {
    NNS_G2D_BGEXTPLTTSLOT_MAIN0,
    NNS_G2D_BGEXTPLTTSLOT_MAIN1,
    NNS_G2D_BGEXTPLTTSLOT_MAIN2,
    NNS_G2D_BGEXTPLTTSLOT_MAIN3,
    NNS_G2D_BGEXTPLTTSLOT_SUB0,
    NNS_G2D_BGEXTPLTTSLOT_SUB1,
    NNS_G2D_BGEXTPLTTSLOT_SUB2,
    NNS_G2D_BGEXTPLTTSLOT_SUB3
} NNSG2dBGExtPlttSlot;

/* func_02012b6c -- NitroSystem g2d_Screen.c: GetBGExtPlttSlot. */
NNSG2dBGExtPlttSlot func_02012b6c (NNSG2dBGSelect bg)
{
    static const u16 addrTable[] = {
        REG_BG0CNT_OFFSET,
        REG_BG1CNT_OFFSET,
        0,
        0,
        REG_DB_BG0CNT_OFFSET,
        REG_DB_BG1CNT_OFFSET,
        0,
        0
    };
    u32 addr;
    NNSG2dBGExtPlttSlot slot = (NNSG2dBGExtPlttSlot)bg;

    addr = addrTable[bg];

    if (addr != 0) {
        addr += HW_REG_BASE;

        if ((*(u16 *)addr & REG_G2_BG0CNT_BGPLTTSLOT_MASK) != 0) {
            slot += 2;
        }
    }

    return slot;
}
