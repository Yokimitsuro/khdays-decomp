/*
 * Set (arg1!=0) or clear (arg1==0) bit 0x200 of a 64-bit flag word at arg0[0..1], after notifying
 * func_0202beb8 with a 0/1 flag. The operation is 64-bit: the low word gets `| 0x200` / `& ~0x200`,
 * and the high word the identity `| 0` / `& ~0` -- which is why the ROM keeps the otherwise-dead
 * arg0[1] store, and shares the `mvn` (~0) between the ~0x200 low mask and the ~0 high mask.
 */
extern void func_0202beb8(int index, int flag);

void func_ov022_0209a68c(unsigned int *arg0, int arg1) {
    if (arg1 != 0) {
        func_0202beb8((int)*(char *)((int)arg0 + 0x12f * 4), 0);
        *(unsigned long long *)arg0 |= 0x200;
        return;
    }
    func_0202beb8((int)*(char *)((int)arg0 + 0x12f * 4), 1);
    *(unsigned long long *)arg0 &= ~(unsigned long long)0x200;
}
