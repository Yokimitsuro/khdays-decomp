extern int func_ov107_020cab14();
extern int VEC_Subtract();
extern int func_01ff8d18();
extern int func_020050b4();

typedef struct { int x, y, z; } Vec3;

typedef struct {
    char pad0[0x80];
    int v80;
    char pad84[0x10c];
    Vec3 v190;
} P3bc;

typedef struct {
    char pad0[0xb0];
    Vec3 vb0;
    char padbc[0x10b];
    unsigned char b1c7;
    char pad1c8[0x1f4];
    P3bc *p3bc;
    char pad3c0[0xe0];
    int v4a0;
} Obj;

typedef struct {
    Obj *obj;
    char pad4[0x40];
    int v44;
} Wrap;

typedef struct {
    char pad0[4];
    Wrap *wrap;
} Param;

int func_ov249_020d10b4(Param *param)
{
    Wrap *wrap;
    Obj *obj;
    P3bc *p3bc;
    int diff;
    Vec3 local;

    wrap = param->wrap;
    obj = wrap->obj;
    p3bc = obj->p3bc;
    if (p3bc == 0) {
        p3bc = (P3bc *)func_ov107_020cab14(obj, 0);
        obj = wrap->obj;
        obj->p3bc = p3bc;
        obj = wrap->obj;
        p3bc = obj->p3bc;
        if (p3bc == 0) {
            obj->b1c7 = 2;
            return -1;
        }
    }

    VEC_Subtract(&p3bc->v190, &obj->vb0, &local);
    diff = func_01ff8d18(&local, &local);
    obj = wrap->obj;
    diff = diff - (obj->v4a0 + obj->p3bc->v80);
    if (diff < 0) {
        diff = 0;
    }
    wrap->v44 = func_020050b4(local.x, local.z);
    return diff;
}
