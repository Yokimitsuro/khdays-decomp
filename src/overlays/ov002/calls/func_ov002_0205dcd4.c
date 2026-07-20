/* Publish one key/value pair into the session's slot table, and if it actually
 * changed, re-run the screen refresh for the local player.
 *
 * The `>> 32` below is NOT arithmetic on a real 64-bit value.  func_02020400 is
 * the MetroWerks runtime signed divide (`_s32_div_f`): it returns the QUOTIENT in
 * r0 and the REMAINDER in r1, so it is really the same routine mwcc emits for
 * both `/` and `%`.  Declaring it `long long` and taking the high half is how you
 * name the remainder from C.  The statement means
 *
 *     func_ov002_0205b7dc(ctx->bPlayer, ctx->bChannel % 6, 0);
 *
 * and writing it that way compiles to the identical 216 bytes -- but mwcc then
 * names the reloc `_s32_div_f`, while config/arm9/symbols.txt calls 0x02020400
 * `func_02020400`, so the link would not resolve.  ~90 matched files already call
 * this helper by address for the quotient; this is the first one that needed the
 * remainder.  See dudas.md.
 *
 * The refresh block is emitted twice inside the case-1 arm, which is why it is a
 * `static inline` helper rather than a plain call: -inline on,noauto expands it
 * at both sites the way the original does. */
typedef struct {
    unsigned char bKey;      /* +0x00 */
    unsigned char bValue;    /* +0x01 */
} Ov002HudSlot;

typedef struct {
    char pad00[1];
    unsigned char bPlayer;    /* +0x01 */
    unsigned char bChannel;   /* +0x02 */
    char pad03[0x2d];
    unsigned char bSlotCount; /* +0x30 */
    unsigned char bRow;       /* +0x31 */
    Ov002HudSlot aSlots[1];      /* +0x32 -- bSlotCount entries, stride 2 */
} Ov002HudContext;

extern void func_ov002_0205bbbc(int player);
extern int func_ov002_0205a3f0(int *out, int player);
extern void func_ov002_0205c57c(void);
extern void func_ov002_0205c9c4(void);
extern void func_ov002_0205c624(int a);
extern void func_ov002_0205a924(int a, int b, int c, int d);
extern void func_ov002_020536bc(int id);
extern int func_ov002_0205374c(void);
extern int func_ov002_02053558(int id);
extern void func_ov002_020535f0(int handle);
extern long long func_02020400(int a, int b);
extern void func_ov002_0205b7dc(int a, int b, int c);

extern Ov002HudContext *data_ov002_0207f620;

static inline void Ov002_HudRefreshMemberPanel(Ov002HudContext *ctx) {
    func_ov002_020536bc(0xe);
    if (func_ov002_0205374c() == 0) {
        func_ov002_020535f0(func_ov002_02053558(0x79));
    }
    func_ov002_0205b7dc(ctx->bPlayer,
                        (int)(func_02020400(ctx->bChannel, 6) >> 32), 0);
}

void func_ov002_0205dcd4(int key, int value) {
    Ov002HudContext *ctx = data_ov002_0207f620;
    int changed = 0;
    int i;
    int out;

    for (i = 0; i < ctx->bSlotCount; i++) {
        if (key == ctx->aSlots[i].bKey) {
            if (value == ctx->aSlots[i].bValue) break;
            ctx->aSlots[i].bValue = value;
            changed = 1;
            break;
        }
    }
    if (changed == 0) return;

    func_ov002_0205bbbc(ctx->bPlayer);
    switch (func_ov002_0205a3f0(&out, ctx->bPlayer)) {
    case 0:
        func_ov002_0205c57c();
        break;
    case 1:
        Ov002_HudRefreshMemberPanel(ctx);
        func_ov002_0205c624(out);
        func_ov002_0205a924(out + 1, ctx->bRow, 7, 0xb);
        Ov002_HudRefreshMemberPanel(ctx);
        break;
    case 4:
        func_ov002_0205c9c4();
        break;
    }
}
