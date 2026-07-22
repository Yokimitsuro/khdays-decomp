/* Publish the pending menu id at +0x4af8 -- but only while the transition word
 * at +0x6a48 reads zero in its LOW HALFWORD. Mid-transition the slot is blanked
 * instead. Does nothing with no scene installed.
 *
 * The lsl #16 / asrs #16 pair is a cast of a WORD field to short, not a short
 * field: a short field would have been an ldrsh. */
typedef struct {
    char pad0000[0x4af8];
    unsigned short wPendingId;  /* +0x4af8 */
    char pad4afa[0x1f4e];
    int nTransition;            /* +0x6a48 */
} Ov000SceneContext;

extern Ov000SceneContext *data_ov000_0205ac24;

void func_ov000_0205324c(unsigned short id) {
    Ov000SceneContext *ctx = data_ov000_0205ac24;

    if (ctx == 0) {
        return;
    }

    if ((short)ctx->nTransition != 0) {
        ctx->wPendingId = 0;
        return;
    }

    ctx->wPendingId = id;
}
