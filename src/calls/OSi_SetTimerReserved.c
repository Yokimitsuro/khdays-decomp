/* OSi_SetTimerReserved: sets bit `n` in the reserved-timer mask and returns the new mask. */

extern unsigned short data_02044660;

int OSi_SetTimerReserved(int n) {
    int v = data_02044660 | (1 << n);
    data_02044660 = (unsigned short)v;
    return v;
}
