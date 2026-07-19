extern void func_ov102_020bb470(void);
extern int func_ov022_020ad114(int self);
extern int func_ov022_020ad0c0(int self);
extern void VEC_Subtract(int a, int b, void *out);
extern int VEC_Mag(void *v);
extern void func_01ff8d18(void *a, void *b);
extern int FX_Atan2(int y, int x);

typedef struct { int x, y, z; } Vec3;

void *func_ov102_020bac68(int self, int req) {
    Vec3 d;
    void *cb = 0;
    char *blk = (char *)(self + 0xc50);
    int *flag = (int *)(blk + 0x2000);
    if (req == 0x21) {
        cb = (void *)&func_ov102_020bb470;
        if (*flag != 0) {
            (*(void (**)(int, int))(self + 0x664))(self, 0x31);
        } else {
            (*(void (**)(int, int))(self + 0x664))(self, 0x30);
        }
        if (func_ov022_020ad114(self) != 0) {
            VEC_Subtract(func_ov022_020ad0c0(self), self + 0x8c + 0x400, &d);
            if (VEC_Mag(&d) != 0) {
                func_01ff8d18(&d, &d);
            }
            {
                unsigned short ang = (unsigned short)FX_Atan2(-d.x, -d.z);
                int *n = *(int **)(self + 0x20);
                if ((*n & 0x20) == 0) {
                    *(unsigned short *)((char *)n + 0x80) = ang + 0x8000;
                    *(unsigned short *)((char *)n + 4) |= 0x20;
                }
            }
        }
    }
    return cb;
}
