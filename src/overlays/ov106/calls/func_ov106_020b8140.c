/* Queue a point in the ov106 scene: the first free of the four +0x8dd8 slots (+0x8e08 in-use flags)
 * takes `pos` and is marked used. No-op without a scene or a free slot. */
typedef struct { int x, y, z; } Vec3;
struct Ov106Scene { char pad[0x8dd8]; Vec3 points[4]; int used[4]; };

extern struct Ov106Scene *data_ov106_020b8b60;

void func_ov106_020b8140(Vec3 *pos)
{
    int i;

    if (data_ov106_020b8b60 == 0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        if (data_ov106_020b8b60->used[i] == 0) {
            data_ov106_020b8b60->points[i] = *pos;
            data_ov106_020b8b60->used[i] = 1;
            return;
        }
    }
}
