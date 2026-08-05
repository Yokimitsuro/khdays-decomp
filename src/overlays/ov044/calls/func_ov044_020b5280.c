typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct Ov044Actor {
    char pad000[8];
    u8 owner08;
    char pad009[0x17];
    void *node20;
    char pad024[0x440];
    u64 flags464;
    u64 flags46c;
    char pad474[0x248];
    int state6bc;
    char pad6c0[0xea];
    s16 cue7aa;
    char pad7ac[4];
    int timeline7b0;
};

struct Ov044MotionState {
    char bytes[0x170];
};

struct Ov044Controller {
    char pad000[0x0c];
    int pending0c;
    char pad010[4];
    int animState14;
    char animation18[0xe0];
    char animationTablef8[0x138];
    int playerHandle230;
    struct Ov044MotionState motions234[8];
    struct Ov044Actor *actorDb4;
};

extern int func_ov022_02083f0c(void);
extern void func_ov002_0204cdf4(int handle, int a, int b);
extern int func_02030788(void);
extern int func_ov022_020ad718(struct Ov044Actor *actor);
extern void func_ov022_020a4490(struct Ov044Actor *actor, int cue, int mode);
extern void func_ov044_020b3b64(struct Ov044Controller *self);
extern int func_ov044_020b3cf4(struct Ov044Controller *self,
                               struct Ov044MotionState *motion, int delta);
extern int func_ov022_02095524(void *buildBlock);
extern void func_0202accc(void *animation, int track, void *table, int mode);
extern void func_01fff774(void *animation, int track, int frame);
extern int func_0202a818(void *animation, int delta);
extern void func_ov044_020b43b0(struct Ov044Controller *self, int delta);
extern void func_ov044_020b42c0(struct Ov044Controller *self);

void func_ov044_020b5280(struct Ov044Controller *self, int delta)
{
    struct Ov044Actor *actor = self->actorDb4;
    int active = 0;
    int i;
    struct Ov044MotionState *motion;

    if (actor->state6bc != 0x2f) {
        if (self->playerHandle230 == 1) {
            func_ov002_0204cdf4(func_ov022_02083f0c(), 0, 0);
            self->playerHandle230 = 0;
        }
    } else if (actor->owner08 == func_02030788()) {
        self->playerHandle230 = func_ov022_020ad718(actor);
    }

    switch (self->pending0c) {
    case 1:
        break;
    default:
        goto afterSpawn;
    }
    if (actor->state6bc != 0x30) {
        goto afterSpawn;
    }
    if (actor->timeline7b0 < 0x39000) {
        goto afterSpawn;
    }
    func_ov022_020a4490(actor, actor->cue7aa, 0);
    func_ov044_020b3b64(self);
    self->pending0c = 0;
afterSpawn:

    motion = self->motions234;
    i = 0;
    do {
        if (func_ov044_020b3cf4(self, motion, delta) != 0) {
            active = 1;
        }
        i++;
        motion++;
    } while (i < 8);

    if ((u32)(actor->state6bc - 0x2f) <= 1) {
        active = 1;
    }

    if (active != 0) {
        if (func_02030788() == 0) {
            actor->flags464 |= 0x10000;
        }
        if (func_02030788() == 0) {
            actor->flags46c |= 0x10000;
        }
    }

    if (self->pending0c != 0) {
        if (func_ov022_02095524((char *)actor + 0x22f8) == 0 &&
            active == 0) {
            self->pending0c = 0;
        }
    }

    if (self->animState14 == 1) {
        goto updateAnimation;
    }
    if (self->animState14 != 2) {
        goto afterAnimation;
    }
    if (actor->timeline7b0 < 0x4b000) {
        goto afterAnimation;
    }
    func_0202accc(self->animation18, 0, self->animationTablef8, 0);
    func_0202accc(self->animation18, 2, self->animationTablef8, 0);
    func_01fff774(self->animation18, 0, 0);
    func_01fff774(self->animation18, 2, 0);
    self->animState14 = 1;
    goto afterAnimation;

updateAnimation:
    if (func_0202a818(self->animation18, delta) != 0) {
        self->animState14 = 0;
    }
afterAnimation:

    func_ov044_020b43b0(self, delta);
    func_ov044_020b42c0(self);
}
