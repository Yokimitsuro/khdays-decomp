/* SndSwapSlotReleaseChannel: under an interrupt lock, temporarily swap the active
 * sound slot to `slot`, and if `owner` matches the channel currently mapped to
 * `chan`, release it (func_0201b808(chan, 0)); then restore the swap and IRQs.
 * func_0201b3c0 = SND_SetActiveSlotSwap. */
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int old);
extern int SND_SetActiveSlotSwap(int slot);
extern int func_0201b7e0(unsigned int a);
extern void func_0201b808(unsigned int a, int b);

void func_0201c254(int param_1, int param_2, unsigned int param_3)
{
    int oldSwap;
    int oldIrq;

    if (param_2 == 0) {
        return;
    }
    oldIrq = OS_DisableInterrupts();
    oldSwap = SND_SetActiveSlotSwap(param_2);
    if (param_1 == func_0201b7e0(param_3)) {
        func_0201b808(param_3, 0);
    }
    SND_SetActiveSlotSwap(oldSwap);
    OS_RestoreInterrupts(oldIrq);
}
