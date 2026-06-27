extern int GFXi_EnqueueCommand(int a, int b, int c, int d);

typedef struct {
    char _pad[8];
    int f8;    /* +8 */
    int fc;    /* +0xc */
} BG;

int func_02024264(int idx, BG *p) {
    int sh = idx << 13;
    if (idx <= 3) return GFXi_EnqueueCommand(0x11, sh, p->fc, p->f8);
    return GFXi_EnqueueCommand(0x21, sh - 0x8000, p->fc, p->f8);
}
