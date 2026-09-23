/* Placement hook of the ov227 enemy (installed in its +0x10 slot; the ov267 d4664 hook with the
 * position passed by value): the enemy is placed at the given point (020c5c54), its +0xc hook runs
 * while bit 1 of +0x40 is set, the +0x384 rig is reset (0203c7ac) and, while the chain is out
 * (+0x50 == 1), the +0x214 part follows (func_ov227_020d40b0). */
typedef struct { int x, y, z; } Vec3;
typedef struct { int b0 : 1, b1 : 1; } Bits32;

extern void func_ov107_020c5c54(char *obj, Vec3 *pos);
extern void func_0203c7ac(int a, int b);
extern void func_ov227_020d40b0(int part);

void func_ov227_020d3da0(char *obj, Vec3 pos)
{
    func_ov107_020c5c54(obj, &pos);
    if (((Bits32 *)(obj + 0x40))->b1 != 0 && *(void (**)(char *, int))(obj + 0xc) != 0) {
        (*(void (**)(char *, int))(obj + 0xc))(obj, 0);
    }
    func_0203c7ac(*(int *)(obj + 0x384), 0);
    if (*(int *)(obj + 0x50) == 1) {
        func_ov227_020d40b0(*(int *)(obj + 0x214));
    }
}
