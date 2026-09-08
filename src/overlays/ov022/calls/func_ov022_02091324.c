/* Ov022_SendPlacementMessage -- pack a placement record into a gate message.
 *
 * The record's position and its three halfwords go across whole; everything
 * else is squeezed into three bytes of bit fields, two of them from the record
 * and one from the owner. The message goes out on gate 9 as 0x18 bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

struct Owner {
    u8 pad000[9];
    u8 nKind;                    /* 0x09 */
    u8 pad00a[0x5c];
    short nGroup;                /* 0x66 */
};

struct Words {
    u16 nWord0;
    u16 nWord1;
    u16 nWord2;
};

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct Placement {
    struct VecFx32 vecPos;       /* 0x00 */
    struct Words words;          /* 0x0c */
    short nField12;              /* 0x12 */
    int nField14;                /* 0x14 */
    int nField18;                /* 0x18 */
    int nField1c;                /* 0x1c */
    int nField20;                /* 0x20 */
    int nField24;                /* 0x24 */
    int nField28;                /* 0x28 */
};

struct Message {
    u8 nZero : 2;                /* 0x00 bits 0 and 1 */
    u8 nKind : 2;                /* bits 2 and 3 */
    u8 nGroup : 3;               /* bits 4 to 6 */
    u8 nSpare : 1;
    u8 nField14 : 3;             /* 0x01 bits 0 to 2 */
    u8 nField18 : 3;             /* bits 3 to 5 */
    u8 nField1c : 2;             /* bits 6 and 7 */
    short nField12;              /* 0x02 */
    struct VecFx32 vecPos;       /* 0x04 */
    struct Words words;          /* 0x10 */
    u8 nField20 : 3;             /* 0x16 bits 0 to 2 */
    u8 nField28 : 3;             /* bits 3 to 5 */
    u8 nField24 : 2;             /* bits 6 and 7 */
    u8 pad17;
};

extern void func_02031258(int nGate, void *pMessage, int nSize);

#define MESSAGE_GATE 9

void func_ov022_02091324(struct Owner *pOwner, const struct Placement *pSrc)
{
    struct Message msg;

    msg.nZero = 0;
    msg.nKind = pOwner->nKind;
    msg.nGroup = (u8)pOwner->nGroup;
    msg.nField14 = pSrc->nField14;
    msg.nField18 = pSrc->nField18;
    msg.nField1c = pSrc->nField1c;
    msg.vecPos = pSrc->vecPos;
    msg.words = pSrc->words;
    msg.nField20 = pSrc->nField20;
    msg.nField12 = pSrc->nField12;
    msg.nField28 = pSrc->nField28;
    msg.nField24 = pSrc->nField24;
    func_02031258(MESSAGE_GATE, &msg, 0x18);
}
