typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned char hi, mid, lo; } Fx24;
typedef union { struct { unsigned char pad, lo, mid, hi; } b; int w; } Fx24Word;
typedef struct { int w[11]; } BoneXform;

extern void func_0203c960(BoneXform *p);
extern void func_0203ca9c(BoneXform *p, int weight);
extern void func_0203ca30(BoneXform *dst, Vec3 *src);
extern void *func_ov107_020c0794(void *taskList, void *subitem, int mode, int blend,
                                  BoneXform *xform);

void *func_ov107_020c08cc(void *taskList, void *subitem, int mode, int blend,
                           int weight, Fx24 *payload) {
    BoneXform local;

    func_0203c960(&local);
    func_0203ca9c(&local, weight);

    if (payload != 0) {
        Vec3 decoded;
        Fx24Word d[3];

        d[0].b.hi = payload[0].hi;
        d[0].b.mid = payload[0].mid;
        d[0].b.lo = payload[0].lo;
        decoded.x = d[0].w >> 8;

        d[1].b.hi = payload[1].hi;
        d[1].b.mid = payload[1].mid;
        d[1].b.lo = payload[1].lo;
        decoded.y = d[1].w >> 8;

        d[2].b.hi = payload[2].hi;
        d[2].b.mid = payload[2].mid;
        d[2].b.lo = payload[2].lo;
        decoded.z = d[2].w >> 8;

        func_0203ca30(&local, &decoded);
    }

    return func_ov107_020c0794(taskList, subitem, mode, blend, &local);
}
