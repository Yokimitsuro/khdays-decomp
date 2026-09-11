typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned int f : 8; };

extern void func_0203c634(int self, int index, void *cb);
extern void func_ov299_020d4870(void);

void func_ov299_020d47dc(int self) {
    int *obj = *(int **)(self + 4);
    obj[9] = 0;
    *(Vec3 *)((char *)obj + 0x18) = *(Vec3 *)obj[1];
    obj[12] = 0;
    ((struct hw60 *)(*obj + 0x60))->hi &= ~0x80;
    ((struct b8 *)(*(int *)(*obj + 0x388) + 8))->f |= 1;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), (void *)&func_ov299_020d4870);
}
