/* ov022: send the record for a point one unit behind the actor.
 *
 * The point is the actor's own position raised by a fixed amount and walked one
 * unit along its facing negated and flattened, so it lands behind the actor at
 * roughly chest height however the ground slopes.
 *
 * The record carries that point, a unit scale, and the facing with its bias
 * already removed -- the same value the table was indexed with, so the receiver
 * does not have to unbias it again.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

#define ANGLE_BIAS 0x8000
#define ANGLE_SHIFT 4
#define POINT_RAISE 0xf00
#define UNIT_SCALE 0x1000
#define RECORD_KIND 2
#define RECORD_ARG 7

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022ActorNode */
struct ActorNode {
    u8 pad00[0x80];
    u16 nAngle;                  /* 0x80 */
    u8 pad82[2];
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[0x20];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad0024[0x468];
    struct VecFx32 vecPos;       /* 0x048c */
};

/* kFxSinCosTable, walked as one flat array of halfwords */
extern s16 data_0203d210[];

extern void VEC_Add(const struct VecFx32 *pA, const struct VecFx32 *pB,
                    struct VecFx32 *pOut);
/* Ov022_MarshalNetworkRecord */
extern void func_ov022_020ad208(struct Actor *pActor, int nKind,
                                struct VecFx32 *pAt, int nScale, u16 nAngle,
                                int nArg);

void func_ov022_0209ccf4(struct Actor *pActor)
{
    struct VecFx32 vecDir;
    struct VecFx32 vecAt;
    u16 nAngle;
    int nIndex;

    vecAt = pActor->vecPos;
    nAngle = (u16)(pActor->pNode->nAngle - ANGLE_BIAS);
    nIndex = nAngle >> ANGLE_SHIFT;
    vecDir.x = -data_0203d210[nIndex * 2];
    vecDir.y = 0;
    vecDir.z = -data_0203d210[nIndex * 2 + 1];
    vecAt.y = vecAt.y + POINT_RAISE;
    VEC_Add(&vecAt, &vecDir, &vecAt);
    func_ov022_020ad208(pActor, RECORD_KIND, &vecAt, UNIT_SCALE, nAngle,
                        RECORD_ARG);
}
