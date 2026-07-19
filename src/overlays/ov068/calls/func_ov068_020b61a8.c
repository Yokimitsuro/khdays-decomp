extern int func_ov022_0209fe20(int self, void *out);
extern void func_0202af1c(int a);
extern int func_02030788(void);

typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;

int func_ov068_020b61a8(int self) {
    int v[3];
    int r;
    func_ov022_0209fe20(self, v);
    *(int *)(self + 0x58) = v[1];
    r = (*(int (**)(int))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (((Flags *)(self + 0x694))->b1) {
        int *p;
        *(unsigned long long *)self |= 0x2000000000000ULL;
        p = *(int **)(self + 0x20);
        if ((*p & 0x20) == 0) {
            func_0202af1c((int)p + 4);
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)((char *)self + 0x464) |= 2;
        }
    }
    return 0;
}
