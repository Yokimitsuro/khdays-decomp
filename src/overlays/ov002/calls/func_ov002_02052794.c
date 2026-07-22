/* Push both of the object's bitmap surfaces to the graphics queue: the one at
 * +0x3c with its own palette from +0x44, and the one at +0x40 with a fixed
 * 0x1e0-byte extent. Either may be absent. */
extern int func_02024a18(int handle);
extern int func_02024a28(int handle);
extern void GFXi_EnqueueCommand(int a, int b, int c, int d);

void func_ov002_02052794(char *self) {
    int surface = *(int *)(self + 0x3c);

    if (surface != 0) {
        GFXi_EnqueueCommand(func_02024a18(*(int *)(self + 0x10)),
                            *(int *)(self + 0x44),
                            *(int *)(surface + 0x14),
                            *(int *)(surface + 0x10));
    }

    surface = *(int *)(self + 0x40);
    if (surface == 0) {
        return;
    }

    GFXi_EnqueueCommand(func_02024a28(*(int *)(self + 0x10)), 0,
                        *(int *)(surface + 0xc), 0x1e0);
}
