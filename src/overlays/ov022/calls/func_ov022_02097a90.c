/* ov022: start the actor's third effect slot at its own feet, sized by model.
 *
 * Only ever starts one: a slot already holding anything other than the free
 * value is left alone, and so is an actor with no context for it.
 *
 * The effect goes exactly where the actor is, and the only thing that varies is
 * how big it is. Most models get the largest size, seven of the twenty-two get
 * the middle one, and three plus anything off the end of the table keep the
 * smallest.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SLOT_FREE (-1)
#define SIZE_SMALL 0x1000
#define SIZE_MEDIUM 0x1800
#define SIZE_LARGE 0x2000

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[0xc];
    int nModelId;                /* 0x000c */
    u8 pad0010[0x47c];
    struct VecFx32 vecPos;       /* 0x048c */
    u8 pad0498[0x328];
    int nEffectC;                /* 0x07c0 */
    int nEffectD;                /* 0x07c4 */
};

extern int func_ov022_020893f4(int nContext, struct VecFx32 *pAt, int nValue);
extern void func_ov022_0208956c(int nContext, int nSlot, int nValue);

void func_ov022_02097a90(struct Actor *pActor)
{
    struct VecFx32 vecAt;
    int nSize;

    if (pActor->nEffectC == 0) {
        return;
    }
    if (pActor->nEffectD != SLOT_FREE) {
        return;
    }
    vecAt = pActor->vecPos;
    nSize = SIZE_SMALL;
    pActor->nEffectD = func_ov022_020893f4(pActor->nEffectC, &vecAt, 0);
    switch (pActor->nModelId) {
    case 0:
    case 5:
    case 11:
    case 14:
    case 18:
    case 20:
    case 21:
        nSize = SIZE_MEDIUM;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 12:
    case 13:
    case 15:
        nSize = SIZE_LARGE;
        break;
    }
    func_ov022_0208956c(pActor->nEffectC, pActor->nEffectD, nSize);
}
