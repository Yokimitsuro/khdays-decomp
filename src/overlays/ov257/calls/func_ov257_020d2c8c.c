/* Helper tick of the ov257 enemy: unless its owner's kind (+0x1c6) is 0xc, the owner's four
 * sub-objects (+0x3a4 array) restart channel 2 (mode 2) and the slot hands over to
 * func_ov257_020d2cf8. The array is indexed as ((int *)owner)[0xe9 + i] (0xe9 * 4 == 0x3a4) so
 * mwcc emits the ROM's `add base,i<<2; ldr [.,#0x3a4]` addressing. */
extern int func_0203b9fc(int obj, int slot, int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov257_020d2cf8(int *node);

void func_ov257_020d2c8c(int *node)
{
    int *h = (int *)node[1];
    int i;

    if (*(signed char *)(h[0] + 0x1c6) == 0xc) {
        return;
    }
    for (i = 0; i < 4; i++) {
        func_0203b9fc(((int *)h[0])[0xe9 + i], 2, 2, 0);
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov257_020d2cf8);
}
