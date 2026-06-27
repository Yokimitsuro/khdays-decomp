extern unsigned short *GXx_SetMasterBrightness_(unsigned short *p, int v);

extern unsigned char data_027e0080;
extern signed char data_027e0084;

struct VBlankNode {
    int pad0[5];
    void (*func)(void);
    struct VBlankNode *next;
};

struct VBlankCtx {
    unsigned int counter;
    struct VBlankNode *list;
};

extern struct VBlankCtx data_027e0088;

extern char data_027e0000[];

void OSi_VBlankInterruptHandler(void) {
    struct VBlankCtx *ctx;
    struct VBlankNode *p;
    unsigned char flags;

    ctx = &data_027e0088;
    flags = data_027e0080;
    ctx->counter = ctx->counter + 1;

    if (flags & 1) {
        GXx_SetMasterBrightness_((unsigned short *)0x0400006C, (&data_027e0084)[0]);
    }
    if (flags & 2) {
        GXx_SetMasterBrightness_((unsigned short *)0x0400106C, (&data_027e0084)[1]);
    }
    p = ctx->list;
    data_027e0080 = 0;
    while (p) {
        (*p->func)();
        p = p->next;
    }
    {
        unsigned int base = ((unsigned int)data_027e0000) + 0x3000;
        *(volatile unsigned int *)(base + 0xFF8) |= 1;
    }
}
