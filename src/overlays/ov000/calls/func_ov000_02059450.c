/* Maps a raw input coordinate to a list selection index, with paging offset and cursor clamp.
 *
 * position = input->value - (page*4 + 16), clamped to [0, limit] where limit = 160 - page*8.
 * selected = 18 * position / limit (func_02020400 is the signed-divide helper _s32_div_f), i.e. the
 * position scaled to an 18-row window; the sub-row remainder becomes the paging offset. The cursor
 * (the top visible row) is clamped to keep selected within [cursor, cursor+9]. If the selection
 * changed, func_ov000_02059d78 re-queues the row transfers.
 *
 * This is a list-scene context taken from the root heap; +0/+2 are selected/cursor (the two shorts
 * the 0xd18c type reads as nValue0/nSelection), but page/offset at +0x5c/+0x60 are this scene's own
 * fields -- kept as a local view rather than merged into Ov000SceneContext.
 */

typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

typedef struct {
    u16 unknown_0;
    u16 value;
} OverlayInput;

typedef struct {
    s16 selected;      /* +0x00 */
    s16 cursor;        /* +0x02 */
    u8 pad_0004[0x58];
    int page;          /* +0x5c */
    int offset;        /* +0x60 */
} Ov000ListSelectCtx;

extern Ov000ListSelectCtx *NNSi_FndGetCurrentRootHeap(void);
extern int func_02020400(int numerator, int denominator);
extern void func_ov000_020593f4(int selected);
extern void func_ov000_02059d78(void);

void func_ov000_02059450(const OverlayInput *input) {
    Ov000ListSelectCtx *context = NNSi_FndGetCurrentRootHeap();
    int position;
    int limit;
    int old_selected;

    old_selected = context->selected;
    position = input->value - (context->page * 4 + 16);
    limit = 160 - context->page * 8;

    context->offset = 0;
    if (position < 0) {
        position = 0;
    } else if (position >= limit) {
        position = limit;
    } else if (limit > 18) {
        int scaled = func_02020400(18 * position, limit);
        context->offset = position - (limit * scaled) / 18;
    }

    context->selected = func_02020400(18 * position, limit);
    if (context->cursor < context->selected) {
        context->cursor = context->selected;
    } else if (context->selected + 9 < context->cursor) {
        context->cursor = context->selected + 9;
    }

    func_ov000_020593f4(context->selected);
    if (old_selected != context->selected) {
        func_ov000_02059d78();
    }
}
