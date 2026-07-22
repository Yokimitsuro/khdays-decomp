/* Retarget the widget: re-bind it to the new owner with style 0xe, point the
 * renderer at the new source, and push the new depth down the three-deep depth
 * chain at +0xb8 / +0xb4 / +0xb0.
 *
 * The chain is written as three separate assignments, each RE-READING the field
 * it just wrote -- the ROM rebuilds the address every time, so a held pointer or
 * a single value reused across the three loses it. */
extern void func_0202a634(void *self, int owner, int flags, int style);
extern void func_02016cd0(void *renderer, void *source);

typedef struct {
    char pad0000[0x78];
    void *pRenderer;    /* +0x78 */
    char pad007c[0x34];
    int nDepth0;        /* +0xb0 */
    int nDepth1;        /* +0xb4 */
    int nDepth2;        /* +0xb8 */
} Ov002Widget;

void func_ov002_0205f5a8(Ov002Widget *self, int owner, void *source, int depth) {
    func_0202a634(self, owner, 1, 0xe);
    func_02016cd0(self->pRenderer, source);

    self->nDepth2 = depth;
    self->nDepth1 = self->nDepth2;
    self->nDepth0 = self->nDepth1;
}
