/* Strike sweep of the ov221 enemy. The hit mask is the owner's +0x420 byte for mode 6 and the
 * state's +0x76 byte otherwise. With a query the entities come from ov107 c8fd0; without one a
 * sphere at the +0x3b0 body's +0x20 point is swept (ov107 c8eb8): radius 0x2400 for mode 7,
 * else 0x1380 pushed that far along the sine/cosine of the +0x50 heading. Every entity whose
 * kind bit is clear in the mask is pushed 1.0 along the flattened unit direction from the
 * owner's +0x74 (data_02042258 when degenerate) with the mode as the kind; on acceptance the
 * owner is sent mode 0 at the entity's +0x74 (with a query) or at the sphere's edge along the
 * unit direction (without), and the bit is set. Any acceptance fires reaction 0x4f (mode 6) or
 * 0x51 at the +8 point. */
typedef unsigned char u8;
typedef unsigned short u16;

struct Vecx32 { int x, y, z; };
struct Sphere { struct Vecx32 pos; int nRadius; };

struct Ov221Hit {
    char pad000[2];
    u16 nKind;
    char pad004[0x70];
    struct Vecx32 vOrigin74;
};

struct Ov221Owner {
    char pad000[0x74];
    struct Vecx32 vOrigin74;
    char pad080[0x330];
    int *pBody3b0;
    char pad3b4[0x6c];
    u8 bMask420;
};

struct Ov221Body { char pad[0x20]; struct Vecx32 vPoint20; };

struct Ov221Node {
    struct Ov221Owner *pOwner;
    char pad004[4];
    int nEffect08;
    char pad00c[0x44];
    int nHeading50;
    char pad054[0x22];
    u8 bMask76;
};

extern int func_ov107_020c8eb8(struct Ov221Owner *owner, void *query, void *out);
extern int func_ov107_020c8fd0(struct Ov221Owner *owner, void *params, void *out);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern void func_01ffa724(int scale, void *v, void *d);
extern void VEC_Add(void *a, void *b, void *d);
extern int func_ov107_020ca918(struct Ov221Hit *hit, struct Ov221Owner *a, struct Ov221Owner *b,
                               u8 kind, void *push, int z);
extern void func_ov107_020c0b90(struct Ov221Owner *owner, int a, struct Vecx32 v, int b);
extern void func_ov107_020c5af8(struct Ov221Owner *owner, int a, int id, int p);
extern const struct Vecx32 data_02042258;
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov222_020d284c(struct Ov221Node *node, unsigned int mode, void *params)
{
    struct Sphere sphere;
    struct Ov221Hit *hits[4];
    struct Vecx32 dir;
    struct Vecx32 push;
    struct Vecx32 step;
    int n;
    int pushed;
    int i;
    u8 bit;
    u8 *pMask;
    unsigned int idx;

    pushed = 0;
    if (mode == 6) {
        pMask = &node->pOwner->bMask420;
    } else {
        pMask = &node->bMask76;
    }
    if (params != 0) {
        n = func_ov107_020c8fd0(node->pOwner, params, hits);
    } else {
        sphere.pos = ((struct Ov221Body *)*node->pOwner->pBody3b0)->vPoint20;
        sphere.nRadius = 0x1380;
        if (mode == 7) {
            sphere.nRadius = 0x2400;
        } else {
            idx = ANG2IDX(node->nHeading50);
            dir.x = data_0203d210[idx * 2];
            dir.y = 0;
            dir.z = data_0203d210[idx * 2 + 1];
            func_01ffa724(sphere.nRadius, &dir, &dir);
            VEC_Add(&dir, &sphere.pos, &sphere.pos);
        }
        n = func_ov107_020c8eb8(node->pOwner, &sphere, hits);
    }
    i = 0;
    if (n > 0) {
        do {
            bit = (u8)(1 << hits[i]->nKind);
            if ((*pMask & bit) == 0) {
                VEC_Subtract(&hits[i]->vOrigin74, &node->pOwner->vOrigin74, &push);
                func_01ff8d18(&push, &step);
                push.y = 0;
                if (func_01ff8d18(&push, &push) == 0) {
                    push = data_02042258;
                }
                func_01ffa724(0x1000, &push, &push);
                if (func_ov107_020ca918(hits[i], node->pOwner, node->pOwner, mode, &push, 0) != 0) {
                    if (params != 0) {
                        step = hits[i]->vOrigin74;
                    } else {
                        func_01ffa724(sphere.nRadius, &step, &step);
                        VEC_Add(&step, &sphere.pos, &step);
                    }
                    func_ov107_020c0b90(node->pOwner, 0, step, 0);
                    *pMask |= bit;
                    pushed = 1;
                }
            }
            i++;
        } while (i < n);
    }
    if (pushed == 0) {
        return;
    }
    switch (mode) {
    case 6:
        func_ov107_020c5af8(node->pOwner, 0, 0x4f, node->nEffect08);
        break;
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    default:
        func_ov107_020c5af8(node->pOwner, 0, 0x51, node->nEffect08);
        break;
    }
}
