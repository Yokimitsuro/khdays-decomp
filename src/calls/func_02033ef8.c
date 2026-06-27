extern void VEC_CrossProduct();
extern void func_01ff8d18();
extern char *data_0204c234;

typedef struct { int x, y, z; } Vec3;

void func_02033ef8(Vec3 *src, Vec3 *a, Vec3 *b)
{
    char *base;
    Vec3 local;

    base = data_0204c234;
    VEC_CrossProduct(a, b, &local);
    func_01ff8d18(&local, base + 0xb44d8);
    *(Vec3 *)(base + 0xb44cc) = *src;
}
