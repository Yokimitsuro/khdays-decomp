typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    u16 field_00;
    u8 pad002[2];
    void *field_04;               /* 0x004 */
    u8 pad008[0x48];
    int field_50;                 /* 0x050 */
    int field_54;                 /* 0x054 */
    int field_58;                 /* 0x058 */
    int flags5c;                  /* 0x05c */
    u16 flags60;                  /* 0x060 */
    u8 pad062[0x12];
    VecFx32 field_74;             /* 0x074 */
    int field_80;                 /* 0x080 */
    u8 pad084[0x1c];
    VecFx32 field_a0;             /* 0x0a0 */
    u8 pad0ac[4];
    VecFx32 field_b0;             /* 0x0b0 */
    u8 pad0bc[0x40];
    VecFx32 field_fc;             /* 0x0fc */
    u8 pad108[0xc];
    VecFx32 field_114;            /* 0x114 */
    int field_120;                /* 0x120 */
    int field_124;                /* 0x124 */
    int field_128;                /* 0x128 */
    int field_12c;                /* 0x12c */
    int field_130;                /* 0x130 */
    int field_134;                /* 0x134 */
    int field_138;                /* 0x138 */
    u8 pad13c[4];
    void *field_140;              /* 0x140 */
    u8 pad144[0x28];
    VecFx32 field_16c;            /* 0x16c */
    signed char field_178;        /* 0x178 */
    u8 pad179[1];
    u8 field_17a;                 /* 0x17a */
    u8 pad17b[5];
    VecFx32 field_180;            /* 0x180 */
};

typedef struct CollisionHit {
    void *field_00;
    void *field_04;
    void *field_08;
    int field_0c;
} CollisionHit;

typedef struct CollisionInfo {
    u8 pad00[0x14];
    short field_14;
    short field_16;
    short field_18;
    u8 pad1a[2];
    int field_1c;
    u8 pad20[2];
    u16 field_22;
} CollisionInfo;

typedef struct Owner {
    u8 pad00[0x7c];
    void *field_7c;
} Owner;

extern void func_01ffa724(int factor, int *src, int *dst);
extern int func_02020400(int numerator, int denominator);
extern void VEC_Add(int *a, int *b, int *out);
extern CollisionHit *func_01fff948(void *collision, VecFx32 *origin,
                                    VecFx32 *direction, int radius);
extern int func_01ff8d18(VecFx32 *source, VecFx32 *destination);
extern void func_01ffd144(int factor, int *in, int *out);
extern CollisionHit *func_01fff8b8(void *collision, VecFx32 *origin,
                                    VecFx32 *direction, int extra);
extern CollisionHit *func_01fff920(void *collision, VecFx32 *origin,
                                    VecFx32 *direction);
extern void func_0203ca30(void *dst, const void *src);
extern void func_ov107_020c4ecc(struct AiState *node);

void func_ov107_020c3e50(struct AiState *self, int factor)
{
    VecFx32 position;
    VecFx32 direction;
    CollisionHit *hit;
    int savedDistance;
    Owner *owner;

    do {
    if (self->field_50 != 1) {
        break;
    }
    if ((((u32)(self->flags60 << 24) >> 24) & 1) == 0) {
        break;
    }
    owner = (Owner *)self->field_04;
    if ((((u32)(self->flags60 << 24) >> 24) & 0x40) == 0 &&
        ((u32)(self->field_17a << 31) >> 31) == 0) {
        self->field_fc.y -= (int)(((long long)self->field_58 *
                                   self->flags5c + 0x800) >> 12);
    }

    func_01ffa724(factor, (int *)&self->field_fc, (int *)&self->field_fc);
    if ((signed char)self->field_178 != 0) {
    self->field_16c.x = func_02020400(self->field_16c.x, self->field_178);
    self->field_16c.y = func_02020400(self->field_16c.y, self->field_178);
    self->field_16c.z = func_02020400(self->field_16c.z, self->field_178);
    VEC_Add((int *)&self->field_fc, (int *)&self->field_16c,
            (int *)&self->field_fc);

    }

    if (owner->field_7c == 0) {
        break;
    }
    if ((self->field_00 & 0x80) != 0) {
        break;
    }
    if ((((u32)(self->flags60 << 24) >> 24) & 4) == 0) {
        position = self->field_74;
        hit = func_01fff948(owner->field_7c, &position,
                            (VecFx32 *)&self->field_fc,
                            (self->field_80 +
                             (int)((u32)self->field_80 >> 31)) >> 1);
        if (hit != 0) {
            if (hit->field_08 == 0 ||
                (hit->field_08 != 0 &&
                 (((CollisionInfo *)hit->field_08)->field_22 & 0xff) == 0)) {
                savedDistance = self->field_fc.y;
                self->field_17a |= 4;
                self->field_114.x =
                    ((CollisionInfo *)hit->field_04)->field_14;
                self->field_114.y =
                    ((CollisionInfo *)hit->field_04)->field_16;
                self->field_114.z =
                    ((CollisionInfo *)hit->field_04)->field_18;
                func_01ff8d18((VecFx32 *)&self->field_114,
                              (VecFx32 *)&self->field_114);
                self->field_120 =
                    *(int *)((char *)hit->field_04 + 0x1c);
                func_01ffd144(hit->field_0c, (int *)&self->field_fc,
                              (int *)&self->field_fc);
                self->field_fc.y = savedDistance;
            }
        }
    }

    self->field_17a &= ~8;
    if ((((u32)(self->flags60 << 24) >> 24) & 0x10) == 0) {
        position = self->field_74;
        direction = self->field_fc;
        direction.y += self->field_80;
        hit = func_01fff8b8(owner->field_7c, &position, &direction, 0);
        if (hit != 0) {
            if (hit->field_08 == 0 ||
                (hit->field_08 != 0 &&
                 (((CollisionInfo *)hit->field_08)->field_22 & 0xff) == 0)) {
                func_01ffd144(hit->field_0c, (int *)&direction,
                              (int *)&self->field_fc);
                self->field_fc.y -= self->field_80;
                self->field_17a |= 8;
                self->field_130 = ((CollisionInfo *)hit->field_04)->field_14;
                self->field_134 = ((CollisionInfo *)hit->field_04)->field_16;
                self->field_138 = ((CollisionInfo *)hit->field_04)->field_18;
            }
        }
    }

    if ((((u32)(self->flags60 << 24) >> 24) & 8) == 0) {
    position = self->field_74;
    direction = self->field_fc;
    direction.y -= self->field_80;
    hit = func_01fff920(owner->field_7c, &position, &direction);
    if (hit != 0) {
        if (hit->field_08 == 0 ||
            (hit->field_08 != 0 &&
             (((CollisionInfo *)hit->field_08)->field_22 & 0xff) == 0)) {
            func_01ffd144(hit->field_0c, (int *)&direction,
                          (int *)&self->field_fc);
            self->field_fc.y += self->field_80;
            self->field_140 = hit->field_04;
            self->field_124 = ((CollisionInfo *)self->field_140)->field_14;
            self->field_128 = ((CollisionInfo *)self->field_140)->field_16;
            self->field_12c = ((CollisionInfo *)self->field_140)->field_18;
            self->field_17a = (self->field_17a & ~1) | 1;
            VEC_Add((int *)&position, (int *)&self->field_fc,
                    (int *)&self->field_180);
        }
    }
    }

    } while (0);

    VEC_Add((int *)&self->field_b0, (int *)&self->field_fc,
            (int *)&position);
    func_0203ca30((char *)self + 0xa0, &position);
    func_ov107_020c4ecc(self);
    return;
}
