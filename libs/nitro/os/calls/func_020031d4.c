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
typedef volatile unsigned long long vu64;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define REG_TM0CNT_L_OFFSET 0x100
#define REG_TM0CNT_L_ADDR (HW_REG_BASE + REG_TM0CNT_L_OFFSET)
#define REG_IF_OFFSET 0x214
#define REG_IF_ADDR (HW_REG_BASE + REG_IF_OFFSET)
#define reg_OS_IF (*( REGType32v *) REG_IF_ADDR)
#define REG_OS_IE_T0_SHIFT 3
#define HW_IOREG 0x04000000
#define HW_REG_BASE HW_IOREG        // alias
#define OS_IE_TIMER0 (1UL << REG_OS_IE_T0_SHIFT)
#define OSi_TICK_TIMER OS_TIMER_0
#define OSi_TICK_IE_TIMER OS_IE_TIMER0

typedef u16 REGType16;
typedef vu32 REGType32v;
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
typedef enum {
    OS_TIMER_0 = 0,
    OS_TIMER_1 = 1,
    OS_TIMER_2 = 2,
    OS_TIMER_3 = 3
} OSTimer;
typedef u64 OSTick;

/* khdays: shared-bss */
BOOL OSi_NeedResetTimer = 0;   /* OSi_NeedResetTimer */
u16 data_02044664 = 0;   /* data_02044664 */
vu64 data_0204466c = 0;   /* data_0204466c */



/* func_020031d4 -- NitroSDK os_tick.c: OS_GetTick. */
OSTick func_020031d4 (void)
{
    vu16 countL;
    vu64 countH;

    OSIntrMode prev = OS_DisableInterrupts();

    countL = *(REGType16 *)((u32)REG_TM0CNT_L_ADDR + OSi_TICK_TIMER * 4);
    countH = data_0204466c & 0xffffffffffffULL;

    if (reg_OS_IF & OSi_TICK_IE_TIMER && !(countL & 0x8000)) {
        countH++;
    }

    (void)OS_RestoreInterrupts(prev);

    return (countH << 16) | countL;
}
