/* func_ov203_020d5760: recoil entry of the ov202 enemy (x2), variant of the matched ov132 sibling (+0x60 bit 6 cleared before the +0x3e0 bit-0 clear; the zero vector is a const extern so its load hoists above the stores). */
struct v3 { int a, b, c; };
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
struct pair { unsigned short a, b; };

extern unsigned short data_ov203_020d67e4[];
extern const struct v3 data_02041dc8;
extern void func_02031384();
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov203_020d5840(void);

void func_ov203_020d5760(char *obj) {
    int *state = *(int **)(obj + 4);
    struct pair buf;
    if (*(unsigned char *)state[0x11] != 0) return;
    buf = *(struct pair *)&data_ov203_020d67e4[2];
    buf.a = *(unsigned short *)(*state + 2);
    func_02031384(4, &buf, 4);
    func_ov107_020c9264(*state, 7, 1);
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x40;
    *(int *)(*state + 0x3e0) &= ~1;
    *(struct v3 *)((char *)state + 0x20) = data_02041dc8;
    state[0x15] = 0;
    state[0xb] = 0;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov203_020d5840);
}
