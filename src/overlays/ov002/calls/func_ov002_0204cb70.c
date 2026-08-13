typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    int x;
    int y;
    int z;
} Ov002MotionPreset;

typedef struct {
    char pad00[0x38];
    unsigned int flags;            /* +0x38 */
    char pad3c[4];
    int mode;                      /* +0x40 */
    int value;                     /* +0x44 */
    char pad48[0x18];
    int derivedZ;                  /* +0x60 */
    char pad64[0x28];
    Vec3 target;                   /* +0x8c */
    char pad98[0x24];
    int presetX0;                  /* +0xbc */
    int scratch0;                  /* +0xc0 */
    int scratch1;                  /* +0xc4 */
    int presetX1;                  /* +0xc8 */
    int presetIndex;               /* +0xcc */
} Ov002MotionState;

typedef struct {
    char pad00[0x20];
    Ov002MotionState *motion;       /* +0x20 */
} Ov002Actor;

extern int func_ov002_02050a54(int value);
extern Ov002MotionPreset data_ov002_0207e738[];

void func_ov002_0204cb70(Ov002Actor *actor, int mode, void *modeData)
{
    Ov002MotionState *motion = actor->motion;

    if (mode != 3 && mode != 4 && mode != 9 && motion->mode == mode) {
        return;
    }

    switch (mode) {
    case 0:
    case 8:
        if (motion->mode == 1) {
            motion->flags = (motion->flags & 0xfffff7ff) | 0x1000;
        } else if (motion->mode == 3) {
            motion->scratch0 = 0;
            motion->presetX0 = 0;
        }
        motion->derivedZ = func_ov002_02050a54(motion->value);
        motion->flags &= 0xd7ffbeff;
        break;
    case 6:
        motion->flags |= 0x8000;
        break;
    case 10:
        motion->flags |= 0x20000000;
        break;
    case 1:
        motion->flags = (motion->flags & 0xffffefff) | 0x800;
        break;
    case 2:
        motion->derivedZ = func_ov002_02050a54(motion->value) - 0x1a00;
        break;
    case 3:
        motion->presetIndex = (int)modeData;
        motion->scratch0 = 0;
        motion->scratch1 = 0;
        motion->presetX0 = data_ov002_0207e738[motion->presetIndex].x;
        motion->presetX1 = data_ov002_0207e738[motion->presetIndex].x;
        break;
    case 9:
        motion->flags |= 0x08000000;
    case 4:
        if (modeData == 0) {
            return;
        }
        motion->target = *(Vec3 *)modeData;
        break;
    case 5:
        motion->mode = 0;
        motion->flags |= 0x4000;
        break;
    }

    motion->mode = mode;
}
