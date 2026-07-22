/* Take a 0x30-byte channel block: register the frame callback on channel 9 the
 * first time anyone asks, count the reference, clear the block and stamp the two
 * caller words at +0 / +4. */
extern void func_02030cf8(int channel, void *handler);
extern void func_ov022_02090a50(void);
extern void MIi_CpuClearFast(unsigned int value, void *dest, unsigned int size);

extern int data_ov022_020b2ea8;

void func_ov022_020911f0(char *block, int a, int b) {
    if (data_ov022_020b2ea8 == 0) {
        func_02030cf8(9, (void *)func_ov022_02090a50);
    }

    data_ov022_020b2ea8++;

    MIi_CpuClearFast(0, block, 0x30);

    *(int *)block = a;
    *(int *)(block + 4) = b;
}
