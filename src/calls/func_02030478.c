#pragma thumb on
/* func_02030478 -- set up the shared session context, MAIN. The context lives at the base of the
 * current root heap and is published in data_0204c228. It copies the session id from the source
 * block (CARDi_GetRomAccessor_0x020315f4 is misnamed); in a connected session (func_02030670) it
 * takes the member mask (+0xc), registers the source's +0x8 (func_02023e34) and stores the own
 * index (+0x20), otherwise the mask is just member 0. A 32-bit LCG (MATH_InitRand32) is seeded
 * from func_02023eb4(-1), two handles are opened (func_02023930), the member mask is compacted
 * (+0x6) and the own position among the members is recorded (+0x22). Returns the session
 * callback func_02030570. */
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

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
    int pad04;
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
extern SessionSource *CARDi_GetRomAccessor_0x020315f4(void);
extern int func_02030670(void);
extern void func_02023e34(int a, int b, int c);
extern u16 OS_IsTickAvailable_0x01ff8138(void);
extern u32 func_02023eb4(int mode);
extern void *func_02023930(const void *desc, int flags);
extern int OS_IsTickAvailable(void);
extern void func_02030570(void);
extern SessionCtx *data_0204c228;
extern const char data_02042990[];
extern const char data_020429a4[];

void *func_02030478(void)
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
    src = CARDi_GetRomAccessor_0x020315f4();
    ctx->id = src->id;
    if (func_02030670() != 0) {
        ctx->memberMask = src->memberMask;
        func_02023e34(src->key, src->key, 0);
        ctx->selfIndex = OS_IsTickAvailable_0x01ff8138();
    } else {
        ctx->memberMask = 1;
    }
    MATH_InitRand32(&ctx->rand, func_02023eb4(-1));
    ctx->handleA = func_02023930(data_02042990, 0);
    ctx->handleB = func_02023930(data_020429a4, 0);
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
    self = OS_IsTickAvailable();
    for (j = 0; j < 4; j++) {
        if ((1 << j) & ctx->memberMask) {
            if (self == j) {
                ctx->selfPos = pos;
                break;
            }
            pos++;
        }
    }
    return func_02030570;
}
