extern void func_ov107_020c9264(int a, int b, int c);
typedef struct { int x, y, z; } Vec3;
extern void func_ov107_020c0b90(int a, int b, Vec3 v, int d);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov189_020d1aac(void);
extern Vec3 data_02041dc8;

void func_ov189_020d1a44(int self) {
    int *s = *(int **)(self + 4);
    func_ov107_020c9264(s[0], 0xb, 0);
    func_ov107_020c0b90(s[0], 5, data_02041dc8, 0);
    func_0203c634(self, *(signed char *)(self + 0x20), (void *)&func_ov189_020d1aac);
}
