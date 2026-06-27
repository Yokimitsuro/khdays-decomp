extern int VEC_Add();

typedef struct { int x, y, z; } Vec3;

typedef struct {
    char pad0[0x10];
    Vec3 v10;
    Vec3 v1c;
    Vec3 v28;
    int f34;
    int f38;
    int f3c;
    int f40;
    char pad44[0x10];
    Vec3 v54;
} Obj;

typedef struct {
    char pad0[0x64];
    Vec3 v64;
} Other;

void func_01ffeba0(Obj *obj, Other *other)
{
    VEC_Add(&obj->v28, &other->v64, &obj->v10);
    VEC_Add(&obj->v10, &obj->v1c, &obj->v54);

    if (obj->v10.x < obj->v54.x) {
        obj->f34 = obj->v10.x;
        obj->f3c = obj->v54.x;
    } else {
        obj->f34 = obj->v54.x;
        obj->f3c = obj->v10.x;
    }

    if (obj->v10.z < obj->v54.z) {
        obj->f38 = obj->v10.z;
        obj->f40 = obj->v54.z;
    } else {
        obj->f38 = obj->v54.z;
        obj->f40 = obj->v10.z;
    }
}
