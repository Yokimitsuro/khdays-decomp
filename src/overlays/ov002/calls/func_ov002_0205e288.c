/* Take the lock at +0x5dc for the given owner, if it is free: raise the held
 * flag at +0x5d8 and stamp the acquisition time at +0x5e0. A lock that is
 * already held is left alone and the caller is not told. */
extern unsigned long long func_020031d4(void);

typedef struct {
    char pad0000[0x5d8];
    int bHeld;                      /* +0x5d8 */
    int nOwner;                     /* +0x5dc, 0 = free */
    unsigned long long qwTakenAt;   /* +0x5e0 */
} Ov002LockContext;

extern Ov002LockContext *data_ov002_0207f620;

void func_ov002_0205e288(int owner) {
    Ov002LockContext *ctx = data_ov002_0207f620;

    if (ctx->nOwner != 0) {
        return;
    }

    ctx->nOwner = owner;
    ctx->bHeld = 1;
    ctx->qwTakenAt = func_020031d4();
}
