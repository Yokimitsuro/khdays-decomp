/* ov022: keep the actor's second effect slot alive, re-placing it toward the
 * camera whenever it is not.
 *
 * A slot that is still held is asked whether its record has run out; one that
 * has is thrown away so the same pass can start a fresh one.
 *
 * A fresh one is placed one unit from the actor toward the camera: the actor's
 * anchor is raised a little, the direction from there to the cached camera
 * position is normalised, and the anchor is walked along it. A request the
 * dispatcher refuses comes back negative and is stored but not used further.
 *
 * A slot that is still running is stepped instead of being re-placed.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define ANCHOR_RAISE 0x200
#define ANCHOR_REACH 0x800
#define EMIT_PARAM 0xb33

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
extern int func_ov022_020894f8(int nContext, int nSlot);
extern int func_ov022_020893f4(int nContext, struct VecFx32 *pAt,
                               int nValue);
extern void func_ov022_0208956c(int nContext, int nSlot, int nValue);
extern void func_ov022_020894cc(int nContext, int nSlot, int nValue);
extern void VEC_Subtract(const struct VecFx32 *pA, const struct VecFx32 *pB,
                         struct VecFx32 *pOut);
extern void VEC_MultAdd(int nFactor, const struct VecFx32 *pStep,
                        const struct VecFx32 *pFrom, struct VecFx32 *pOut);
/* VEC_Normalize */
extern int func_01ff8d18(const struct VecFx32 *pSrc, struct VecFx32 *pDst);

void func_ov022_02097904(struct Actor *pActor)
{
    struct VecFx32 vecAt;
    struct VecFx32 vecDir;

    if (pActor->nEffectA == 0) {
        return;
    }
    if (pActor->nEffectB >= 0) {
        if (func_ov022_020894f8(pActor->nEffectA, pActor->nEffectB) != 0) {
            pActor->nEffectB = -1;
        }
    }
    if (pActor->nEffectB < 0) {
        func_ov022_020ad44c(&vecAt, pActor);
        vecAt.y = vecAt.y + ANCHOR_RAISE;
        VEC_Subtract(&data_020475ac, &vecAt, &vecDir);
        func_01ff8d18(&vecDir, &vecDir);
        VEC_MultAdd(ANCHOR_REACH, &vecDir, &vecAt, &vecAt);
        pActor->nEffectB = func_ov022_020893f4(pActor->nEffectA, &vecAt, 0);
        if (pActor->nEffectB < 0) {
            return;
        }
        func_ov022_0208956c(pActor->nEffectA, pActor->nEffectB, EMIT_PARAM);
    } else {
        func_ov022_020894cc(pActor->nEffectA, pActor->nEffectB, 0);
    }
}
