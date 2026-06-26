extern int func_0202c2ac();
extern void func_01ffd0e8();
extern void func_01ff8b90();
extern int func_0202c268();

struct Vec3 { int x; int y; int z; };

void func_ov099_020bb708(struct Vec3 *out, char *p1, char *p2, int p3, int p4, int p5)
{
    int *r4;
    int *obj;
    struct Vec3 va;
    struct Vec3 vb;

    r4 = *(int **)(p1 + 0xdb4);

    if (p5 != 0) {
        obj = (int *)func_0202c2ac(*(unsigned char *)(p2 + 0x15c), p3, p4, 0x800, r4[8]);
        if (obj != 0 && obj[2] == 0) {
            func_01ffd0e8(obj[3] - 0x800, p4, p3, &va);
            *(char *)(p2 + 0x12c) = 5;
        } else {
            func_01ff8b90(p3, p4, &va);
        }
    } else {
        func_01ff8b90(p3, p4, &va);
    }

    va.y += 0x1000;
    vb.x = 0;
    vb.z = 0;
    vb.y = -0x2000;

    obj = (int *)func_0202c268(*(unsigned char *)(p2 + 0x15c), &va, &vb, r4[8]);
    if (obj != 0) {
        func_01ffd0e8(obj[3], &vb, &va, &va);
    } else {
        int lim = *(int *)(p2 + 0x138);
        if (va.y >= lim) {
            va.y = lim;
        } else {
            va.y = lim - 0x2000;
        }
    }

    *out = va;
}
