/* Step one roster slot's release, and say whether it is finished.
 *
 * A slot index of -1 means the currently active slot, which comes from
 * func_01fffe14. Nothing happens while the session's leading word is -1 or while
 * the party entry for the slot does not exist; both answer done.
 *
 * For the ACTIVE slot the phase at session+0xc0 drives it. Phase 2 hands the
 * recorded peer back: it releases the world's music, clears the session and
 * forgets the peer, then asks whether that peer still owns a piece. If it does,
 * the entry is cleaned up, the session parks in phase 6 remembering the peer,
 * and the answer is not-yet. Phase 6 waits on that owner, reading the four-bit
 * field at owner+0xf8, and clears the session once it reads zero. Any other
 * phase falls through unchanged. A non-active slot is simply handed back and
 * cleaned up, always answering done.
 *
 * Codegen notes, all measured. The two zeroes in phase 6 live in two registers
 * with a copy between them, which only happens when their ranges interfere, so
 * the flag is set to 1 BEFORE the session store and the store cannot borrow the
 * flag's register; writing the store first lets mwcc coalesce them and loses the
 * copy. The lookup result must be a named local so the flag's clear is sequenced
 * after the call and lands in the ROM's scheduling slot -- every spelling that
 * clears the flag before the call schedules it ahead of the branch instead, and
 * every spelling that holds the PHASE in a local instead costs four bytes by
 * pushing the session offset back to the literal pool. The phase is a signed
 * four-bit bitfield, which is what emits the lsls/asrs pair rather than a mask.
 * The -1 stores need no constant of their own: mwcc derives them from whichever
 * constant register is live, which is why phase 2 subtracts one from its zero
 * and phase 6 subtracts two from the flag's one.
 *
 * Ghidra carries this as Ov002_StepRosterSlotRelease over Ov002SessionBlock and
 * Ov002Owner; it is the unwinding counterpart of Ov002_StepRosterSlotPhase.
 */

/* The object a roster slot owns; only its phase nibble is read here. */
typedef struct Ov002Owner {
    char pad0000[0xf8];
    signed int nPhase : 4;              /* +0x0f8, low nibble, signed */
} Ov002Owner;

/* The roster session block inside the root context. */
typedef struct Ov002SessionBlock {
    int nSessionToken;                  /* +0x000 */
    char pad0004[0xbc];
    int nPhase;                         /* +0x0c0 */
    int nPeer;                          /* +0x0c4 */
} Ov002SessionBlock;

extern char *data_ov002_0207fa00;

extern int func_01fffe14(void);
extern void *func_01fffde0(int nSlot);
extern int func_ov022_02088474(int nSlot);
extern void func_ov022_02087298(int nSlot);
extern void func_ov022_020883f4(int nSlot);
extern void func_ov002_0206d798(int nWorld);
extern Ov002Owner *func_ov002_02073880(int nPeer);

int func_ov002_0206b600(int nSlot)
{
    Ov002SessionBlock *pSession;
    int bDone;
    int nPeer;
    int nWorld;
    int nPhase;
    Ov002Owner *pOwner;

    bDone = 1;
    pSession = (Ov002SessionBlock *)(data_ov002_0207fa00 + 0x8bcc);
    if (nSlot == -1) {
        nSlot = func_01fffe14();
    }
    if (pSession->nSessionToken == -1) {
        return 1;
    }
    if (func_01fffde0(nSlot) == 0) {
        return 1;
    }

    if (nSlot == func_01fffe14()) {
        nPhase = pSession->nPhase;
        switch (nPhase) {
        case 2:
            nPeer = pSession->nPeer;
            nWorld = func_ov022_02088474(nSlot);
            func_ov022_02087298(nSlot);
            func_ov002_0206d798(nWorld);
            pSession->nPhase = 0;
            pSession->nPeer = -1;
            if (func_ov002_02073880(nPeer) != 0) {
                func_ov022_020883f4(nSlot);
                pSession->nPhase = 6;
                pSession->nPeer = nPeer;
                bDone = 0;
            }
            break;
        case 6:
            pOwner = func_ov002_02073880(pSession->nPeer);
            bDone = 0;
            if (pOwner->nPhase == 0) {
                bDone = 1;
                pSession->nPhase = 0;
                pSession->nPeer = -1;
            }
            break;
        }
    } else {
        nWorld = func_ov022_02088474(nSlot);
        func_ov022_02087298(nSlot);
        if (func_ov002_02073880(nWorld) != 0) {
            func_ov022_020883f4(nSlot);
        }
    }
    return bDone;
}
