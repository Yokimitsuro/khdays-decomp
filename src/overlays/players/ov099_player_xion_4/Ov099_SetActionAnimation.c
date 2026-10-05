/* Drive the sub-object for the selected action: selector 0x22 plays animation 0x2f; selector 0x23
 * plays 0x30, sets the 0x39000 parameter and the 0x1000 field at +0x64, and -- when a target exists
 * -- turns the object to face it (FX_Atan2Idx of the normalised delta, minus half a turn) unless bit 5
 * of the node's flag word is already set. */

extern int func_ov022_020acf14();
extern int Ov022_ValidateTargetRef();
extern int func_ov022_020ad0c0();
extern int VEC_Subtract();
extern int VEC_Mag();
extern int VEC_Normalize();
extern int FX_Atan2Idx();

struct Obj {
    char pad0[0x20];
    void *off20;
    char pad24[0x64 - 0x24];
    unsigned short off64;
    char pad66[0x664 - 0x66];
    int (*method)();
};

struct Outer {
    char pad0[0xdb4];
    struct Obj *obj;
};

void Ov099_SetActionAnimation(struct Outer *outer, int sel)
{
    int local[3];
    struct Obj *obj = outer->obj;
    unsigned short *p;

    switch (sel) {
    case 0x22:
        obj->method(obj, 0x2f);
        return;
    case 0x23:
        break;
    default:
        return;
    }

    obj->method(obj, 0x30);
    func_ov022_020acf14(obj, 0x39000);
    obj->off64 = 0x1000;
    if (Ov022_ValidateTargetRef(obj) == 0) {
        return;
    }
    VEC_Subtract(func_ov022_020ad0c0(obj), (char *)obj + 0x8c + 0x400, local);
    if (VEC_Mag(local) != 0) {
        VEC_Normalize(local, local);
    }
    {
        unsigned short v = (unsigned short)FX_Atan2Idx(-local[0], -local[2]);
        p = (unsigned short *)obj->off20;
        if (*(int *)p & 0x20) {
            return;
        }
        p[0x80 / 2] = (unsigned short)(v + 0x8000);
        p[4 / 2] |= 0x20;
    }
}
