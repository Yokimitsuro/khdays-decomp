/* Places the mode-2/3 marker: pick an entry by id, read its position, and re-apply it (offset) to
 * entry id 1.
 *
 * Mode 2 selects entry (base2 + 2), mode 3 selects (base3 + 5), from the object list at +0x78; other
 * modes do nothing. The selected entry's position is read, nudged (+0x8000 in X for mode 2, +0x8000
 * in Y always -- half a tile in 16.16), and written onto entry id 1. Same Ov000SubSceneContext as
 * Ov000_DrawModeIcon; +0x20/+0x24 are the two mode bases (the +0x20 the constructor seeds to 1).
 *
 * OverlayPoint {x,y} is a 2-D 16.16 point; kept local (no 2-D fx32 type exists in the tree yet).
 */

typedef unsigned char u8;

typedef struct {
    int x;
    int y;
} OverlayPoint;

typedef struct {
    u8 pad_0000[0x20];
    int base2;              /* +0x20 */
    int base3;              /* +0x24 */
    u8 pad_0028[0x50];
    u8 object_list[1];      /* +0x78 */
} Ov000SubSceneContext;

extern Ov000SubSceneContext *data_ov000_0205ac28;
extern int *func_ov000_02055b48(void *list, int id);
extern void func_ov000_02055d98(void *list, int *entry);
extern OverlayPoint *func_ov000_02055c40(void *list, int *entry);
extern void func_ov000_02055bfc(void *list, int *entry,
                                const OverlayPoint *position);

void func_ov000_02053c3c(int mode) {
    Ov000SubSceneContext *context = data_ov000_0205ac28;
    int *entry = 0;
    OverlayPoint position;

    switch (mode) {
    case 2:
        entry = func_ov000_02055b48(context->object_list,
                                    context->base2 + 2);
        func_ov000_02055d98(context->object_list, entry);
        break;
    case 3:
        entry = func_ov000_02055b48(context->object_list,
                                    context->base3 + 5);
        func_ov000_02055d98(context->object_list, entry);
        break;
    }

    if (entry == 0) {
        return;
    }

    position = *func_ov000_02055c40(context->object_list, entry);
    entry = func_ov000_02055b48(context->object_list, 1);
    if (mode == 2) {
        position.x += 0x8000;
    }
    position.y += 0x8000;
    func_ov000_02055bfc(context->object_list, entry, &position);
}
