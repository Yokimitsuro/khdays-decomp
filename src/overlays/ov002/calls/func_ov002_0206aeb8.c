typedef unsigned long long u64;

extern char *data_ov002_0207fa00;

extern void func_0202fcb8(int nId, void *pRecord);
extern int func_02020a9c(void);
extern void func_ov002_02056edc(void *pRecord, u64 nScaled, int nSlot, int nFlags);
extern void func_ov002_02057684(void *pRecord);

/* Post a record for the given id. A non-negative amount is scaled and sent on
 * the normal path; a negative one falls back to the plain post, which is
 * suppressed in mode 0x2a. Nothing happens while the channel is unset. */
void func_ov002_0206aeb8(int nId, int nAmount, int nSlot, int nFlags)
{
    char stk[0x100];

    if (*(int *)(data_ov002_0207fa00 + 0x8c94) == -1) {
        return;
    }

    func_0202fcb8(nId, stk);

    if (nAmount >= 0) {
        func_ov002_02056edc(stk, (u64)((long long)nAmount * 0x82ea) >> 6,
                            nSlot, nFlags);
        return;
    }

    if (func_02020a9c() == 0x2a) {
        return;
    }

    func_ov002_02057684(stk);
}
