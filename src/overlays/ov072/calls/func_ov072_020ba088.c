/* Shot step of the ov032 enemy (and its byte-identical twins): on the local player both 64-bit
 * flag words get bit 16 and bit 7 of +0x24 is cleared; with the mission root's +0x2e78 flag
 * set the shared sampler gives a spawn motion that is folded into the +0x498 position on the
 * ground plane (raising bit 46 and clearing +0x58 unless bit 2 of +0x24 says grounded). While
 * the +0x4cc timer is non-negative and the +0x2e7c latch clear, the projectile parameters are
 * built from the overlay's aim/offset vectors rotated by the facing (speed 0x1a00, kind 0, or
 * 0x2200/kind 1 with the extra fields when the flag is set; otherwise a puppet-free actor queues
 * action 3/0) and handed to 02091324, latching +0x2e7c. The +0x668 hook then decides the fired
 * bit (bit 49, node shown, bit 1 of +0x464 on the local session); once fired the state becomes
 * 0x23 while the +0x22f8 emitter is idle, else 0x25 once the timer reaches +0x7b0 (plus 0xf000
 * with the flag). */
struct ActorBits {
    unsigned char bUnk0 : 1;
    unsigned char bFired : 1;
};

typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

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

extern int func_02030788(void);                                                /* Session_GetLocalPlayerIndex */
extern void func_ov022_0209fe20(char *self, Vec3 *pOut);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void MTX_RotY33_(Mtx33 *m, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *v, const Mtx33 *m, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern void func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov022_02091324(char *self, struct FireParams *p);
extern void func_0202af1c(int *p);
extern int func_ov022_02095524(char *emitter);
extern int func_ov022_020a35f4(char *self, int nMode);
extern int data_ov072_020ba7a0;
extern Vec3 data_02041dc8;
extern Vec3 data_ov072_020ba5c8;
extern Vec3 data_ov072_020ba5d4;
extern const short data_0203d210[];

int func_ov072_020ba088(char *self)
{
    Vec3 vSpawn;
    Vec3 vAim;
    Vec3 vDir;
    Mtx33 mFacing;
    struct FireParams p;
    Vec3 vOffset;
    int nRet = 0;
    int *pBlock = (int *)(*(int *)&data_ov072_020ba7a0 + 0x278 + 0x2c00);
    int nLimit;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000ULL;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000ULL;
    }
    *(int *)(self + 0x24) &= ~0x80;
    vSpawn = data_02041dc8;
    if (pBlock[0] != 0) {
        func_ov022_0209fe20(self, &vSpawn);
    }
    if ((*(int *)(self + 0x24) & 4) == 0) {
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    vOffset = vSpawn;
    vOffset.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &vOffset, (Vec3 *)(self + 0x98 + 0x400));
    if (*(int *)(self + 0x4cc) >= 0 && pBlock[1] == 0) {
        int nIndex;
        vAim = data_ov072_020ba5c8;
        vDir = data_ov072_020ba5d4;
        nIndex = (unsigned short)(*(unsigned short *)(*(char **)(self + 0x20) + 0x80)
                                  - 0x8000) >> 4;
        MTX_RotY33_(&mFacing, -data_0203d210[nIndex * 2], -data_0203d210[nIndex * 2 + 1]);
        MTX_MultVec33(&vDir, &mFacing, &p.vPos);
        VEC_Add(&p.vPos, (Vec3 *)(self + 0x8c + 0x400), &p.vPos);
        MTX_RotY33_(&mFacing, -data_0203d210[nIndex * 2], -data_0203d210[nIndex * 2 + 1]);
        MTX_MultVec33(&vAim, &mFacing, &vAim);
        if (VEC_Mag(&vAim) != 0) {
            func_01ff8d18(&vAim, &vAim);
        }
        p.vx = (short)vAim.x;
        p.vy = (short)vAim.y;
        p.vz = (short)vAim.z;
        p.nSpeed = 0x1a00;
        p.bFromSlot = 1;
        p.pad1c[0] = 1;
        p.pad1c[1] = 0;
        p.nKind = 0;
        p.pad1c[3] = 0;
        p.pad1c[2] = 0;
        if (pBlock[0] != 0) {
            p.nSpeed = 0x2200;
            p.nKind = 1;
            p.pad1c[3] = 1;
            p.pad1c[2] = 1;
        } else if ((*(int *)self & 0x10000) == 0) {
            *(unsigned char *)(self + 0x47a) = 3;
            *(unsigned char *)(self + 0x47b) = 0;
        }
        func_ov022_02091324(self, &p);
        pBlock[1] = 1;
    }
    ((struct ActorBits *)(self + 0x694))->bFired = (*(int (**)(char *))(self + 0x668))(self);
    if (((struct ActorBits *)(self + 0x694))->bFired) {
        *(unsigned long long *)self |= 0x2000000000000ULL;
        if ((**(int **)(self + 0x20) & 0x20) == 0) {
            func_0202af1c(*(int **)(self + 0x20) + 1);
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)(self + 0x464) |= 2ULL;
        }
    }
    if (((struct ActorBits *)(self + 0x694))->bFired) {
        nLimit = pBlock[0] != 0 ? 0xf000 : 0;
        if (func_ov022_02095524(self + 0x2f8 + 0x2000) == 0) {
            nRet = func_ov022_020a35f4(self, 0x23);
        } else if (*(int *)(self + 0x4cc) >= *(int *)(self + 0x7b0) + nLimit) {
            nRet = func_ov022_020a35f4(self, 0x25);
        }
    }
    return nRet;
}
