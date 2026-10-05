/* OS_SetTick (NitroSDK os_tick.c) -- set the system tick to nTick.
 *
 * Timer 0 counts the tick's low 16 bits; the 48 above them are OSi_TickCounter (data_02044664
 * +8, a u64, which OS_GetTick reads), counted up by the timer-0 interrupt, acknowledged here
 * in REG_IF first. OSi_NeedResetTimer (+4) has OSi_CountUpTick put timer 0's reload back to 0
 * at its next overflow.
 *
 * Two details carry the match. The mask in `(u16)(nTick & 0xffff)` must be applied to
 * the 64-bit value, not to a u32 cast of it: masking a u32 is redundant in front of a
 * 16-bit store and mwcc folds it away, costing the `rsb`/`and` pair, whereas the 64-bit
 * mask survives. And both timer registers come off ONE pool word at 0x04000102 -- mwcc
 * materialises the address of the register the source writes FIRST (the control word)
 * and reaches the reload counter at -2, which is why the control write has to come
 * before the counter write for the addresses to collapse. */

#include "nitro/types.h"
#include "nitro/hw.h"

typedef struct OsAlarmState {
    u8  pad_00[4];
    u32 bNeedResetTimer;    /* OSi_NeedResetTimer */
    u32 nTickCounterLo;     /* OSi_TickCounter, low word */
    u32 nTickCounterHi;     /* OSi_TickCounter, high word */
} OsAlarmState;

extern OsAlarmState data_02044664;

extern int  OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

void OS_SetTick(u64 nTick)
{
    int state = OS_DisableInterrupts();

    REG_IF = 8;
    data_02044664.bNeedResetTimer = 1;
    data_02044664.nTickCounterLo = (u32)(nTick >> 16);
    data_02044664.nTickCounterHi = (u32)(nTick >> 48);
    REG_TM0CNT_H = 0;
    REG_TM0CNT_L = (u16)(nTick & 0xffff);
    REG_TM0CNT_H = 0xc1;
    OS_RestoreInterrupts(state);
}
