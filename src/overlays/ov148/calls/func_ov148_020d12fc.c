extern int func_ov107_020cab14(int a, int b);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int *self, int idx, void *cb);
extern void func_ov148_020d13d4(void);

typedef struct { int x, y, z; } Vec3;
extern Vec3 data_02041dc8;
extern void func_ov107_020c0b90(int a, int b, Vec3 v, int d);

void func_ov148_020d12fc(int *self) {
    int *s = (int *)self[1];
    *(int *)(*s + 0x394) = func_ov107_020cab14(*s, 0);
    if (*(int *)(*s + 0x394) == 0) {
        *(signed char *)(*s + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
        return;
    }
    func_ov107_020c9264(*s, 6, 0);
    func_ov107_020c0b90(*s, 0, *(Vec3 *)(*s + 0x3d8), 0);
    func_ov107_020c0b90(*s, 2, data_02041dc8, 0);
    s[0x10] = 0;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), (void *)&func_ov148_020d13d4);
}
