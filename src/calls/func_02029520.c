extern void func_01ffd0e8();
extern void VEC_Subtract();
extern void func_01ffcfd0();
extern int func_01ffcf0c();

struct Vec3 { int x; int y; int z; };

void func_02029520(char *p1, char *p2, char *p3)
{
    struct Vec3 va;
    struct Vec3 vb;

    func_01ffd0e8(*(int *)(p2 + 0x78), p2 + 0x1c, p2 + 0x10, &va);
    VEC_Subtract(&va, p1 + 0x2c, &vb);
    vb.y = vb.y - *(int *)(p1 + 0x3c);
    func_01ffcfd0(&vb, p3 + 0x14);
    *(int *)(p3 + 0x1c) = func_01ffcf0c(&va, p3 + 0x14);
}
