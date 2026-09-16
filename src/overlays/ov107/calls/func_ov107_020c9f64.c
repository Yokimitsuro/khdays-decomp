/* Collect sphere contacts against polygon fans, then visit child spatial groups.
 * The ROM adds an unwritten stack vector at +0x37c; field_34 preserves that
 * observed read. No normal calculation has been inferred for it.
 * The child-offset table is read-only in the ROM (rodata).
 */
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed long long s64;

typedef struct {
    int x;
    int z;
} Pair;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    VecFx32 center;
    int radius;
} Sphere;

typedef struct {
    int minX;
    int minZ;
    int maxX;
    int maxZ;
} Bounds;

/* Partial spatial-group layout; the object may extend beyond its children. */
typedef struct {
    u16 flags;
    u8 pad02[2];
    s16 polygonIndex;
    u8 pad06[0x10 - 0x6];
    int entries[4];
} CollisionGroup;

/* Polygon records have a 0x84-byte stride. Unused fields remain unnamed. */
typedef struct {
    u8 pad00[0x10];
    u16 flags;
    u16 kind;
    s16 normalX;
    s16 normalY;
    s16 normalZ;
    int planeDistance;
    u8 pad20[0x50 - 0x20];
    VecFx32 vertices[4];
    u8 pad80[4];
} CollisionPolygon;

typedef struct {
    s64 factorB;
    s64 factorA;
    const VecFx32 *vertices[3];
    VecFx32 edgeB;
    VecFx32 edgeA;
    VecFx32 field_34;
    u8 pad40[4];
    VecFx32 point;
    VecFx32 delta;
} CollisionScratch;

extern int func_0203ae14(const Sphere *sphere, const VecFx32 **vertices,
                         s64 *factorA, s64 *factorB);
extern int FX_Sqrt(int value);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Mag(const VecFx32 *v);
extern int func_01ff8d18(const VecFx32 *source, VecFx32 *destination);
typedef struct { s16 x, z; } ChildOffset;
extern const ChildOffset data_ov107_020cb664[4];

void func_ov107_020c9f64(const Pair *pair, int scale, const CollisionGroup *group,
                         const CollisionPolygon *polygons, const Sphere *sphere,
                         const Bounds *bounds, int *count, VecFx32 *outList,
                         VecFx32 *outDir)
{
    const VecFx32 *base;
    int triangle;
    int vertexOffset;
    int radius;
    int margin;
    Bounds groupBounds;
    CollisionScratch scratch;
    Pair childPair;
    int i;
    int quarterScale;
    const CollisionGroup *childGroup;

    margin = (scale >> 1) + 0x80;
    groupBounds.minX = pair->x - margin;
    groupBounds.minZ = pair->z - margin;
    groupBounds.maxX = pair->x + margin;
    groupBounds.maxZ = pair->z + margin;
    radius = sphere->radius;
    if (groupBounds.maxX >= bounds->minX && groupBounds.minX <= bounds->maxX &&
        groupBounds.maxZ >= bounds->minZ && groupBounds.minZ <= bounds->maxZ) {
        const CollisionPolygon *polygon = polygons + group->polygonIndex;
        do {
            if (!(polygon->flags & 0x4000)) {
                int plane = (int)(((s64)polygon->normalX * sphere->center.x +
                                   (s64)polygon->normalY * sphere->center.y +
                                   (s64)polygon->normalZ * sphere->center.z + 0x800) >> 12)
                            - polygon->planeDistance;
                triangle = 0;
                if (plane >= 0 && plane <= radius) {
                    /* Keep a byte offset separate from the fixed fan origin: a walking
                     * vertex pointer changes mwcc's loop strength reduction. */
                    base = polygon->vertices;
                    for (vertexOffset = 0; triangle < 2; triangle++, vertexOffset += sizeof(VecFx32)) {
                        scratch.vertices[0] = base;
                        scratch.vertices[1] = (const VecFx32 *)((const u8 *)base + (vertexOffset + sizeof(VecFx32)));
                        scratch.vertices[2] = (const VecFx32 *)((const u8 *)base + (vertexOffset + 2 * sizeof(VecFx32)));
                        if (FX_Sqrt(func_0203ae14(sphere, scratch.vertices,
                                                  &scratch.factorA, &scratch.factorB)) <= radius) {
                            VEC_Subtract(scratch.vertices[1], scratch.vertices[0], &scratch.edgeA);
                            VEC_Subtract(scratch.vertices[2], scratch.vertices[0], &scratch.edgeB);

                            scratch.edgeA.x = (int)((scratch.factorA * scratch.edgeA.x +
                                                     0x80000000LL) >> 32);
                            scratch.edgeA.y = (int)((scratch.factorA * scratch.edgeA.y +
                                                     0x80000000LL) >> 32);
                            scratch.edgeA.z = (int)((scratch.factorA * scratch.edgeA.z +
                                                     0x80000000LL) >> 32);
                            scratch.edgeB.x = (int)((scratch.factorB * scratch.edgeB.x +
                                                     0x80000000LL) >> 32);
                            scratch.edgeB.y = (int)((scratch.factorB * scratch.edgeB.y +
                                                     0x80000000LL) >> 32);
                            scratch.edgeB.z = (int)((scratch.factorB * scratch.edgeB.z +
                                                     0x80000000LL) >> 32);

                            VEC_Add(&scratch.edgeA, &scratch.edgeB, &scratch.point);
                            VEC_Add(&scratch.point, scratch.vertices[0], &scratch.point);
                            VEC_Subtract(&sphere->center, &scratch.point, &scratch.delta);
                            if (VEC_Mag(&scratch.delta) <= radius) {
                                outList[*count] = scratch.point;
                                VEC_Add(outDir, &scratch.field_34, outDir);
                                func_01ff8d18(outDir, outDir);
                                if (++*count >= 4)
                                    return;
                            }
                        }

                        if (polygon->kind == 3)
                            break;
                    }
                }
            }
        } while (!(polygon++->flags & 0x8000));
    }

    if (!(group->flags & 0xf0))
        return;

    quarterScale = scale >> 2;
    for (i = 0; i < 4; i++) {
        childGroup = (CollisionGroup *)group->entries[i];
        if (childGroup != 0) {
            childPair.x = quarterScale *
                          data_ov107_020cb664[i].x +
                          pair->x;
            childPair.z = quarterScale *
                          data_ov107_020cb664[i].z +
                          pair->z;
            func_ov107_020c9f64(&childPair, scale >> 1, childGroup,
                                polygons, sphere, bounds, count, outList, outDir);
            if (*count >= 4)
                return;
        }
    }
}
