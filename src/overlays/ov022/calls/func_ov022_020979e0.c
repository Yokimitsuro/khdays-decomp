/* ov022: move the actor's held effect slot to keep facing the camera.
 *
 * The companion to the step that creates the slot. This one only runs while a
 * slot is actually held, and it moves rather than places: the actor's anchor is
 * raised the same amount, the direction to the cached camera position is
 * normalised and then flattened, and the anchor is walked one unit along the
 * result. Dropping the vertical keeps the effect level with the actor however
 * far above or below the camera sits.
 *
 * The slot is asked afterwards whether its record has run out, and released
 * when it has.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define ANCHOR_RAISE 0x200
#define ANCHOR_REACH 0x800

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[0x7b8];
    int nEffectA;                /* 0x07b8 */
    int nEffectB;                /* 0x07bc */
};

/* gCameraCachePos */
extern struct VecFx32 data_020475ac;

extern void func_ov022_020ad44c(struct VecFx32 *pOut, struct Actor *pActor);
extern void func_ov022_02089478(int nContext, int nSlot, struct VecFx32 *pAt);
extern int func_ov022_020894f8(int nContext, int nSlot);
extern void VEC_Subtract(const struct VecFx32 *pA, const struct VecFx32 *pB,
                         struct VecFx32 *pOut);
extern void VEC_MultAdd(int nFactor, const struct VecFx32 *pStep,
                        const struct VecFx32 *pFrom, struct VecFx32 *pOut);
/* VEC_Normalize */
extern int func_01ff8d18(const struct VecFx32 *pSrc, struct VecFx32 *pDst);

void func_ov022_020979e0(struct Actor *pActor)
{
    struct VecFx32 vecAt;
    struct VecFx32 vecDir;

    if (pActor->nEffectA == 0) {
        return;
    }
    if (pActor->nEffectB < 0) {
        return;
    }
    func_ov022_020ad44c(&vecAt, pActor);
    vecAt.y = vecAt.y + ANCHOR_RAISE;
    VEC_Subtract(&data_020475ac, &vecAt, &vecDir);
    func_01ff8d18(&vecDir, &vecDir);
    vecDir.y = 0;
    VEC_MultAdd(ANCHOR_REACH, &vecDir, &vecAt, &vecAt);
    func_ov022_02089478(pActor->nEffectA, pActor->nEffectB, &vecAt);
    if (func_ov022_020894f8(pActor->nEffectA, pActor->nEffectB) != 0) {
        pActor->nEffectB = -1;
    }
}
