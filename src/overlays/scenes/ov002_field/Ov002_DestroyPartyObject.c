/* Destroy the party object of the roster block (+0x8bcc), if there is one: the instance of
 * ov022's party class that Ov002_AdvanceRosterSetup creates. Then mark it gone (-1), reset the
 * phase to 0 and clear the peer (-1). */
extern void VeneerTo_Obj_Destroy(int handle);

typedef struct {
    int nHandle;            /* +0 of the block, i.e. +0x8bcc */
    char pad0004[0xbc];
    int nPhase;             /* +0xc0 */
    int nPeer;              /* +0xc4 */
} Ov002SessionBlock;

typedef struct {
    char pad0000[0x8bcc];
    Ov002SessionBlock session;  /* +0x8bcc */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

void Ov002_DestroyPartyObject(void) {
    Ov002SessionBlock *session = &data_ov002_0207fa00->session;

    if (session->nHandle == -1) {
        return;
    }

    VeneerTo_Obj_Destroy(session->nHandle);

    session->nHandle = -1;
    session->nPhase = 0;
    session->nPeer = -1;
}
