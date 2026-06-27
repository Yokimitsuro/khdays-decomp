extern int GFXi_EnqueueCommand(int a, int b, int c, int d);

typedef struct {
    char _pad[8];
    int f8;    /* +8 */
    int fc;    /* +0xc */
} BG;

int func_0202429c(int idx, BG *p) {
    if (idx <= 3) return GFXi_EnqueueCommand(0xf, 0, p->fc, p->f8);
    return GFXi_EnqueueCommand(0x1f, 0, p->fc, p->f8);
}
