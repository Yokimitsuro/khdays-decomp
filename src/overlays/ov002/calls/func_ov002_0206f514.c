typedef struct {
    int nFlags;                         /* +0x00, bit 1 armed, bit 2 busy */
    int nRate;                          /* +0x04 */
    int nPending;                       /* +0x08 */
} Ov002Session;

extern Ov002Session *data_ov002_0207fa08;

extern int func_02030694(void);
extern void func_ov002_0206f25c(void);

/* Set or clear the busy bit and notify, but only while the session is ready
 * and armed, and only when the bit actually changes. */
void func_ov002_0206f514(int bBusy)
{
    Ov002Session *pSession;
    int nFlags;

    pSession = data_ov002_0207fa08;

    if (func_02030694() == 0) {
        return;
    }

    nFlags = pSession->nFlags;
    if ((nFlags & 2) <= 0) {
        return;
    }

    if (bBusy != 0) {
        if ((nFlags & 4) != 0) {
            return;
        }
        pSession->nFlags = nFlags | 4;
    } else {
        if ((nFlags & 4) == 0) {
            return;
        }
        pSession->nFlags = nFlags & ~4;
    }

    func_ov002_0206f25c();
}
