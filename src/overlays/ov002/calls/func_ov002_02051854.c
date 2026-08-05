/*
 * func_ov002_02051854 - arm a one-shot subsystem flag once its preconditions hold (ARM).
 *
 * Reads the subsystem state at *(int*)&data_ov002_0207f600. Does nothing if it is already active
 * (state word bit 2 set, or the +0x40 latch already non-zero), or if the required-ready bits
 * (bit 0 and bit 4) are not both set. When those pass it sets the +0x40 latch to 1, first running
 * the deferred-init call func_0201e374(0) unless bit 3 indicates init already happened. The base
 * pointer is re-read after the call because it may have moved.
 */
extern int data_ov002_0207f600;
extern void func_0201e374(int a);

void func_ov002_02051854(void)
{
    int base = *(int *)&data_ov002_0207f600;
    int flags = *(int *)base;
    if ((flags & 4) || *(int *)(base + 0x40) != 0) return;
    if ((flags & 1) == 0) return;
    if ((flags & 0x10) == 0) return;
    if ((flags & 8) == 0) {
        func_0201e374(0);
    }
    *(int *)(*(int *)&data_ov002_0207f600 + 0x40) = 1;
}
