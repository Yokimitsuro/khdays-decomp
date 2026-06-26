extern int func_ov107_020c6980();

struct s44 {
    int a[11];
};

struct s16 {
    int a[4];
};

struct obj {
    char pad0[0x64];
    struct s16 src2;
    char pad1[0xa0 - 0x64 - 0x10];
    struct s44 src1;
    char pad2[0x388 - 0xa0 - 0x2c];
    char **p388;
};

void func_ov224_020d4274(struct obj *o)
{
    func_ov107_020c6980(o);
    *(struct s44 *)(*(o->p388) + 0x10) = o->src1;
    *(struct s16 *)(*(o->p388) + 0x58) = o->src2;
    *(struct s16 *)(*(o->p388) + 0x68) = o->src2;
}
