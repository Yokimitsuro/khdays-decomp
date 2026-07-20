/* Reflows a scrollable list to a new item count: hides the 16 body handles, sizes the window, and
 * re-enables the first/last (arrow) handles.
 *
 * The handle group lives at context+0x8 (first at +0, last at +4, handles[16] at +8..0x48,
 * count at +0x48). NOTE this is a DIFFERENT ov000 scene context from the 0xd18c menu context:
 * there context+0x8 is inside the render node, here it is this handle table. ov000 builds several
 * scenes at the same root-heap address, so the two layouts legitimately share an address; kept as
 * its own type rather than forced into Ov000SceneContext.
 *
 * visible_count = 160 / input_value clamped to [4,20] (func_02020400 is the signed-divide runtime
 * helper _s32_div_f -- see codegen-cracks.md), with input_value==0 taken as the maximum 20. That is
 * a viewport height in rows: 160 units of list divided by per-item spacing. count is then
 * visible_count - 4, i.e. the four arrow/frame handles are excluded from the body total. The final
 * func_ov000_02059264(0) re-lays-out from row 0.
 */

typedef unsigned char u8;

typedef struct {
    int *pFirstHandle;   /* +0x00 */
    int *pLastHandle;    /* +0x04 */
    int *handles[16];    /* +0x08 */
    int nCount;          /* +0x48 */
    int nInputValue;     /* +0x4c */
    int nUnk50;          /* +0x50 */
    int nVisibleCount;   /* +0x54 */
    int nUnk58;          /* +0x58 */
    int nUnk5c;          /* +0x5c */
} Ov000HandleGroup;

typedef struct {
    u8 pad_0000[8];
    Ov000HandleGroup handle_group; /* +0x08 */
    u8 pad_0068[0x4b70];
    u8 object[1];                  /* +0x4bd8 */
} Ov000ListSceneContext;

extern Ov000ListSceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov000_02055cb4(void *object, int *handle, int enabled);
extern int func_02020400(int numerator, int denominator);
extern void func_ov000_02059264(int row);

void func_ov000_02059324(int input_value) {
    Ov000ListSceneContext *context = NNSi_FndGetCurrentRootHeap();
    Ov000HandleGroup *group = &context->handle_group;
    int i;

    for (i = 0; i < 16; i++) {
        func_ov000_02055cb4(context->object, group->handles[i], 0);
    }

    group->nInputValue = input_value;
    group->nUnk50 = 0;
    group->nUnk5c = 0;
    group->nUnk58 = 0;

    if (input_value == 0) {
        group->nVisibleCount = 20;
    } else {
        group->nVisibleCount = func_02020400(160, input_value);
        if (group->nVisibleCount < 4) {
            group->nVisibleCount = 4;
        }
        if (group->nVisibleCount > 20) {
            group->nVisibleCount = 20;
        }
    }

    group->nCount = group->nVisibleCount - 4;
    func_ov000_02055cb4(context->object, group->pFirstHandle, 1);
    func_ov000_02055cb4(context->object, group->pLastHandle, 1);
    func_ov000_02059264(0);
}
