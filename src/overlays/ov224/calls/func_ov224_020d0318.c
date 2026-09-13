/* func_ov224_020d0318 -- effect command hook (byte-identical in ov221 /
 * ov222 / ov223 / ov224).  A type-5 command carries three big-endian
 * signed 24-bit coordinates in bytes 5 .. 0xd, unpacked through a packed
 * word union into a translation that seeds a fresh transform (0203c960 /
 * 0203ca30).  Byte 3 picks the effect slot (+0x424 + 8 * slot: resource,
 * handle): slots 0 / 5 / 6 spawn kind 5 at the transform (020c0794),
 * slots 1 / 3 kind 5 on the actor's transform (+0xa0) with byte 4 and the
 * flag 0 / 1 (020c09a0), slot 4 with the flag set when byte 4 is zero,
 * slots 2 / 7 kind 0x15, slot 9 sets the pose (020c0b14 with byte 4 below
 * 4, else -1), slot 10 finishes the effect of slot byte 4 (0203c650) and
 * clears its handle; slot 8 does nothing.  Every command then reaches
 * the base hook (020c7500).  Codegen: the cases are written in the ROM's
 * body order 0, 1, 3, 4, 2 / 7 (shared), 5, 6, 8, 9, 10 (0 / 5 / 6 are
 * three copies); the unpack and the transform are built before the
 * switch; byte 4 is always an unsigned read.
 */
typedef unsigned char u8;

typedef struct SrtTransform {
    int w[11];
} SrtTransform;

typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

typedef struct EffectSlot {
    int nResource;            /* 0x00 */
    int hEffect;              /* 0x04 */
} EffectSlot;

typedef struct EffectActor {
    u8  pad_000[0x3c];
    int hList;                /* 0x03c */
    u8  pad_040[0xa0 - 0x40];
    u8  srt[0x424 - 0xa0];    /* 0x0a0 */
    EffectSlot aSlot[11];     /* 0x424 */
} EffectActor;

#define KIND_EFFECT   5
#define KIND_EFFECT_B 0x15

extern void func_0203c960(SrtTransform *pTransform);                   /* Srt_Init */
extern void func_0203ca30(SrtTransform *pTransform, const Vec3 *pPos);  /* Srt_SetTranslation */
extern int  func_ov107_020c0794(int hList, int nResource, int nKind, int nZero, SrtTransform *pTransform);
extern int  func_ov107_020c09a0(int hList, int nResource, int nKind, void *pSrt, int nParam, int nFlag);
extern void func_ov107_020c0b14(EffectActor *pActor, int nPose);
extern void func_0203c650(int hList, int hEffect);                      /* TaskList_FinishByTag */
extern void func_ov107_020c7500(EffectActor *pActor, u8 *pCommand, int nArg);

void func_ov224_020d0318(EffectActor *pActor, u8 *pCommand, int nArg)
{
    SrtTransform transform;
    Vec3 translation;
    union {
        int words[3];
        u8 bytes[12];
    } packed;

    if (pCommand[2] == 5) {
        packed.bytes[3] = pCommand[5];
        packed.bytes[2] = pCommand[6];
        packed.bytes[1] = pCommand[7];
        translation.x = packed.words[0] >> 8;

        packed.bytes[7] = pCommand[8];
        packed.bytes[6] = pCommand[9];
        packed.bytes[5] = pCommand[0xa];
        translation.y = packed.words[1] >> 8;

        packed.bytes[11] = pCommand[0xb];
        packed.bytes[10] = pCommand[0xc];
        packed.bytes[9] = pCommand[0xd];
        translation.z = packed.words[2] >> 8;

        func_0203c960(&transform);
        func_0203ca30(&transform, &translation);

        switch (pCommand[3]) {
        case 0:
            pActor->aSlot[pCommand[3]].hEffect =
                func_ov107_020c0794(pActor->hList, pActor->aSlot[pCommand[3]].nResource, KIND_EFFECT, 0, &transform);
            break;
        case 1:
            pActor->aSlot[pCommand[3]].hEffect =
                func_ov107_020c09a0(pActor->hList, pActor->aSlot[pCommand[3]].nResource, KIND_EFFECT, pActor->srt, pCommand[4], 0);
            break;
        case 3:
            pActor->aSlot[pCommand[3]].hEffect =
                func_ov107_020c09a0(pActor->hList, pActor->aSlot[pCommand[3]].nResource, KIND_EFFECT, pActor->srt, pCommand[4], 1);
            break;
        case 4:
            pActor->aSlot[pCommand[3]].hEffect =
                func_ov107_020c09a0(pActor->hList, pActor->aSlot[pCommand[3]].nResource, KIND_EFFECT, pActor->srt, pCommand[4], pCommand[4] == 0);
            break;
        case 2:
        case 7:
            pActor->aSlot[pCommand[3]].hEffect =
                func_ov107_020c09a0(pActor->hList, pActor->aSlot[pCommand[3]].nResource, KIND_EFFECT_B, pActor->srt, pCommand[4], 0);
            break;
        case 5:
            pActor->aSlot[pCommand[3]].hEffect =
                func_ov107_020c0794(pActor->hList, pActor->aSlot[pCommand[3]].nResource, KIND_EFFECT, 0, &transform);
            break;
        case 6:
            pActor->aSlot[pCommand[3]].hEffect =
                func_ov107_020c0794(pActor->hList, pActor->aSlot[pCommand[3]].nResource, KIND_EFFECT, 0, &transform);
            break;
        case 8:
            break;
        case 9:
            func_ov107_020c0b14(pActor, pCommand[4] < 4 ? pCommand[4] : -1);
            break;
        case 10:
            if (pActor->aSlot[pCommand[4]].hEffect != 0) {
                func_0203c650(pActor->hList, pActor->aSlot[pCommand[4]].hEffect);
                pActor->aSlot[pCommand[4]].hEffect = 0;
            }
            break;
        }
    }
    func_ov107_020c7500(pActor, pCommand, nArg);
}
