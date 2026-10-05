/* Moves the two trail nodes along one joint (offsets 0x800/0x1000) and a third node to another
 * joint. */

#include "game/engine.h"

extern int VEC_Add();
extern int NNS_G3dGetResultMtx();
extern int Srt_SetTranslation();

struct A {
    char pad88[0x88];
    char *p88;
};

struct B {
    char pad[0x3b4];
    int f3b4;
    int f3b8;
};

void Ov248_SyncEffectNodesToJoints(struct A *a0, struct B *sl) {
    int buf4[3];
    int loc[9];
    int work[3];
    int i;

    if (NNS_G3dGetResultMtx(a0->p88 + 0x20, loc, 0, sl->f3b4) != 0) {
        char *p;
        Srt_SetTranslation((char *)sl + 0x3e0, buf4);

        p = (char *)sl + 0xc + 0x400;
        for (i = 0; i < 2; i++) {
            work[0] = 0;
            work[1] = 0;
            work[2] = (i == 0) ? 0x800 : 0x1000;
            Vec3TransformViaTempMtx(work, (char *)sl + 0xa0, work);
            VEC_Add(work, buf4, work);
            Srt_SetTranslation(p, work);
            p += 0x2c;
        }
    }

    if (NNS_G3dGetResultMtx(a0->p88 + 0x20, loc, 0, sl->f3b8) == 0)
        return;

    Srt_SetTranslation((char *)sl + 0x64 + 0x400, buf4);
}
