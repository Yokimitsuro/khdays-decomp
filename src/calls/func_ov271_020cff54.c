extern int func_ov107_020c6980();

struct s44 {
    int a[11];
};

struct obj {
    char pad[0xa0];
    struct s44 src;
    char pad2[0x388 - 0xa0 - 0x2c];
    char *p388;
    char *p38c;
};

void func_ov271_020cff54(struct obj *o)
{
    func_ov107_020c6980(o);
    *(struct s44 *)(*(char **)(o->p388) + 0x10) = o->src;
    *(struct s44 *)(o->p38c + 0x10) = o->src;
}
