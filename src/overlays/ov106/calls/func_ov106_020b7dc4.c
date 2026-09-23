/* Consume the ov106 scene's queued points that `target` reaches (020b7e38): each live one of the four
 * +0x8dd8 slots it hits is freed. */
typedef struct { int x, y, z; } Vec3;
struct Ov106Scene { char pad[0x8dd8]; Vec3 points[4]; int used[4]; };

extern struct Ov106Scene *data_ov106_020b8b60;
extern int func_ov106_020b7e38(void *target, Vec3 *point);

void func_ov106_020b7dc4(void *target)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (data_ov106_020b8b60->used[i] != 0 && func_ov106_020b7e38(target, &data_ov106_020b8b60->points[i]) != 0) {
            data_ov106_020b8b60->used[i] = 0;
        }
    }
}
