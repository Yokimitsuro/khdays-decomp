/* Start tick of the ov257 part helper: the owner's four sub-objects (+0x3a4 array) are shown (bit
 * 1 of +0x5c cleared) and restart channel 2, and slot 1 gets func_ov257_020d2c20. The array is
 * indexed as ((int *)owner)[0xe9 + i] (0xe9 * 4 == 0x3a4) for the ROM's addressing. */
extern int func_0203b9fc(int obj, int slot, int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov257_020d2c20(int *node);

void func_ov257_020d2b80(int *node)
{
    int *h = (int *)node[1];
    int i;

    for (i = 0; i < 4; i++) {
        *(int *)(((int *)h[0])[0xe9 + i] + 0x5c) &= ~2;
        func_0203b9fc(((int *)h[0])[0xe9 + i], 2, 0, 0);
    }
    func_0203c634(node, 1, (void *)func_ov257_020d2c20);
}
