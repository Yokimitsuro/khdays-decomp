/* ov022: hand a pair of ids to the sound side, one way or the other.
 *
 * A positive direction starts them, a negative one stops them, and zero does
 * nothing at all. Either way the pair is put on the stack first, because both
 * of the calls that take it want its address.
 *
 * The sound side is only told when this object owns the active channel. On the
 * stopping path there is one more turn: if the event flag is set the stop gets
 * its own handler, otherwise the default one runs with zero.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define STOP_EVENT_ID 0x37c5

struct Owner {
    u8 pad00[8];
    u8 nChannel;                 /* 0x08 */
    u8 nHandle;                  /* 0x09 */
};

extern int func_02030788(void);
extern void func_ov002_0205e358(u16 nFirst, u16 nSecond);
extern void func_ov002_0205e3e4(u16 nFirst, u16 nSecond);
extern void func_ov002_0205e448(void);
extern void func_ov002_02056d90(int nMode);
extern int func_020235d0(int nEvent, int nFlag);
extern void func_020359b4(int nHandle, u16 *pPair);
extern void func_020359f0(int nHandle, u16 *pPair);

void func_ov022_020aa824(struct Owner *pOwner, int nSecond, int nFirst,
                         int nDir)
{
    u16 aPair[2];

    aPair[1] = (u16)nSecond;
    aPair[0] = (u16)nFirst;
    if (nDir > 0) {
        if (pOwner->nChannel == func_02030788()) {
            func_ov002_0205e358(nFirst, nSecond);
        }
        func_020359b4(pOwner->nHandle, aPair);
    } else if (nDir < 0) {
        if (pOwner->nChannel == func_02030788()) {
            func_ov002_0205e3e4(nFirst, nSecond);
            if (func_020235d0(STOP_EVENT_ID, 1) == 0) {
                func_ov002_02056d90(0);
            } else {
                func_ov002_0205e448();
            }
        }
        func_020359f0(pOwner->nHandle, aPair);
    }
}
