extern char *data_ov026_02091368;
extern int data_ov026_0209115c[];
extern void GFXi_EnqueueCommand(int dst, int a, void *src, int size);

/* Flushes the dirty VRAM banks: one 0x600-byte DMA per set bit of the dirty mask. */
void func_ov026_0208529c(void) {
    char *st = *(char **)&data_ov026_02091368;
    int i;
    char *src = st + 0xa8;
    for (i = 0; i < 7; i++) {
        if ((*(int *)(st + 0x2aac) & (1 << i)) != 0) {
            GFXi_EnqueueCommand(data_ov026_0209115c[i], 0, src, 0x600);
        }
        src += 0x600;
    }
    *(int *)(st + 0x2aac) = 0;
}
