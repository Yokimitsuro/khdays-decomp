struct S {
    int f0;
    int f4;
};

void func_ov031_020b3a20(int *p, int v)
{
    p[1] = 3;
    p[0x44] = v;
    p[0x45] = 0;
}
