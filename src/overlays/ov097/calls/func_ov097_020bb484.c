/* Launches a projectile of the ov041 enemy (x4: ov041/060/080/097): takes the first free slot of
 * the three at +0x330 of the slot block (0x110 apart), puts it in phase 2 with tracks 0 and 2
 * bound to its own blend table (+0xe4) and rewound, places it one unit behind the anchor sample
 * along the actor's heading (+0xa8), and builds its orientation at +0x84 as identity rotated by
 * the heading about Y and by the given roll about Z. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void func_0202accc(void *animation, int track, void *table, short mode);   /* BindAnimTrack */
extern void func_01fff774(void *animation, int track, int frame);                /* Anim_SetFrameWrapped */
extern void func_ov022_020ad44c(Vec3 *out, char *self);
extern void VEC_MultAdd(int scale, const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void MTX_Identity33_(Mtx33 *m);
extern void MTX_RotY33_(Mtx33 *m, int s, int c);
extern void MTX_RotZ33_(Mtx33 *m, int s, int c);
extern void MTX_Concat33(const Mtx33 *a, const Mtx33 *b, Mtx33 *out);
extern void MI_Copy36B(const void *src, void *dst);
extern short data_0203d210[];

void func_ov097_020bb484(char *self, char *slots, int roll, int mode)
{
    Vec3 pos;
    Vec3 dir;
    Mtx33 m;
    Mtx33 mz;
    Mtx33 my;
    char *slot = 0;
    int i;
    char *p;
    u16 angle;
    int idx;

    for (i = 0, p = slots; i < 3; i++) {
        if (*(int *)(p + 0x330) == 0) {
            slot = slots + 0x330 + i * 0x110;
            break;
        }
        p += 0x110;
    }
    if (slot == 0) {
        return;
    }
    *(int *)slot = 2;
    func_0202accc(slot + 4, 0, slot + 0xe4, mode);
    func_0202accc(slot + 4, 2, slot + 0xe4, mode);
    func_01fff774(slot + 4, 0, 0);
    func_01fff774(slot + 4, 2, 0);
    angle = *(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000;
    idx = angle >> 4;
    dir.x = -data_0203d210[idx * 2];
    dir.z = -data_0203d210[idx * 2 + 1];
    dir.y = 0;
    func_ov022_020ad44c(&pos, self);
    VEC_MultAdd(0x1000, &dir, &pos, &pos);
    *(Vec3 *)(slot + 0xa8) = pos;
    MTX_Identity33_(&m);
    idx = (u16)(angle + 0x8000) >> 4;
    MTX_RotY33_(&my, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_Concat33(&my, &m, &m);
    MTX_RotZ33_(&mz, data_0203d210[(roll >> 4) * 2], data_0203d210[(roll >> 4) * 2 + 1]);
    MTX_Concat33(&mz, &m, &m);
    MI_Copy36B(&m, slot + 0x84);
}
