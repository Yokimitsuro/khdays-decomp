/*
 * Ov002_SetPendingPeerNotice - raise one slot's pending peer notice.
 *
 * While a session is live and this machine is the host, the slot's notice byte
 * takes the caller's value in bit 0 and is marked pending with bit 7, and the
 * whole set is flushed straight away.  Off-session, or on any peer that is not
 * the host, the request is handed to the peer path instead.
 *
 * The clear and the set are two compound assignments on the array element
 * rather than one combined expression.  That is load-bearing: mwcc folds the
 * pair back into a single load/store but keeps the intermediate mask in its own
 * register, which is the extra scratch register the original spends here.  Any
 * single-expression spelling reuses one register too few and rotates the whole
 * block.
 *
 * ARM.
 */

typedef unsigned char u8;

typedef struct Ov002RootContext {
    char pad0000[0x8db7];
    u8 aPendingPeerNotice[4];       /* +0x8db7, one byte per slot */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

extern int func_02030670(void);                 /* a session is running */
extern int func_02030788(void);                 /* this machine's player index */
extern void func_ov002_0206dec4(void);          /* flush the pending notices */
extern void func_ov002_0206dfd8(unsigned int nSlot, int bValue);

void func_ov002_0206df6c(unsigned int nSlot, int bValue)
{
    Ov002RootContext *pRoot;

    pRoot = data_ov002_0207fa00;
    if (func_02030670() != 0 && func_02030788() == 0) {
        pRoot->aPendingPeerNotice[nSlot] &= 0xfe;
        pRoot->aPendingPeerNotice[nSlot] |= (bValue & 1) | 0x80;
        func_ov002_0206dec4();
    } else {
        func_ov002_0206dfd8(nSlot, bValue);
    }
}
