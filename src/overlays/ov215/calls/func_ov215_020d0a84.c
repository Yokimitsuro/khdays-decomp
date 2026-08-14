#pragma opt_dead_assignments off

typedef unsigned char u8;
typedef unsigned short u16;

struct Vecx32 { int x, y, z; };
struct Vec4 { int x, y, z, w; };

struct Ov264Hit {
    char pad000[2];
    u16 nKind;
    char pad004[0x70];
    struct Vec4 vOrigin74;
};

struct Ov264Owner {
    char pad000[0x74];
    struct Vec4 vOrigin74;
    char pad084[0x140];
    u8 bFlags1c4;
};

struct Ov264Node {
    struct Ov264Owner *pOwner;
    char pad004[0x0c];
    int nEffect10;
    struct Vecx32 vStep14;
    char pad020[0x51];
    u8 bHandled71;
};

struct Ov264Params {
    struct Vecx32 aim;
    struct Vecx32 v0c;
    struct Vecx32 v18;
    struct Vecx32 v24;
    int nSteps;
    int bFlag;
};

extern int func_ov107_020c8eb8(struct Ov264Owner *owner, void *query, void *out);
extern int func_ov107_020c8fd0(struct Ov264Owner *owner, struct Ov264Params *params, void *out);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern void func_01ffa724(int scale, void *v, void *d);
extern void VEC_Add(void *a, void *b, void *d);
extern int func_ov107_020ca918(struct Ov264Hit *hit, struct Ov264Owner *a, struct Ov264Owner *b,
                               u8 kind, void *push, int z);
extern void func_ov107_020c0b90(struct Ov264Owner *owner, int a, struct Vecx32 v, int b);
extern void func_ov107_020c5af8(struct Ov264Owner *owner, int a, int id, int p);
extern const struct Vecx32 data_02042258;

void func_ov215_020d0a84(struct Ov264Node *node, unsigned int kind, struct Ov264Params *params) {
    struct Vec4 origin;
    struct Ov264Hit *hits[4];
    struct Vecx32 push;
    struct Vecx32 step;
    int i;
    u8 bit;
    u8 seen;
    int n;
    int pushed;

    i = 1;
    seen = 1;
    bit = 0;
    seen = 0;
    origin = node->pOwner->vOrigin74;
    pushed = 0;
    if ((node->pOwner->bFlags1c4 & 2) != 0) {
        return;
    }
    if (params != 0) {
        n = func_ov107_020c8fd0(node->pOwner, params, hits);
    } else {
        n = func_ov107_020c8eb8(node->pOwner, &origin, hits);
    }
    i = 0;
    if (n > 0) {
        do {
            bit = (u8)(1 << hits[i]->nKind);
            seen |= bit;
            if ((node->bHandled71 & bit) == 0) {
                VEC_Subtract(&hits[i]->vOrigin74, &node->pOwner->vOrigin74, &push);
                func_01ff8d18(&push, &step);
                push.y = 0;
                if (func_01ff8d18(&push, &push) == 0) {
                    push = data_02042258;
                }
                func_01ffa724(0x800, &push, &push);
                if (func_ov107_020ca918(hits[i], node->pOwner, node->pOwner, kind, &push, 0) != 0) {
                    if (params != 0) {
                        VEC_Add(&hits[i]->vOrigin74, &push, &step);
                        func_ov107_020c0b90(node->pOwner, 1, step, 0);
                    } else {
                        func_01ffa724(origin.w, &step, &step);
                        VEC_Add(&step, &push, &step);
                        VEC_Add(&step, &origin, &step);
                        func_ov107_020c0b90(node->pOwner, 1, step, 0);
                    }
                    node->bHandled71 |= bit;
                    func_01ffa724(-0x1000, &push, &node->vStep14);
                    func_01ff8d18(&node->vStep14, &node->vStep14);
                    pushed = 1;
                }
            }
            i++;
        } while (i < n);
    }
    node->bHandled71 &= seen;
    if (pushed == 0) {
        return;
    }
    switch (kind) {
    case 1:
        func_ov107_020c5af8(node->pOwner, 0, 0x50, node->nEffect10);
        break;
    case 0:
    case 2:
        func_ov107_020c5af8(node->pOwner, 0, 0x52, node->nEffect10);
        break;
    }
}
