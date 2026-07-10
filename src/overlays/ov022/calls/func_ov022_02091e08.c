extern int func_02030694(void);
extern void func_02031384(int a, void *buf, int c);

struct Buf02091e08 {
    unsigned char f01 : 2;
    unsigned char f23 : 2;
    unsigned char pad0 : 4;
    unsigned char g : 3;
    unsigned char pad1 : 5;
    signed char b2;
};

void func_ov022_02091e08(int *obj, unsigned char *param_2) {
    int e = obj[2];
    struct Buf02091e08 buf;
    if (func_02030694() == 0) return;
    if ((*(unsigned short *)(e + 0x1a) & 1) != 0) return;
    if ((*param_2 & 1) != 0) return;
    buf.f01 = 3;
    buf.f23 = *(unsigned char *)(e + 9);
    buf.g = (unsigned char)*obj;
    buf.b2 = *(signed char *)(param_2 + 1);
    func_02031384(9, &buf, 3);
}
