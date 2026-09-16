/* func_ov016_02080a14 -- Ov016_BreakableHit: hit handler of the breakable.  Unless the
 * "broken" bit (bit 1 of the breakable's GameState field) is already set, it queues a kind-6
 * message on the piece (ov002 020766e0) carrying the attacker byte of the hit record (+0xc);
 * when the message goes out the broken bit is set (the field's bits 1..15 shifted back into
 * place), the 0x1c-byte hit record is kept at +0x2c8 and the drop is marked pending (+0x2bd),
 * answering 0.  Otherwise the hit is refused with 8. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov016HitRecord {
    u8 pad_00[0xc];
    u8 nAttacker;             /* 0x0c */
    u8 pad_0d[0x1c - 0xd];
} Ov016HitRecord;

typedef struct Ov016BrokenMessage {
    u8 pad_00[4];
    u16 nAttacker;            /* 0x04 */
} Ov016BrokenMessage;

typedef struct Ov016Breakable {
    u8 pad_000[0x14];
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8  pad_017[0x2bd - 0x17];
    u8  bDropPending;         /* 0x2bd */
    u8  pad_2be[0x2c8 - 0x2be];
    Ov016HitRecord hit;       /* 0x2c8 */
} Ov016Breakable;

extern int  func_020235d0(u16 nField, u8 nBit);                      /* GameState_GetField */
extern void func_020235e8(u16 nField, u8 nBit, u16 nValue);          /* GameState_SetField */
extern int  func_ov002_020766e0(void *pPiece, void *pMessage, int nKind); /* queue a message on the piece */
extern void MI_CpuCopy8(const void *pSrc, void *pDst, u32 nSize);

int func_ov016_02080a14(Ov016Breakable *pSelf, Ov016HitRecord *pHit)
{
    Ov016BrokenMessage message;
    u32 nBits;

    nBits = (u16)((func_020235d0(pSelf->nStateField, pSelf->nStateBit) & 0xfffe) >> 1);
    if ((nBits & 1) == 0) {
        message.nAttacker = pHit->nAttacker;
        if (func_ov002_020766e0(pSelf, &message, 6) != 0) {
            func_020235e8(pSelf->nStateField, pSelf->nStateBit,
                          (func_020235d0(pSelf->nStateField, pSelf->nStateBit) & 0xffff0001) | ((u16)(nBits | 1) << 1));
            MI_CpuCopy8(pHit, &pSelf->hit, 0x1c);
            pSelf->bDropPending = 1;
            return 0;
        }
    }
    return 8;
}
