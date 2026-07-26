/* func_02003284 -- arm the alarm timer for an absolute 64-bit tick.
 *
 * Timer 0 counts the low 16 bits in hardware; the remaining 48 live in software at
 * data_02044664 (+8 mid, +0xc high) and are counted down by the timer-0 interrupt, which
 * this function acknowledges in REG_IF before re-arming. +4 is the "armed" flag.
 *
 * Two details carry the match. The mask in `(u16)(nTick & 0xffff)` must be applied to
 * the 64-bit value, not to a u32 cast of it: masking a u32 is redundant in front of a
 * 16-bit store and mwcc folds it away, costing the `rsb`/`and` pair, whereas the 64-bit
 * mask survives. And both timer registers come off ONE pool word at 0x04000102 -- mwcc
 * materialises the address of the register the source writes FIRST (the control word)
 * and reaches the reload counter at -2, which is why the control write has to come
 * before the counter write for the addresses to collapse. */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef struct OsAlarmState {
    u8  pad_00[4];
    u32 bArmed;
    u32 nTickMid;
    u32 nTickHigh;
} OsAlarmState;

extern OsAlarmState data_02044664;

extern int  OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

#define REG_IF       (*(volatile u32 *)0x04000214)
#define REG_TM0CNT_H (*(volatile u16 *)0x04000102)
#define REG_TM0CNT_L (*(volatile u16 *)0x04000100)

void func_02003284(u64 nTick)
{
    int state = OS_DisableInterrupts();

    REG_IF = 8;
    data_02044664.bArmed = 1;
    data_02044664.nTickMid = (u32)(nTick >> 16);
    data_02044664.nTickHigh = (u32)(nTick >> 48);
    REG_TM0CNT_H = 0;
    REG_TM0CNT_L = (u16)(nTick & 0xffff);
    REG_TM0CNT_H = 0xc1;
    OS_RestoreInterrupts(state);
}
