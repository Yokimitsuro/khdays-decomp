/* Fires both of the mission owner's +0x2d38 rows (stride 0x240): each shot spawns at the row's
 * slot position (4ef0), aims along the normalised +0x340 vector of the row, kind 7 from a slot,
 * speed 0x1100, and is handed to func_ov022_02091324. */
typedef struct { int x, y, z; } Vec3;

/* One object, not two: the position vector is its head and the projectile fields are its
 * tail, which is why the ROM passes a single pointer. */
struct FireParams {
    Vec3 vPos;
    short vx;
    short vy;
    short vz;
    short nSpeed;
    int bFromSlot;
    int nKind;
    int pad1c[4];
};

extern void func_ov062_020b76f0(char *self, int slot, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern void func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov022_02091324(char *self, struct FireParams *p);
extern char *data_ov062_020b80e0;

void func_ov062_020b7920(char *self)
{
    Vec3 vAim;
    struct FireParams p;
    int i;
    char *pRow = data_ov062_020b80e0 + 0x138 + 0x2c00;

    for (i = 0; i < 2; i++) {
        func_ov062_020b76f0(self, i, &p.vPos);
        vAim = *(Vec3 *)(pRow + 0x340);
        if (VEC_Mag(&vAim) != 0) {
            func_01ff8d18(&vAim, &vAim);
        }
        p.vx = (short)vAim.x;
        p.vy = (short)vAim.y;
        p.vz = (short)vAim.z;
        p.bFromSlot = 1;
        p.pad1c[0] = 0;
        p.pad1c[1] = 0;
        p.nKind = 7;
        p.pad1c[2] = 0;
        p.pad1c[3] = 0;
        p.nSpeed = 0x1100;
        func_ov022_02091324(self, &p);
        pRow += 0x240;
    }
}
