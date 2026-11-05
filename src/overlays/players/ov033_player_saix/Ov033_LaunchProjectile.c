/* Launches a projectile of the ov033 enemy (x4: ov033/051/071/089): takes the first free slot of
 * the six at +0x2d44 of the rig (0x110 apart), tells the object 0xca (variant 1 for kind 2),
 * puts the slot in phase 1 with tracks 0, 1 and 2 bound to its own table (+0xe8) in the given
 * kind and rewound, copies the spawn position to +0xac, and builds its orientation at +0x88 as
 * identity rotated by the heading about Y and, unless grounded, by random pitch and roll within
 * +/- 0x1555. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { int m[9]; } Mtx33;

extern int Ov022_PlayEntityVoice(char *self, int nSeqArc, int nSeq);
extern void BindAnimTrack(void *animation, int track, void *table, short mode);   /* BindAnimTrack */
extern void Anim_SetFrameWrapped(void *animation, int track, int frame);                /* Anim_SetFrameWrapped */
extern void MTX_Identity33_(Mtx33 *m);
extern void MTX_RotY33_(Mtx33 *m, int s, int c);
extern void MTX_RotX33_(Mtx33 *m, int s, int c);
extern void MTX_RotZ33_(Mtx33 *m, int s, int c);
extern void MTX_Concat33(const Mtx33 *a, const Mtx33 *b, Mtx33 *out);
extern void MI_Copy36B(const void *src, void *dst);
extern char *data_ov033_020b4b80;
extern short data_0203d210[];

void Ov033_LaunchProjectile(VecFx32 *pos, int angle, int kind, int grounded)
{
    Mtx33 m;
    Mtx33 mx;
    Mtx33 mz;
    Mtx33 my;
    char *base = data_ov033_020b4b80;
    char *rig = base + 0x2c + 0x2c00;
    char *slot = 0;
    char *p;
    int i;
    int idx;

    for (i = 0, p = rig; i < 6; i++) {
        if (*(int *)(p + 0x118) == 0) {
            slot = rig + 0x118 + i * 0x110;
            break;
        }
        p += 0x110;
    }
    if (slot == 0) {
        return;
    }
    if (kind == 2) {
        Ov022_PlayEntityVoice(base, 0xca, 1);
    } else {
        Ov022_PlayEntityVoice(base, 0xca, 0);
    }
    *(int *)slot = 1;
    BindAnimTrack(slot + 8, 0, slot + 0xe8, kind);
    BindAnimTrack(slot + 8, 1, slot + 0xe8, kind);
    BindAnimTrack(slot + 8, 2, slot + 0xe8, kind);
    Anim_SetFrameWrapped(slot + 8, 0, 0);
    Anim_SetFrameWrapped(slot + 8, 1, 0);
    Anim_SetFrameWrapped(slot + 8, 2, 0);
    *(VecFx32 *)(slot + 0xac) = *pos;
    MTX_Identity33_(&m);
    idx = (u16)(angle + 0x8000) >> 4;
    MTX_RotY33_(&my, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_Concat33(&my, &m, &m);
    if (grounded == 0) {
        idx = (u16)(Session_RandNextScaled(0x2aaa) - 0x1555) >> 4;
        MTX_RotX33_(&mx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
        MTX_Concat33(&mx, &m, &m);
        idx = (u16)(Session_RandNextScaled(0x2aaa) - 0x1555) >> 4;
        MTX_RotZ33_(&mz, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
        MTX_Concat33(&mz, &m, &m);
    }
    MI_Copy36B(&m, slot + 0x88);
}
