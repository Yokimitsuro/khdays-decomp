/*
 * Ov002_PollLinkRequest - read this frame's request and hand it to the record.
 *
 * The queued blit goes out first, then the request block is copied in. While a
 * request is still waiting, an empty one clears the wait and nothing else is
 * sent. Otherwise the request is published only when the session answers, the
 * shutdown hook is idle, the transition key is not held and the panel has
 * nothing pending; if any of those refuses, an empty request is published.
 *
 * ARM.
 */

typedef unsigned short u16;

typedef struct {
    void *pSrc;
    u16 wStride;
    unsigned char bWidth;
    unsigned char bHeight;
    void *pParams;
} Ov002BlitDesc;

typedef struct {
    char pad000[4];
    int bWaiting;
} Ov002LinkCtx;

extern Ov002LinkCtx *data_ov002_0207f9f0;

extern Ov002BlitDesc *OS_IsThreadAvailable_0x0206373c(void);
extern void func_ov002_02066820(Ov002BlitDesc *pDesc);
extern u16 *func_ov002_02054d4c(u16 *pReq);
extern void func_ov002_02066f14(u16 *pReq);
extern int func_ov002_02053884(void);
extern int func_ov002_0206b7a4(void);
extern int func_ov002_0205724c(void);

int func_ov002_02066bd8(void)
{
    u16 aReq[4];
    Ov002LinkCtx *ctx;

    ctx = data_ov002_0207f9f0;
    func_ov002_02066820(OS_IsThreadAvailable_0x0206373c());
    func_ov002_02054d4c(aReq);
    if (ctx->bWaiting != 0) {
        if (aReq[2] == 0) {
            ctx->bWaiting = 0;
        }
    } else if (func_ov002_02053884() != 0 && func_ov002_0206b7a4() == 0 &&
               ((*(volatile u16 *)0x027fffa8 & 0x8000) >> 15) == 0 &&
               func_ov002_0205724c() == 0) {
        func_ov002_02066f14(func_ov002_02054d4c(aReq));
    } else {
        aReq[2] = 0;
        func_ov002_02066f14(aReq);
    }
    return 0;
}
