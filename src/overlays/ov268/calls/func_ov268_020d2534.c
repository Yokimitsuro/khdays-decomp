/* Charge tick of the ov268 enemy (twin of ov206 cee10 with its state moved): until the +0x49 flag is
 * set the +0x2c clock runs up at the frame rate and, on reaching 0x99a, reaction 0x15f mode 4 fires at
 * the owner's +0x3c4 bone (+4) and the flag latches. Once the +4 rig is idle, bit 0 of the owner's
 * +0x1ae clears, flag 0 of the +0x3b8 and +0x3b4 rigs is set, pose 6 loops, the clock resets and brain
 * slot +0x20 runs 020d2638. */
extern void func_ov107_020c5af8(int owner, int a, int b, int c);
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov268_020d2638(void);
struct b8 { unsigned int f:8; };
void func_ov268_020d2534(int self) {
    int obj = *(int *)(self + 4);
    if (*(unsigned char *)(obj + 0x49) == 0) {
        int f24 = *(int *)(obj + 0x2c) + *(int *)(*(int *)self + 0x2c);
        *(int *)(obj + 0x2c) = f24;
        if (f24 >= 0x99a) {
            func_ov107_020c5af8(*(int *)obj, 0x15f, 4, *(int *)(*(int *)obj + 0x3c4) + 4);
            *(unsigned char *)(obj + 0x49) = 1;
        }
    }
    if (*(unsigned char *)(*(int *)(obj + 4) + 0xad) != 0) {
        return;
    }
    *(unsigned short *)(*(int *)obj + 0x1ae) &= ~1;
    ((struct b8 *)(*(int *)(*(int *)obj + 0x3b8) + 8))->f |= 1;
    ((struct b8 *)(*(int *)(*(int *)obj + 0x3b4) + 8))->f |= 1;
    func_ov107_020c9264(*(int *)obj, 6, 1);
    *(int *)(obj + 0x2c) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov268_020d2638);
}
