typedef unsigned char u8;
typedef unsigned short u16;

struct Ov234Vec3 {
    int x;
    int y;
    int z;
};

static inline void Ov234Vec3_Set(struct Ov234Vec3 *vec, int x, int y, int z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

struct Ov234HitFlags {
    unsigned int low : 16;
    unsigned int kind : 16;
};

struct Ov234Hit {
    struct Ov234HitFlags flags;
    struct Ov234Vec3 position;
    char pad10[0x18];
    int result28;
};

struct Ov234Object {
    char pad000[0x74];
    struct Ov234Vec3 vector74;
    char pad080[0x147];
    u8 state1c7;
};

struct Ov234Work {
    struct Ov234Object *object00;
    int field04;
    int node08;
    void *source0c;
    struct Ov234Vec3 direction10;
    char pad1c[0x0c];
    struct Ov234Vec3 velocity28;
    int angle34;
    int angle38;
    char pad3c[0x08];
    int field44;
    int timer48;
    int field4c;
    char pad50[0x10];
    int baseSpeed60;
    int active64;
    char pad68[0x0a];
    u8 facing72;
};

struct Ov234Actor {
    char pad000[0x214];
    struct Ov234Work *work214;
    char pad218[2];
    short hitCount21a;
};

struct Ov234ReactionModes {
    u8 special[2];
    u8 normal[2];
};

extern const struct Ov234ReactionModes data_ov234_020cd104;
extern const short data_0203d210[];

extern int func_ov107_020c89e8();
extern void func_ov107_020c5af8(struct Ov234Actor *, int, u16, int);
extern void func_01ffa724(int, struct Ov234Vec3 *, struct Ov234Vec3 *);
extern int func_020050b4(int, int);
extern int func_01ff8d18(struct Ov234Vec3 *, struct Ov234Vec3 *);
extern unsigned func_02023eb4(unsigned);
extern int func_02023e80(int);
extern void func_ov107_020c0b90(struct Ov234Object *, int,
                                struct Ov234Vec3, int);

int func_ov234_020cc574(struct Ov234Actor *self, void *source,
                        struct Ov234Hit *hit)
{
    struct Ov234Vec3 normalized;
    u8 specialModes[2] = {
        data_ov234_020cd104.special[0],
        data_ov234_020cd104.special[1]
    };
    u8 normalModes[2] = {
        data_ov234_020cd104.normal[0],
        data_ov234_020cd104.normal[1]
    };
    struct Ov234Work *work = self->work214;
    unsigned lowFlags;
    int angleIndex;

    hit->result28 = func_ov107_020c89e8(self, hit);

    if (self->hitCount21a <= 0) {
        return 0;
    }
    if (hit->result28 <= 0) {
        return 1;
    }
    if (work->timer48 > 0) {
        return 0;
    }

    lowFlags = hit->flags.low;
    if ((lowFlags & 0x22) != 0 &&
        ((lowFlags & 8) == 0 || (lowFlags & 0x80) == 0 ||
         hit->flags.kind != 0x80)) {
        func_ov107_020c5af8(self, 0x178,
                            normalModes[work->facing72], work->node08);
    } else {
        func_ov107_020c5af8(self, 0x178,
                            specialModes[work->facing72], work->node08);
    }

    work->source0c = source;
    work->velocity28 = hit->position;

    if (hit->flags.low & 0x20) {
        func_01ffa724(0x2000, &work->velocity28, &work->velocity28);
        work->velocity28.y = 0x3000;
        if (work->active64 == 0) {
            work->active64 = 1;
        }
    } else if (work->active64 == 0) {
        work->velocity28.y = work->baseSpeed60;
        if (work->active64 == 0) {
            work->active64 = 1;
        }
    } else {
        work->velocity28.y = 0x200;
    }

    if (*(int *)((char *)work->node08 + 4) > 0x19000) {
        work->velocity28.y = 0x100;
    }

    work->field4c = 0;
    work->field44 = 0;
    work->direction10 = work->velocity28;
    work->angle34 = work->angle38 =
        func_020050b4(work->velocity28.x, work->velocity28.z);

    if (hit->flags.low & 0x20) {
        func_01ff8d18(&work->velocity28, &normalized);
        if (func_02023eb4(100) < 50) {
            work->angle34 = work->angle38 =
                work->angle34 - func_02023e80(0x1922);
        } else {
            work->angle34 = work->angle38 =
                work->angle34 + func_02023e80(0x1922);
        }

        angleIndex =
            ((int)(u16)((unsigned int)(
                ((long long)work->angle34 * 0x28be60db9391LL +
                 0x80000000000LL) >> 32) >> 12) >> 4);
        Ov234Vec3_Set(&work->direction10,
                      data_0203d210[angleIndex * 2],
                      normalized.y,
                      data_0203d210[angleIndex * 2 + 1]);
        func_01ffa724(0xd00, &work->direction10, &work->direction10);
    }

    work->facing72 ^= 1;
    func_ov107_020c0b90(work->object00, 2, work->object00->vector74,
                        *(u8 *)((char *)work->source0c + 0x1b4));
    if (work->active64 != 0) {
        work->object00->state1c7 = 5;
    }
    return 1;
}
