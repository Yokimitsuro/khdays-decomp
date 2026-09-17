/* Fire one of this enemy's stored shots: the placement takes the shot's position (+0x14 of the
 * shot record), a random direction (Session_RandNextScaled(0xffff) into the sin/cos table, both
 * components negated, no vertical part), kind 7 and speed 0x1c80. On the local player's side the
 * reaction is queued as 3/0. A shot whose +0x30 word is set is the strong kind (2, else 1);
 * with `bCharged` and a shot level above 1 the placement's +0x24 counter and the reaction
 * variant go up by one; shot level 1 selects kind 3. The first shot also rings cue 0xcd at the
 * shot's position, latched in the shared rig's +0x2ce4. */
typedef unsigned short u16;
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 p; short a, b, c; short scale; int f14, f18, f1c, f20, f24, f28; } Placement;

extern unsigned func_020307f4(unsigned);                                       /* Session_RandNextScaled */
extern void func_ov022_02091324(char *, Placement *);
extern void func_ov022_020ad28c(char *self, Vec3 *pos, int nCue, int nKind);
extern short data_0203d210[];
extern char *data_ov095_020bcba0;

void func_ov095_020bbf2c(char *self, char *shot, int bCharged)
{
    Placement req;
    char *rig = data_ov095_020bcba0 + 0xd4 + 0x2c00;
    int idx;
    int nKind;

    idx = (int)func_020307f4(0xffff) >> 4;
    req.b = 0;
    req.a = -data_0203d210[idx * 2];
    req.c = -data_0203d210[idx * 2 + 1];
    req.p = *(Vec3 *)(shot + 0x14);
    req.f14 = 0;
    req.f1c = 0;
    req.f20 = 0;
    req.f28 = 0;
    req.f18 = 7;
    if ((*(int *)self & 0x10000) == 0) {
        *(u8 *)(self + 0x47a) = 3;
        *(u8 *)(self + 0x47b) = 0;
    }
    if (*(int *)(shot + 0x30) == 0) {
        req.f28 = 0;
        req.f24 = 0;
        req.scale = 0x1c80;
        nKind = 1;
    } else {
        req.f28 = 1;
        req.f24 = 1;
        req.scale = 0x1c80;
        nKind = 2;
    }
    if (bCharged != 0 && *(int *)shot > 1) {
        req.f24++;
        *(u8 *)(self + 0x47b) = 1;
    }
    if (*(int *)shot == 1) {
        nKind = 3;
    }
    func_ov022_02091324(self, &req);
    if (*(int *)(rig + 0x10) == 0) {
        func_ov022_020ad28c(self, (Vec3 *)(shot + 0x14), 0xcd, nKind);
        *(int *)(rig + 0x10) = 1;
    }
}
