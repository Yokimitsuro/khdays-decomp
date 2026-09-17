/* Per-frame step of one stored shot record: a live record (+8) that no longer belongs to this
 * enemy (+0x2c vs the enemy's +0x66 id) is dropped. While the enemy has a target, the shot heads
 * for it (target position minus the shot's +0x14 position, speed capped at the +0xc value by the
 * distance); otherwise it keeps its last heading (+0x20). The unit heading is stored back, scaled
 * to the speed and swept against collision group +0x2c with a 0x800 radius: a hit stops the shot
 * at the contact fraction, else it just moves. Every 0x6000 of accumulated time (+0x10) it fires
 * (Ov039_FireStoredShot); the shot level (+4) goes up and, once it reaches the count at +0,
 * the shot fires charged and the record is closed. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern int func_ov022_020ad114(char *self);
extern Vec3 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern void func_01ffa724(int scale, const Vec3 *src, Vec3 *dst);
extern char *func_0202c33c(int group, const Vec3 *origin, const Vec3 *disp, int radius);
extern void func_01ffd0e8(int t, const Vec3 *disp, const Vec3 *origin, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov039_020b498c(char *self, char *shot, int bCharged);          /* Ov039_FireStoredShot */

void func_ov039_020b4168(char *self, char *shot, int dt)
{
    Vec3 vMove;
    int speed;
    char *hit;
    int bCharged;

    if (*(int *)(shot + 8) == 0) {
        return;
    }
    if (*(u8 *)(shot + 0x2c) != *(short *)(self + 0x66)) {
        *(int *)(shot + 8) = 0;
    }
    if (func_ov022_020ad114(self) != 0) {
        VEC_Subtract(func_ov022_020ad0c0(self), (Vec3 *)(shot + 0x14), &vMove);
        speed = *(int *)(shot + 0xc);
        if (VEC_Mag(&vMove) <= speed) {
            speed = VEC_Mag(&vMove);
        }
    } else {
        vMove = *(Vec3 *)(shot + 0x20);
        speed = *(int *)(shot + 0xc);
    }
    if (VEC_Mag(&vMove) != 0) {
        func_01ff8d18(&vMove, &vMove);
    }
    *(Vec3 *)(shot + 0x20) = vMove;
    func_01ffa724(speed, &vMove, &vMove);
    hit = func_0202c33c(*(u8 *)(shot + 0x2c), (Vec3 *)(shot + 0x14), &vMove, 0x800);
    if (hit != 0) {
        func_01ffd0e8(*(int *)(hit + 0xc), &vMove, (Vec3 *)(shot + 0x14), (Vec3 *)(shot + 0x14));
    } else {
        VEC_Add((Vec3 *)(shot + 0x14), &vMove, (Vec3 *)(shot + 0x14));
    }
    *(int *)(shot + 0x10) += dt;
    if (*(int *)(shot + 0x10) < 0x6000) {
        return;
    }
    bCharged = 0;
    *(int *)(shot + 0x10) = 0;
    *(int *)(shot + 4) += 1;
    if (*(int *)(shot + 4) >= *(int *)shot) {
        bCharged = 1;
    }
    func_ov039_020b498c(self, shot, bCharged);
    if (bCharged != 0) {
        *(int *)(shot + 8) = 0;
    }
}
