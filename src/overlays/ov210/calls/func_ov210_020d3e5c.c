/*
 * func_ov210_020d3e5c -- x3 (ov210/...). Tick the sub-emitter and re-aim its spawn cone.
 * If a child scene exists at +0x3c, tick it (0203c4a8); tick the emitter (020c41e4). Skip the rest
 * unless one of the three aim words +0x124/+0x128/+0x12c is set. Build the aim matrix into `m` via
 * 0202ed60(&m, &data_02042264, self+0x124). Take the muzzle offset (self+0x74..0x7c), pull its Y in by
 * the recoil +0x13c, and drive the emitter node at *(self+0x190)+0x30: set its cone via
 * 0203ca14(node, x, y+0x100, z), its length via 0203ca9c(node, 0x1000), and its orientation via
 * 0203c9d0(node, &m).
 */
struct vec3 { int x, y, z; };
struct xform4 { int w[4]; };

extern void func_0203c4a8(int scene, unsigned tick);
extern void func_ov107_020c41e4(int self, unsigned tick);
extern void func_0202ed60(struct xform4 *out, void *basis, int *vec);
extern void func_0203ca14(int node, int x, int y, int z);
extern void func_0203ca9c(int node, int len);
extern void func_0203c9d0(int node, struct xform4 *m);
extern int data_02042264;

void func_ov210_020d3e5c(int self, unsigned tick) {
    if (*(int *)(self + 0x3c) != 0) {
        func_0203c4a8(*(int *)(self + 0x3c), tick);
    }
    func_ov107_020c41e4(self, tick);
    if (*(int *)(self + 0x124) == 0 && *(int *)(self + 0x128) == 0 && *(int *)(self + 0x12c) == 0) {
        return;
    }
    {
        int recoil = *(int *)(self + 0x13c);
        struct vec3 s;
        struct xform4 m;

        func_0202ed60(&m, &data_02042264, (int *)(self + 0x124));
        s = *(struct vec3 *)(self + 0x74);
        s.y -= recoil;
        func_0203ca14(*(int *)(self + 0x190) + 0x30, s.x, s.y + 0x100, s.z);
        func_0203ca9c(*(int *)(self + 0x190) + 0x30, 0x1000);
        func_0203c9d0(*(int *)(self + 0x190) + 0x30, &m);
    }
}
