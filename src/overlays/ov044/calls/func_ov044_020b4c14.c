#pragma opt_propagation off
#pragma opt_common_subs off

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct Vec3 {
    int x;
    int y;
    int z;
};

struct Ov044UpdateVectors {
    struct Vec3 horizontal;
    struct Vec3 movement;
    struct Vec3 direction;
};

struct Ov044Node {
    u32 flags00;
    u16 flags04;
    char pad006[0x7a];
    u16 angle80;
};

struct Ov044Actor;
typedef int (*Ov044ActorCallback)(struct Ov044Actor *actor, int mode);
typedef int (*Ov044ActorUpdateCallback)(struct Ov044Actor *actor);

struct Ov044ActorBits694 {
    u8 bit0 : 1;
    u8 callbackActive : 1;
};

struct Ov044Actor {
    u64 flags000;
    char pad008[0x10];
    u16 flags18;
    char pad01a[6];
    struct Ov044Node *node20;
    u32 flags24;
    char pad028[0x30];
    int verticalDelta58;
    char pad05c[0x408];
    u64 flags464;
    u64 flags46c;
    char pad474[0x18];
    struct Vec3 anchor48c;
    struct Vec3 accumulated498;
    char pad4a4[0x1c0];
    Ov044ActorCallback callback664;
    Ov044ActorUpdateCallback callback668;
    char pad66c[0x28];
    struct Ov044ActorBits694 bits694;
    char pad695[3];
    struct Vec3 accumulated698;
    char pad6a4[0x10c];
    int timeline7b0;
    char pad7b4[0x1b44];
    u8 effectContext22f8[1];
};

struct Ov044Controller4c14 {
    char pad000[8];
    int latched08;
    char pad00c[0xda8];
    struct Ov044Actor *actorDb4;
};

extern u32 func_02030788(void);
extern int func_ov022_020ad114(struct Ov044Actor *actor);
extern struct Vec3 *func_ov022_020ad0c0(struct Ov044Actor *actor);
extern void VEC_Subtract(const struct Vec3 *a, const struct Vec3 *b,
                         struct Vec3 *out);
extern int VEC_Mag(const struct Vec3 *v);
extern void func_01ff8d18(const struct Vec3 *v, struct Vec3 *out);
extern int FX_Atan2(int y, int x);
extern void func_ov022_0209fe20(struct Ov044Actor *actor, struct Vec3 *out);
extern void VEC_Add(const struct Vec3 *a, const struct Vec3 *b,
                    struct Vec3 *out);
extern void func_ov044_020b4498(struct Ov044Controller4c14 *self);
extern int func_ov022_02095554(void *context);
extern int func_ov022_02095524(void *context);
extern void func_ov022_020acf14(struct Ov044Actor *actor, int mode);
extern void func_0202af1c(u16 *nodeFlags);
extern void *func_ov022_020a35f4(struct Ov044Actor *actor, int mode);

