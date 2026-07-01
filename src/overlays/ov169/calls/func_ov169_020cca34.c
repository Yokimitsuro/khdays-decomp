extern int VEC_Subtract();
extern int func_01ff8d18();
extern int func_0203cd7c();
extern int func_0202ea48();

extern int data_02042264;

typedef struct { int a, b, c; } Vec3;

typedef struct {
    char pad74[0x74];
    char sub[0xc];
    int v80;
} Node;

typedef struct {
    Node *n0;
    char pad4[8];
    Node *n0c;
    char padc[0x64];
    char sub[0xc];
} Inner;

typedef struct {
    int field0;
    Inner *inner;
} Obj;

int func_ov169_020cca34(Obj *obj, Vec3 *out)
{
    Node *na;
    Node *nb;
    Inner *inner;
    int diff;
    char localB[0x24];
    Vec3 localA;

    inner = obj->inner;
    nb = inner->n0c;
    if (nb == 0) {
        return 0;
    }
    na = inner->n0;

    VEC_Subtract(nb->sub, na->sub, &localA);
    diff = func_01ff8d18(&localA, &localA) - nb->v80 - na->v80;
    if (diff < 0) {
        diff = 0;
    }
    func_0203cd7c(localB, nb->sub, na->sub, &data_02042264);
    func_0202ea48(inner->sub, localB);
    if (out != 0) {
        *out = localA;
    }
    return diff;
}
