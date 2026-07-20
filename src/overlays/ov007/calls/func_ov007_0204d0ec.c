/* Advance the message-box line timer; every 15 frames either step to the next line or
 * finish, and let the B button cut straight to the skip handler.
 *
 * Returns the handler to install next, or null while the timer is still running.
 *
 * THE CRACK, and it is a lesson about how these were being tested.  The diff was two
 * predicated instructions in the empty-line branch -- the ROM stores then loads, we loaded
 * then stored -- and it survived roughly a dozen spellings across two sessions.  It needs
 * TWO changes AT ONCE:
 *   1. the test inverted so the EMPTY-LINE case is the `if` and the has-more-lines case
 *      the `else`, and
 *   2. `volatile` on that branch's store of root->frame.
 * Both had been tried, and each ALONE looks like a dead end: the inversion by itself is
 * 140 bytes (8 over) and the volatile by itself leaves the diff exactly where it was.  Only
 * together do they give the ROM.  Two axes that each score WORSE alone but right together
 * are invisible to one-axis-at-a-time search, which is what every previous attempt did.
 *
 * Also note the ROM is internally inconsistent -- the B-button block emits load-then-store
 * while this block emits store-then-load -- which is the tell that the two blocks did not
 * come from the same source shape, and is what the inversion reproduces.
 *
 * With this, ov007 is 14/14.
 */
typedef int (*Ov007Handler)(void);

typedef struct {
    char pad00[0x20];
    int frame;                /* +0x20 */
    char pad24[0x4c];
    int lineCount;            /* +0x70 */
    char pad74[0x8];
    unsigned short line[1];   /* +0x7c */
} Ov007Ctx;

extern Ov007Ctx *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov007_0204ce94(void *p);
extern int func_ov007_0204d170(void);
extern int func_ov007_0204cf7c(void);
extern int func_ov007_0204d2d0(void);
extern unsigned short data_0204c190;

Ov007Handler func_ov007_0204d0ec(void)
{
    Ov007Ctx *root;
    Ov007Handler ret;
    int frame;

    root = NNSi_FndGetCurrentRootHeap();
    ret = 0;

    frame = root->frame;
    frame++;
    root->frame = frame;

    if (frame >= 15) {
        func_ov007_0204ce94(root);

        if (root->line[0] == 0) {
            *(volatile int *)&root->frame = 0;
            ret = func_ov007_0204d170;
        } else {
            root->lineCount++;
            root->frame = 0;
            ret = func_ov007_0204cf7c;
        }
    }

    if ((data_0204c190 & 8) != 0) {
        root->frame = 0;
        ret = func_ov007_0204d2d0;
    }

    return ret;
}
