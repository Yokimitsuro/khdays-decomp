extern void func_02011ecc(void *p, int v);

void func_02011f2c(void *p, int v)
{
    *(int *)((char *)p + 0x1c) = v;
    func_02011ecc(p, v);
}
