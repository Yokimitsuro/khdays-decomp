/* func_020031d4 -- OS_GetTick: the current 64-bit tick count.
 *
 * Timer 0 counts the low 16 bits in hardware (TM0CNT_L); the upper 48 bits live in
 * software at data_02044664 (+8), advanced by the timer-0 overflow interrupt (see
 * func_02003284, which arms the same counter). If the overflow IRQ is already pending
 * but has not been serviced yet and the hardware counter has wrapped (top bit clear),
 * the software half is one behind, so it is bumped locally before composing the result.
 *
 * The counter is shared with the interrupt handler, hence volatile. The two snapshot
 * locals are also volatile: that is the SDK's own spelling of this function (vu16 /
 * vu64 locals), and it is what keeps both snapshots in the 12-byte stack frame with a
 * reload at every use instead of in callee-saved registers. Dropping any one of the
 * three qualifiers changes the emitted code.
 */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef struct OsTickState {
    u8  pad_00[8];
    volatile u64 nTickCounter;
} OsTickState;

extern OsTickState data_02044664;

extern int  OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

#define REG_IF       (*(volatile u32 *)0x04000214)
#define REG_TM0CNT_L (*(volatile u16 *)0x04000100)

u64 func_020031d4(void)
{
    int state = OS_DisableInterrupts();
    volatile u16 countL = REG_TM0CNT_L;
    volatile u64 countH = data_02044664.nTickCounter & 0x0000ffffffffffffULL;

    if ((REG_IF & 8) && !(countL & 0x8000)) {
        countH++;
    }

    OS_RestoreInterrupts(state);

    return (countH << 16) | countL;
}
