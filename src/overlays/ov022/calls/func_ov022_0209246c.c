/* Ov022_SendAimMessage -- pack an aim record into a gate 10 message.
 *
 * Nothing is sent unless the session is up. The record's position and its two
 * halfwords go across whole; the rest is one packed word: the record's kind and
 * sub-kind, the slot the caller names, and a flag pair. The angle and the range
 * are only worth sending when the first flag is set, so they are written after
 * it and only then.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct AimRecord {
    u8 nKind;                    /* 0x00 */
    u8 pad001[3];
    struct VecFx32 vecPos;       /* 0x04 */
    short nField10;              /* 0x10 */
    short nField12;              /* 0x12 */
    u8 nSub;                     /* 0x14 */
    u8 nFlags;                   /* 0x15 */
    u16 nAngle;                  /* 0x16 */
    u16 nRange;                  /* 0x18 */
};

struct AimMessage {
    struct VecFx32 vecPos;       /* 0x00 */
    short nField10;              /* 0x0c */
    short nField12;              /* 0x0e */
    u32 nKind : 2;               /* 0x10 bits 0 and 1 */
    u32 nSub : 3;                /* bits 2 to 4 */
    u32 nSlot : 4;               /* bits 5 to 8 */
    u32 bAimed : 1;              /* bit 9 */
    u32 bFlag1 : 1;              /* bit 10 */
    u32 nAngle : 12;             /* bits 11 to 22 */
    u32 nRange : 8;              /* bits 23 to 30 */
    u32 nSpare : 1;              /* bit 31 */
};

extern int func_02030694(void);
extern void func_02031258(int nGate, void *pMessage, int nSize);

#define MESSAGE_GATE 10

void func_ov022_0209246c(int nArg0, int nSlot, const struct AimRecord *pSrc)
{
    struct AimMessage msg;

    if (func_02030694() == 0) {
        return;
    }
    msg.vecPos = pSrc->vecPos;
    msg.nField10 = pSrc->nField10;
    msg.nField12 = pSrc->nField12;
    msg.nKind = pSrc->nKind;
    msg.nSub = pSrc->nSub;
    msg.nSlot = nSlot;
    msg.bAimed = (pSrc->nFlags & 1) != 0;
    if (msg.bAimed) {
        msg.nAngle = pSrc->nAngle;
        msg.nRange = pSrc->nRange;
    }
    msg.bFlag1 = (pSrc->nFlags & 2) != 0;
    func_02031258(MESSAGE_GATE, &msg, 0x14);
}
