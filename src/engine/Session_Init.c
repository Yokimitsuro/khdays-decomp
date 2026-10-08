#pragma thumb on
/* Session_Init -- set up the shared session context, MAIN. The context lives at the base of the
 * current root heap and is published in data_0204c228. It copies the session id from the source
 * block (Session_GetSetup is misnamed); in a connected session (Session_IsActive) it
 * takes the member mask (+0xc), registers the source's +0x8 (Rng_Seed) and stores the own
 * index (+0x20), otherwise the mask is just member 0. A 32-bit LCG (MATH_InitRand32) is seeded
 * from RandNextScaled(-1), two handles are opened (InstantiateClass), the member mask is compacted
 * (+0x6) and the own position among the members is recorded (+0x22). Returns the session
 * callback Session_CheckSceneLoop. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct MATHRandContext32 {
    u64 x;
    u64 mul;
    u64 add;
} MATHRandContext32;

static inline void MATH_InitRand32(MATHRandContext32 *context, u64 seed)
{
    context->x = seed;
    context->mul = (0x5d588b65ULL << 32) + 0x6c078965ULL;
    context->add = 0x269ec3ULL;
}

typedef struct SessionSource {
    int id;                             /* +0x00 */
    int slotCount;
    int key;                            /* +0x08 */
    u16 memberMask;                     /* +0x0c */
} SessionSource;

typedef struct SessionCtx {
    int id;                             /* +0x00 */
    u16 memberMask;                     /* +0x04 */
    u16 packedMask;                     /* +0x06 */
    MATHRandContext32 rand;             /* +0x08 */
    u16 selfIndex;                      /* +0x20 */
    u16 selfPos;                        /* +0x22 */
    void *handleA;                      /* +0x24 */
    void *handleB;                      /* +0x28 */
} SessionCtx;

extern SessionCtx *NNSi_FndGetCurrentRootHeap(void);
extern unsigned short WH_GetBitmap(void);
extern void *InstantiateClass(const void *desc, int flags);
extern unsigned short WH_GetCurrentAid(void);
extern SessionCtx *data_0204c228;
extern const char data_02042990[];
extern const char data_020429a4[];

void *Session_Init(void)
{
    SessionCtx *ctx = NNSi_FndGetCurrentRootHeap();
    SessionSource *src;
    int j;
    int i;
    u16 bits;
    u16 k;
    int self;
    int pos;

    data_0204c228 = ctx;
    src = (SessionSource *)Session_GetSetup();
    ctx->id = src->id;
    if (Session_IsActive() != 0) {
        ctx->memberMask = src->memberMask;
        Rng_Seed(src->key, src->key, 0);
        ctx->selfIndex = WH_GetBitmap();
    } else {
        ctx->memberMask = 1;
    }
    MATH_InitRand32(&ctx->rand, RandNextScaled(-1));
    ctx->handleA = InstantiateClass(data_02042990, 0);
    ctx->handleB = InstantiateClass(data_020429a4, 0);
    ctx->packedMask = ctx->memberMask;
    k = bits = 0;
    for (i = 0; i < 4; i++) {
        if ((1 << i) & ctx->memberMask) {
            bits |= 1 << k;
            k++;
        }
    }
    ctx->packedMask = bits;
    pos = 0;
    self = WH_GetCurrentAid();
    for (j = 0; j < 4; j++) {
        if ((1 << j) & ctx->memberMask) {
            if (self == j) {
                ctx->selfPos = pos;
                break;
            }
            pos++;
        }
    }
    return Session_CheckSceneLoop;
}
