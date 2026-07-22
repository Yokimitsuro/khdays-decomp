/* Drop the key-sharing session, if one is up: end it at the wireless layer, then
 * clear the handle, reset the phase to 0 and blank the peer field. */
extern void WM_EndKeySharing_0x02023ad0(int handle);

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

void func_ov002_02069844(void) {
    Ov002SessionBlock *session = &data_ov002_0207fa00->session;

    if (session->nHandle == -1) {
        return;
    }

    WM_EndKeySharing_0x02023ad0(session->nHandle);

    session->nHandle = -1;
    session->nPhase = 0;
    session->nPeer = -1;
}
