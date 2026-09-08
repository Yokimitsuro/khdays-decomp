/* Ov022_BroadcastCue -- tell everything that cares where a cue happened.
 *
 * The active entry gets it first, but only while it is the one the caller
 * names: a downed entry that still carries the reply flag answers with the cue
 * kind, and the point and the angle always go in. A live record for the same
 * entry is updated too.
 *
 * The shared packet, if there is one, keeps the local player, the cue kind, the
 * point and the angle, and is posted on gate 2 once the session is up and this
 * machine is not the host.
 */

typedef unsigned char u8;
typedef unsigned short u16;

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct Entry {
    unsigned long long nFlags;   /* 0x00, a 64 bit flag word */
    u8 pad0008[0xa];
    u16 nHp;                     /* 0x12 */
};

struct CueBody {
    struct VecFx32 vecPos;       /* 0x00 */
    u16 nPlayer : 3;             /* 0x0c bits 0 to 2 */
    u16 nKind : 13;              /* bits 3 to 15 */
    short nAngle;                /* 0x0e */
};

struct CuePacket {
    int nField00;                /* 0x00 */
    struct CueBody body;         /* 0x04 */
};

extern struct CuePacket *data_ov022_020b2ea4;

extern int func_ov022_02083f0c(void);
extern u16 func_01fffe14(void);
extern struct Entry *func_01fffde0(unsigned int nState);
extern int func_02030788(void);
extern void func_ov022_02088428(unsigned int nState, int nKind);
extern void func_ov022_02088218(unsigned int nState, struct VecFx32 *pPos);
extern void func_ov022_02088280(unsigned int nState, int nAngle);
extern int func_ov002_0204cb18(int nRecord);
extern void func_ov002_0204ce14(int nRecord, int nAngle);
extern void func_ov002_0204cce0(int nRecord, struct VecFx32 *pPos);
extern int func_ov002_0206aaa0(void);
extern void func_02031384(int nGate, void *pBody, int nSize);

#define ENTRY_REPLIES 0x100
#define CUE_GATE 2

void func_ov022_02089e90(unsigned int nOwner, int nKind, struct VecFx32 *pPos,
                         int nAngle)
{
    struct CueBody *pBody;
    struct Entry *pEntry;
    unsigned int nState;
    int nRecord;
    struct CuePacket *pPacket;

    pPacket = data_ov022_020b2ea4;
    nRecord = func_ov022_02083f0c();
    nState = func_01fffe14();
    pEntry = func_01fffde0(nState);
    if (nState == nOwner) {
        if (func_02030788() == 0 && pEntry->nHp == 0
            && (pEntry->nFlags & ENTRY_REPLIES) != 0) {
            func_ov022_02088428(nState, nKind);
        }
        func_ov022_02088218(nState, pPos);
        func_ov022_02088280(nState, nAngle);
    }
    if (nRecord != -1 && func_ov002_0204cb18(nRecord) != 0 && nState == nOwner) {
        func_ov002_0204ce14(nRecord, nAngle);
        func_ov002_0204cce0(nRecord, pPos);
    }
    if (pPacket == 0) {
        return;
    }
    pBody = &pPacket->body;
    pBody->nPlayer = func_02030788();
    pBody->nKind = nKind;
    pBody->vecPos = *pPos;
    pBody->nAngle = (short)nAngle;
    if (func_ov002_0206aaa0() != 0 && func_02030788() != 0) {
        func_02031384(CUE_GATE, pBody, 0x10);
    }
}
