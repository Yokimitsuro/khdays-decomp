extern int func_0203c634();
extern int func_01ff9010();
extern int func_01ff93bc();

extern short data_0203d210[];

typedef struct {
    char pad[0x60];
    unsigned short f60 : 8;
    unsigned short f60h : 8;
} Inner;

typedef struct { int v[9]; } Local;

void func_ov248_020cdcb0(unsigned char *obj) {
    unsigned char *mid = *(unsigned char **)(obj + 4);
    int s4;
    Local local;

    if (!((*(Inner **)mid)->f60 & 0x80))
        (*(Inner **)mid)->f60h &= ~0x0E;

    *(int *)(mid + 0x4c) += *(int *)(*(unsigned char **)(obj + 0) + 0x2c);

    if (*(int *)(mid + 0x4c) >= 0x110)
        (*(Inner **)mid)->f60h &= ~0x80;

    if (*(unsigned char *)(*(unsigned char **)(mid + 4) + 0xad) == 0) {
        *(unsigned char *)((unsigned char *)*(Inner **)mid + 0x1c7) = 2;
        func_0203c634(obj, *(signed char *)(obj + 0x20), 0);
        return;
    }

    s4 = (int)(((long long)*(int *)(mid + 0x40) * 0x28be60db9391LL + (0x800LL << 32)) >> 32);
    s4 = (int)((unsigned)(s4 << 4) >> 16) >> 4;

    func_01ff9010(&local, data_0203d210[s4 * 2], data_0203d210[s4 * 2 + 1]);
    func_01ff93bc(*(unsigned char **)((unsigned char *)*(Inner **)mid + 0x490) + 0x2c, &local, mid + 0x10);
}
