struct v3 { int a, b, c; };
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
struct pair { unsigned short a, b; };

extern unsigned short data_ov131_020cef6c[];
extern struct v3 data_02041dc8;
extern void func_02031384();
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov131_020cdff4(void);

void func_ov131_020cdf20(char *obj) {
    int *state = *(int **)(obj + 4);
    struct pair buf;
    if (*(unsigned char *)state[0x12] != 0) return;
    buf = *(struct pair *)&data_ov131_020cef6c[2];
    buf.a = *(unsigned short *)(*state + 2);
    func_02031384(4, &buf, 4);
    func_ov107_020c9264(*state, 7, 1);
    *(int *)(*state + 0x3cc) &= ~1;
    *(struct v3 *)((char *)state + 0x24) = data_02041dc8;
    state[0x16] = 0;
    state[0xc] = 0;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x40;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov131_020cdff4);
}
