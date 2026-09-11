typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int obj, int flag, Vec3 v);
extern void func_ov107_020c5af8(int obj, int b, int c, void *d);
extern void func_ov107_020c5c54(int node, Vec3 *pos);
extern void func_0203c634(int obj, int idx, int cb);
extern Vec3 data_02041dc8;

void func_ov298_020d53c4(int *this)
{
    int node = this[1];
    struct {
        int field_00;
        Vec3 pos;
    } dest;

    dest.field_00 = 0;

    func_ov107_020c0b90(*(int *)node, 0, **(Vec3 **)(node + 8));
    func_ov107_020c5af8(*(int *)node, 0x177, 4, (void *)(*(Vec3 **)(node + 8)));

    dest.pos.x = 0;
    dest.pos.y = (int)0xffffda42;
    dest.pos.z = 0x2d077;
    *(int *)(node + 0x84) = 1;

    *(Vec3 *)(node + 0x10) = data_02041dc8;
    func_ov107_020c5c54(*(int *)node, &dest.pos);

    *(int *)(node + 0x38) = 0;
    *(signed char *)(*(int *)node + 0x1c7) = 2;
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), 0);
}
