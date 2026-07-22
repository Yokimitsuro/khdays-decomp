/* Spins briefly, then blocks on the V-blank interrupt. */
extern void WaitByLoop(int n);
extern void OS_WaitIrq(int clear, int mask);

void OS_WaitVBlankIntr(void) {
    int one = 1;
    WaitByLoop(one);
    OS_WaitIrq(one, one);
}
