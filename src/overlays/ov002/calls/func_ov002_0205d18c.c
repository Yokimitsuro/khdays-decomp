/* Expire the lock at +0x5dc once it has been held longer than the timeout. */
extern unsigned long long func_020031d4(void);

typedef struct {
    char pad0000[1];
    unsigned char bMode;            /* +0x1 */
    char pad0002[0x5d6];
    int bHeld;                      /* +0x5d8 */
    int nOwner;                     /* +0x5dc, 0 = free */
    unsigned long long qwTakenAt;   /* +0x5e0 */
} Ov002LockContext;

extern Ov002LockContext *data_ov002_0207f620;

extern int func_ov002_02053558(int nId);
extern void func_ov002_020535f0(int nEntry);
extern void func_ov002_0205ac5c(void);
extern void func_ov002_02053cd4(int nId);

int func_ov002_0205d18c(void) {
    Ov002LockContext *ctx = data_ov002_0207f620;

    if (ctx->bHeld != 0) {
        if (ctx->qwTakenAt + 0x17f898 < func_020031d4()) {
            func_ov002_020535f0(func_ov002_02053558(0x4e));
            func_ov002_020535f0(func_ov002_02053558(0x48));
            func_ov002_0205ac5c();
            ctx->bHeld = 0;
            ctx->nOwner = 0;
        }
    }

    if (ctx->bMode == 9) {
        func_ov002_02053cd4(0xb);
    }
    return 0;
}
