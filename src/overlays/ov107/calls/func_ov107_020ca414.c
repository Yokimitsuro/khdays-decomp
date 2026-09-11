typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 center; int radius; } Sphere;
typedef struct { int minX, minZ, maxX, maxZ; } BBox;
typedef struct { int a, b; } Pair;

typedef struct {
    char pad0[4];
    void *field4;
} Ctx;

typedef struct {
    char pad0[0x84];
    int f84;
    int f88;
    int f8c;
    char pad90[0x9c - 0x90];
    int f9c;
    char pada0[0xa4 - 0xa0];
    int fa4;
} Inner;

extern int func_ov107_020c9f64(Pair *pair, int f8c, int f9c, int fa4,
                                Sphere *b, BBox *bbox, int *count,
                                Vec3 *outList, Vec3 *outDir);

int func_ov107_020ca414(Ctx *a, Sphere *b, Vec3 *outList, Vec3 *outDir) {
    int count = 0;
    BBox bbox;
    Pair pair;
    Inner *inner;

    bbox.minX = b->center.x - b->radius;
    bbox.minZ = b->center.z - b->radius;
    bbox.maxX = b->center.x + b->radius;
    bbox.maxZ = b->center.z + b->radius;

    inner = *(Inner **)a->field4;
    pair.a = inner->f84;
    pair.b = inner->f88;

    func_ov107_020c9f64(&pair, inner->f8c, inner->f9c, inner->fa4,
                         b, &bbox, &count, outList, outDir);
    return count;
}
