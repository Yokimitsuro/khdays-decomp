/* Register the frame callback the first time anyone asks, count the reference,
 * and hand back a cleared six-word slot block. */
extern void func_02030cf8(int channel, void *handler);
extern void func_ov022_02091f8c(void);

extern int data_ov022_020b2eac;

void func_ov022_02092320(int *slots) {
    int i;

    if (data_ov022_020b2eac == 0) {
        func_02030cf8(0xa, (void *)func_ov022_02091f8c);
    }

    data_ov022_020b2eac++;

    for (i = 0; i < 6; i++) {
        *slots++ = 0;
    }
}