void *func_ov044_020b4c14(struct Ov044Controller4c14 *self)
{
    void *result = 0;
    struct Ov044Actor *actor = self->actorDb4;
    register int angle = -1;
    int finishAllowed = 0;
    int zero;
    struct Ov044UpdateVectors vectors;

    if (func_02030788() == 0) {
        actor->flags464 |= 0x10000ULL;
    }
    if (func_02030788() == 0) {
        actor->flags46c |= 0x10000ULL;
    }

    if (func_ov022_020ad114(actor) != 0) {
        VEC_Subtract(func_ov022_020ad0c0(actor), &actor->anchor48c,
                     &vectors.direction);
        if (VEC_Mag(&vectors.direction) != 0) {
            func_01ff8d18(&vectors.direction, &vectors.direction);
        }
        angle = (u16)FX_Atan2(-vectors.direction.x, -vectors.direction.z);
    }

    if (actor->timeline7b0 % 0x6000 == 0 && angle != -1) {
        struct Ov044Node *node = actor->node20;
        if ((node->flags00 & 0x20) == 0) {
            node->angle80 = (u16)(angle + 0x8000);
            node->flags04 |= 0x20;
        }
    }

    if (func_02030788() == 0) {
        actor->flags464 |= 8ULL << 32;
    }

    func_ov022_0209fe20(actor, &vectors.movement);
    if (vectors.movement.y != 0) {
        actor->verticalDelta58 = vectors.movement.y;
    } else if ((actor->flags24 & 4) == 0 &&
               (func_ov022_020ad114(actor) != 0 ||
                (actor->flags000 & (0x10ULL << 32)) != 0)) {
        actor->verticalDelta58 = 0;
    }

    vectors.horizontal = vectors.movement;
    vectors.horizontal.y = 0;
    VEC_Add(&actor->accumulated498, &vectors.horizontal,
            &actor->accumulated498);

    if ((actor->flags18 & 1) != 0) {
        self->latched08 = 1;
    }

    actor->bits694.callbackActive = actor->callback668(actor);
    func_ov044_020b4498(self);

    if (self->latched08 != 0 && actor->timeline7b0 >= 0x39000) {
        int canDispatch = 1;
        if (func_ov022_02095554(actor->effectContext22f8) != 0) {
            canDispatch = 0;
        }
        int effectActive = func_ov022_02095524(actor->effectContext22f8);

        if (effectActive == 0) {
            canDispatch = 0;
            finishAllowed = 1;
        }
        if (func_ov022_020ad114(actor) == 0 &&
            (actor->flags24 & 4) == 0 &&
            (actor->flags000 & (0x10ULL << 32)) == 0) {
            canDispatch = 0;
            finishAllowed = 1;
        }
        if (canDispatch != 0) {
            func_ov022_020acf14(actor, 0);
        } else {
            actor->bits694.callbackActive = 1;
        }
    }

    if (actor->timeline7b0 == 0x12000 &&
        (actor->flags000 & (0x10ULL << 32)) == 0 &&
        func_ov022_020ad114(actor) == 0 &&
        (actor->flags24 & 4) == 0) {
        self->latched08 = 0;
    }

    switch (actor->timeline7b0) {
    case 0x9000:
    case 0x12000:
    case 0x18000:
    case 0x21000:
    case 0x2d000:
    case 0x39000:
        if (self->latched08 == 0) {
            finishAllowed = 1;
            actor->bits694.callbackActive = 1;
        }
        self->latched08 = 0;
        break;
    }

    if (actor->bits694.callbackActive) {
        struct Ov044Node *node;

        actor->flags000 |= 0x20000ULL << 32;
        node = actor->node20;
        if ((node->flags00 & 0x20) == 0) {
            func_0202af1c(&node->flags04);
        }
        if (func_02030788() == 0) {
            actor->flags464 |= 2ULL;
        }
    }

    if ((actor->flags464 & 2ULL) != 0) {
        if (actor->timeline7b0 < 0x39000 ||
            func_ov022_02095524(actor->effectContext22f8) == 0 ||
            finishAllowed != 0) {
            zero = 0;
            actor->accumulated698.x = actor->accumulated698.y =
                actor->accumulated698.z = actor->accumulated498.x =
                actor->accumulated498.y = actor->accumulated498.z = zero;
            actor->flags000 |= 4ULL;
            if ((actor->flags24 & 4) != 0) {
                result = func_ov022_020a35f4(actor, zero);
                actor->callback664(actor, 0);
            } else {
                result = func_ov022_020a35f4(actor, 2);
            }
        } else {
            if (func_02030788() == 0) {
                actor->flags464 |= 0x80000000ULL;
            }
            result = func_ov022_020a35f4(actor, 0x23);
        }
    }

    if (result != 0) {
        actor->flags46c &= ~0x10000ULL;
    }
    return result;
}
