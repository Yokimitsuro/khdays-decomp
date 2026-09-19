/* Facing update: when a heading word is supplied, rebuild the actor's +0xa0 orientation about
 * world Y from it scaled by pi/180 (x 0x3244 / 180). */
typedef struct { int x, y, z; } Vec3;
extern void func_0203c9b4(void *quat, const Vec3 *axis, int angle);
extern const Vec3 data_02042264;

void func_ov244_020cd130(char *actor, int unused, int *pHeading) {
    if (pHeading == 0) return;
    func_0203c9b4(actor + 0xa0, &data_02042264, *pHeading * 0x3244 / 180);
}
