/* Latch the primary camera target and drop the three view flags that depend on
 * it. A null target leaves everything alone. The three-word copy is a WHOLE-
 * STRUCT assignment, which is what produces the ldm/stm pair. */
typedef struct {
    int x, y, z;
} VecFx32;

typedef struct {
    char pad0000[0xd4];
    unsigned int dwViewFlags;   /* +0xd4 */
} CameraState;

extern VecFx32 data_0204744c;
extern CameraState data_02047394;

void func_02015880(const VecFx32 *target) {
    if (target == 0) {
        return;
    }

    data_0204744c = *target;
    data_02047394.dwViewFlags &= ~0xa4;
}
