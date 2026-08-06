#pragma opt_propagation off
#pragma opt_common_subs off
#pragma opt_dead_assignments off

typedef long long s64;
typedef unsigned long long u64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Vec3;
struct TimelineActor;
struct StructOut;
struct StructM;

extern void func_ov022_020ad44c(struct Vec3 *, struct TimelineActor *);
extern void func_ov022_020a23a4(struct TimelineActor *, int, int *, int *);
extern int func_ov022_020a0fb8(struct TimelineActor *, struct StructOut *, int *, int);
extern unsigned func_020307f4(unsigned);
extern int func_0203084c(void);
extern void func_ov022_0209246c(void *, int, struct StructM *);

extern const short data_0203d210[];

struct Vec3 { int x, y, z; };
struct Direction3 {
    int x;
    int y;
    int z;
};

struct BlockConstants {
    int zero;
    int scale;
};

struct ScaleSlot {
    int value;
};

struct TimelineActorNode {
    u32 flags00;
    u16 flags04;
    char pad006[0x7a];
    u16 angle80;
};

struct TimelineActor {
    u32 flags000;
    char pad004[5];
    u8 byte009;
    char pad00a[0x16];
    struct TimelineActorNode *node020;
    char pad024[0x42];
    short field066;
    char pad068[0x412];
    signed char action47a;
    u8 action47b;
    char pad47c[0x32a];
    short field7a6;
    char pad7a8[8];
    int timeline7b0;
    char pad7b4[0x1e94];
    u8 effect2648[0x74];
    u32 flags26bc;
    char pad26c0[8];
    struct Vec3 position26c8;
};

struct TimelineActorOwner {
    int variant000;
    char pad004[0xdb0];
    struct TimelineActor *actorDb4;
};

struct StructB {
    int f00;
    int f04;
    int f08;
    int f0c;
    unsigned char f10;
    unsigned char pad11[3];
    int f14;
    int f18;
    int f1c;
    int f20;
    unsigned char pad24;
    unsigned char f25;
    unsigned char pad26[2];
};

struct StructOut {
    struct Vec3 head;
    int f0c;
    int f10;
    struct Direction3 direction14;
    int f20;
    int f24;
    int f28;
};

static inline void VecSet(struct Vec3 *out, int z, int y, int x) {
    out->x = x;
    out->y = y;
    out->z = z;
}

struct StructM {
    unsigned char f00;
    unsigned char pad01[3];
    struct Vec3 f04;
    unsigned short f10;
    unsigned short f12;
    unsigned char f14;
    unsigned char f15;
    unsigned short f16;
    unsigned short f18;
};

void func_ov030_020b4864(struct TimelineActorOwner *this) {
    struct TimelineActor *p = this->actorDb4;
    int v = p->timeline7b0;
    int ok;
    int idx;
    register int angle;
    int effectKind;
    struct StructOut so;
    struct StructB sb;
    struct Vec3 tmp;
    struct StructM sm;
    unsigned char b;
    int sinValue, cosValue;

    if (v % 3 != 0) {
        return;
    }

    switch (v) {
    case 0x9000: case 0xf000: case 0x15000: case 0x1b000:
    case 0x21000: case 0x27000: case 0x33000: case 0x3c000:
    case 0x4b000:
        ok = 1;
        break;
    default:
        ok = 0;
        break;
    }
    if (ok == 0) {
        return;
    }

    func_ov022_020ad44c(&so.head, p);
    const short *table = data_0203d210;
    register int unit;
    register int zero;

    angle = (u16)(p->node020->angle80 - 0x8000);
    idx = angle >> 4;
    register const int scale = 0x2800;
    sinValue = -table[idx * 2];
    cosValue = -table[idx * 2 + 1];
    zero = 0;
    so.direction14.y = zero;
    so.direction14.x = sinValue;
    so.f0c = scale;
    so.direction14.z = cosValue;
    so.f10 = p->field066;
    unit = 0x1000;
    so.f20 = unit;
    so.f24 = zero;
    so.f28 = zero;

    {
        int arg = unit + 0x3b0;
        sb.f08 = 0x205;
        if (this->variant000 != 0) {
            sb.f08 |= 0x420;
            arg = 0x12c0;
        }
        func_ov022_020a23a4(p, arg, &sb.f00, &sb.f04);
    }
    sb.f0c = 0;
    sb.f14 = 0xa00;
    sb.f18 = 0x66;
    sb.f1c = 0xa00;
    sb.f20 = 0;
    sb.f10 = 0;
    b = sb.f25 & ~1;
    sb.f25 = b & ~2;

    if (func_ov022_020a0fb8(p, &so, &sb.f00, b & ~2) == 0) {
        return;
    }

    if (p->flags26bc & 1) {
        return;
    }
    if (p->flags26bc & 0x40) {
        return;
    }

    effectKind = func_020307f4(3);

    tmp = p->position26c8;
    register int randomOffset;
    randomOffset = func_0203084c() - 0x800;
    tmp.x += (int)(((s64)randomOffset * 0x99a + 0x800) >> 12);
    randomOffset = func_0203084c() - 0x800;
    tmp.y += (int)(((s64)randomOffset * 0x4cd + 0x800) >> 12);
    randomOffset = func_0203084c() - 0x800;
    tmp.z += (int)(((s64)randomOffset * 0x99a + 0x800) >> 12);

    sm.f00 = p->byte009;
    sm.f04 = tmp;
    sm.f10 = 0x1000;
    sm.f12 = (unsigned short)angle;
    sm.f14 = effectKind;
    sm.f15 = 1;
    sm.f16 = p->field7a6;
    sm.f18 = 0;

    func_ov022_0209246c(p->effect2648, 5, &sm);

    if (p->action47a != -1) {
        return;
    }
    if ((u32)(((u64)p->flags000) & 0x10000ULL) == 0) {
        p->action47a = 3;
        p->action47b = 0;
    }
}

