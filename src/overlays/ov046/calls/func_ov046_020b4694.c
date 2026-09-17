typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct Vec3 {
    int x;
    int y;
    int z;
};

struct Ov046StepVectors {
    struct Vec3 horizontal;
    struct Vec3 movement;
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
    u16 flags1a;
    char pad01c[4];
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

/* Per-frame end-of-attack step for the ov046 enemy (x4: ov046/065/084/101), the tail of the
 * ov030 shape without the steering: mark the two attack-flag words 0x10000 on the local player's
 * side, keep the actor on the ground (bit 0x4000 of the high flag word, vertical delta 0) unless
 * its +0x24 bit 2 says otherwise, run the update callback, and once the effect context has gone
 * quiet or the attack bit is clear finish through 020a35f4: mode 0x22 while the shared rig's
 * +0x2d90 counter is still 2 or more, otherwise clear both accumulated vectors and finish with
 * mode 0 (after the +0x664 callback) or 2 depending on the +0x24 bit. */
extern u32 func_02030788(void);
extern void VEC_Add(const struct Vec3 *a, const struct Vec3 *b, struct Vec3 *out);
extern int func_ov022_02095524(void *context);
extern void *func_ov022_020a35f4(struct Ov044Actor *actor, int mode);
extern char *data_ov046_020b4b40;

void *func_ov046_020b4694(struct Ov044Actor *actor)
{
    char *rig = data_ov046_020b4b40 + 0x2c80;
    void *result = 0;
    int finishAllowed = 0;
    struct Ov046StepVectors vectors;
    int effectActive;

    if (func_02030788() == 0) {
        actor->flags464 |= 0x10000ULL;
    }
    if (func_02030788() == 0) {
        actor->flags46c |= 0x10000ULL;
    }
    {
        u32 flags24 = actor->flags24;
        vectors.movement.z = 0;
        vectors.movement.y = 0;
        vectors.movement.x = 0;
        if ((flags24 & 4) == 0) {
            actor->flags000 |= 0x4000ULL << 32;
            actor->verticalDelta58 = 0;
        }
    }
    vectors.horizontal = vectors.movement;
    vectors.horizontal.y = 0;
    VEC_Add(&actor->accumulated498, &vectors.horizontal, &actor->accumulated498);
    actor->callback668(actor);
    if ((actor->flags1a & 1) == 0) {
        finishAllowed = 1;
    }
    effectActive = func_ov022_02095524(actor->effectContext22f8);
    if (effectActive == 0 || finishAllowed != 0) {
        if (*(int *)(rig + 0x110) > 1) {
            result = func_ov022_020a35f4(actor, 0x22);
        } else {
            actor->accumulated498.z = 0;
            actor->accumulated498.y = 0;
            actor->accumulated498.x = 0;
            actor->accumulated698.z = 0;
            actor->accumulated698.y = 0;
            actor->accumulated698.x = 0;
            if ((actor->flags24 & 4) != 0) {
                actor->callback664(actor, 0);
                result = func_ov022_020a35f4(actor, 0);
            } else {
                result = func_ov022_020a35f4(actor, 2);
            }
        }
    }
    return result;
}
