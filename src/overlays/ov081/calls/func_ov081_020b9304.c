/* Lay the enemy's trail: `move` (the frame's displacement) is added to the distance accumulated
 * in the shared object's +0x2c3c; every 0x2000 of it drops one effect (Ov042_ClaimSlotAndLaunch)
 * along the unit direction of the move, at `origin` plus the direction scaled by what was left
 * over from the previous drop (0x2000 - carry), consuming 0x2000 per drop. */
typedef struct { int x, y, z; } Vec3;

extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern int VEC_Mag(const Vec3 *v);
extern void func_01ffa724(int scale, const Vec3 *src, Vec3 *dst);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov081_020b93c8(Vec3 *pos, Vec3 *dir);                         /* Ov042_ClaimSlotAndLaunch */
extern char *data_ov081_020b96e0;

void func_ov081_020b9304(Vec3 *origin, Vec3 *move)
{
    Vec3 vDir;
    Vec3 vPos;
    char *trail = data_ov081_020b96e0 + 0x2c + 0x2c00;
    int carry = *(int *)(trail + 0x10);
    int dist;

    vDir = *move;
    func_01ff8d18(&vDir, &vDir);
    dist = *(int *)(trail + 0x10) + VEC_Mag(move);
    *(int *)(trail + 0x10) = dist;
    if (dist <= 0x2000) {
        return;
    }
    do {
        vDir = *move;
        func_01ff8d18(&vDir, &vDir);
        func_01ffa724(0x2000 - carry, &vDir, &vDir);
        VEC_Add(origin, &vDir, &vPos);
        func_ov081_020b93c8(&vPos, &vDir);
        carry = *(int *)(trail + 0x10) - 0x2000;
        *(int *)(trail + 0x10) = carry;
    } while (carry > 0x2000);
}
