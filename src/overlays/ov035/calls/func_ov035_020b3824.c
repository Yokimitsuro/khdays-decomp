typedef struct { int x, y, z; } Vec3;

extern int func_ov022_02095554(unsigned int *obj);
extern int *func_01fff774(int node, int index, int value);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *dst);
extern int VEC_Mag(const Vec3 *v);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern int FX_Atan2(int x, int z);
extern int func_ov022_020ad114(char *self);
extern Vec3 *func_ov022_020ad0c0(char *self);
extern char *data_ov035_020b4ca0;
extern void func_ov035_020b44d4(void);
extern void func_ov035_020b482c(void);

void *func_ov035_020b3824(char *self, int msg) {
    char *blk = data_ov035_020b4ca0 + 0x2ca4;
    void *next = 0;
    Vec3 delta;
    unsigned short angle;
    int *node;

    switch (msg) {
    case 0x21:
        *(int *)(blk + 8) = 0;
        if (func_ov022_02095554((unsigned int *)(self + 0x22f8)) == 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
            node = *(int **)(self + 0x20);
            func_01fff774((int)(node + 1), 0, 0xf000);
            *(int *)(self + 0x7b0) = 0xf000;
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x32);
        }
        if (func_ov022_020ad114(self) != 0) {
            VEC_Subtract(func_ov022_020ad0c0(self), (const Vec3 *)(self + 0x48c), &delta);
            delta.y = 0;
            if (VEC_Mag(&delta) != 0)
                func_01ff8d18(&delta, &delta);
            angle = (unsigned short)FX_Atan2(-delta.x, -delta.z);
            node = *(int **)(self + 0x20);
            if ((node[0] & 0x20) == 0) {
                *(unsigned short *)((char *)node + 0x80) = angle + 0x8000;
                *(unsigned short *)((char *)node + 4) |= 0x20;
            }
        }
        next = (void *)&func_ov035_020b44d4;
        break;
    case 0x22:
        *(int *)(blk + 4) = 0;
        *(unsigned char *)(blk + 0xc) = 0;
        if (*(int *)blk == 0) {
            *(unsigned char *)(blk + 0xd) = *(int *)(blk + 8) == 2 ? 6 : 3;
            (*(void (**)(char *, int))(self + 0x664))(self, 0x30);
        } else {
            *(unsigned char *)(blk + 0xd) = 1;
            (*(void (**)(char *, int))(self + 0x664))(self, 0x31);
        }
        next = (void *)&func_ov035_020b482c;
        break;
    }
    return next;
}
