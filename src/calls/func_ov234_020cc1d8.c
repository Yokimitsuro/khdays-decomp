extern void func_0203c7e8(void *);
extern void func_ov107_020c68ec(void *);

struct S {
    char pad[0x384];
    void *f384;
    char pad2[0x3bc - 0x384 - 4];
    void *f3bc;
};

void func_ov234_020cc1d8(struct S *p)
{
    func_0203c7e8(p->f384);
    func_0203c7e8(p->f3bc);
    func_ov107_020c68ec(p);
}
