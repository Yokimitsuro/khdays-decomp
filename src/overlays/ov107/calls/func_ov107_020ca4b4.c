typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct Quat {
    fx32 w, x, y, z;
} Quat;

typedef struct Pair {
    int field_00;
    int field_04;
} Pair;

typedef struct Box {
    VecFx32 center;
    VecFx32 axis[3];
    fx32 halfExtent[3];
} Box;

typedef struct ShapeList ShapeList;

typedef struct ShapeNode {
    unsigned char pad_00[4];
    struct ShapeNode *next;
    unsigned char pad_08[8];
    ShapeList *children;
    unsigned char pad_14[0xd];
    unsigned char mode;
    unsigned short flags;
    unsigned char pad_24[8];
    VecFx32 center;
    fx32 extentX;
    fx32 extentY;
    fx32 extentZ;
    int angle;
} ShapeNode;

struct ShapeList {
    unsigned short flags;
    unsigned char pad_02[6];
    ShapeNode *head;
    unsigned char pad_0c[4];
    ShapeList *children[4];
};

typedef struct Sphere {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct ChildOffset {
    short x;
    short y;
} ChildOffset;

extern void func_0202f188(Quat *out, const VecFx32 *axis, int angle);
extern void func_0202f384(void *in_vec, int unused, void *out_vec);
extern fx32 func_02037188(VecFx32 *point, Box *box, fx32 *outX, fx32 *outY, fx32 *outZ);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern fx32 func_01ff8d18(const VecFx32 *source, VecFx32 *destination);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *out);

extern const VecFx32 data_02042270;
extern const VecFx32 data_02042264;
extern const VecFx32 data_02042258;
extern const ChildOffset data_ov107_020cb664[4];

void func_ov107_020ca4b4(Pair *pair, int step, ShapeList *list, int unused,
                         Sphere *sphere, void *unused2, int *count,
                         VecFx32 *outPoints, VecFx32 *outDirection)
{
    VecFx32 difference;
    Box box;
    Quat quaternion;
    VecFx32 closest;
    VecFx32 initialDifference;
    VecFx32 unusedDifference;
    VecFx32 basisX;
    VecFx32 basisY;
    VecFx32 basisZ;
    int x;
    int y;
    int z;
    Pair childPair;
    int halfStep;
    ShapeNode *node;
    int i;
    int rotation;
    fx32 squaredDistance;

    halfStep = step >> 1;
    node = list->head;
    if (node != 0) {
        basisX = data_02042270;
        basisY = data_02042264;
        basisZ = data_02042258;

        do {
        if ((node->flags & 0xff) == 0) {
            if (node->mode == 2) {
                box.center = node->center;
                box.center.y += node->extentY >> 1;
                box.axis[0] = basisX;
                box.axis[1] = basisY;
                box.axis[2] = basisZ;
                box.halfExtent[0] = node->extentX;
                box.halfExtent[1] = node->extentY >> 1;
                box.halfExtent[2] = node->extentX;
            } else if (node->mode == 1) {
                box.center = node->center;
                box.center.y += node->extentY >> 1;
                box.axis[0] = basisX;
                box.axis[1] = basisY;
                box.axis[2] = basisZ;
                box.halfExtent[0] = node->extentX;
                box.halfExtent[1] = node->extentY >> 1;
                box.halfExtent[2] = node->extentX;
            } else {
                rotation = (int)(((long long)node->angle * 0x6487f + 0x80000) >> 20);
                func_0202f188(&quaternion, &data_02042264, rotation);
                box.center = node->center;
                func_0202f384(&box.axis[0], (int)&quaternion, (void *)&data_02042270);
                box.axis[1] = basisY;
                func_0202f384(&box.axis[2], (int)&quaternion, (void *)&data_02042258);
                box.halfExtent[0] = node->extentX >> 1;
                box.halfExtent[1] = node->extentY >> 1;
                box.halfExtent[2] = node->extentZ >> 1;
            }

            squaredDistance = func_02037188(&sphere->center, &box, &x, &y, &z);
            if (squaredDistance <=
                (fx32)(((long long)sphere->radius * sphere->radius + 0x800) >> 12)) {
                closest.x = x;
                closest.y = y;
                closest.z = z;
                VEC_Subtract(&sphere->center, &box.center, &initialDifference);
                VEC_Subtract(&sphere->center, &closest, &unusedDifference);
                outPoints[*count] = closest;
                VEC_Subtract(&closest, &box.center, &difference);
                func_01ff8d18(&difference, &difference);
                VEC_Add(outDirection, &difference, outDirection);
                func_01ff8d18(outDirection, outDirection);
                *count = *count + 1;
                if (*count >= 4) {
                    return;
                }
            }
        }
            node = node->next;
        } while (node != 0);
    }

    if ((list->flags & 0xf000) == 0) {
        return;
    }

    for (i = 0; i < 4; i++) {
        ShapeList *child = list->children[i];
        if (child != 0) {
            childPair.field_00 = pair->field_00 + (step >> 2) * data_ov107_020cb664[i].x;
            childPair.field_04 = pair->field_04 + (step >> 2) * data_ov107_020cb664[i].y;
            func_ov107_020ca4b4(&childPair, halfStep, child, unused,
                                sphere, unused2, count, outPoints, outDirection);
            if (*count >= 4) {
                return;
            }
        }
    }
}
