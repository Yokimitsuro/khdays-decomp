extern int func_02030788(void);
extern void func_ov022_0208a6b0(int obj);
extern int func_020357f4(int kind, int idx);
extern void func_020357c8(int kind, int idx, int v);
extern void *data_ov022_020b2a20[];
extern int data_0204be04;

typedef void (*Handler0208a6d0)(int obj);

void func_ov022_0208a6d0(int obj) {
    int e = *(int *)(obj + 0x58);
    int t = func_02030788();
    int r;
    if (*(unsigned char *)(e + 8) == t) {
        *(unsigned long long *)e |= 0x100000LL;
    }
    *(unsigned short *)(*(int *)(obj + *(int *)(obj + 0xc) * 4 + 0x18) + 0x114) = 0xffff;
    ((Handler0208a6d0)data_ov022_020b2a20[*(int *)(obj + 0xc)])(obj);
    func_ov022_0208a6b0(obj);
    *(unsigned short *)obj |= 0x140;
    *(unsigned short *)obj &= ~0x80;
    r = func_020357f4(*(unsigned char *)(e + 9), *(int *)(obj + 0xc));
    if (*(unsigned char *)&data_0204be04 != 0) return;
    func_020357c8(*(unsigned char *)(e + 9), *(int *)(obj + 0xc), r - 1);
}
