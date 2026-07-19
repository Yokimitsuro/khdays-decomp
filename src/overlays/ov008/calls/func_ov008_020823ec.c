extern char *data_ov008_02090fac;
extern int data_ov008_0208ff04[];
extern void GFXi_EnqueueCommand(int dst, int a, void *src, int size);

/* Flushes the dirty VRAM banks: one 0x600-byte DMA per set bit of the dirty mask. */
void func_ov008_020823ec(void) {
    char *st = *(char **)&data_ov008_02090fac;
    int i;
    char *src = st + 0xa8;
    for (i = 0; i < 7; i++) {
        if ((*(int *)(st + 0x2aac) & (1 << i)) != 0) {
            GFXi_EnqueueCommand(data_ov008_0208ff04[i], 0, src, 0x600);
        }
        src += 0x600;
    }
    *(int *)(st + 0x2aac) = 0;
}
