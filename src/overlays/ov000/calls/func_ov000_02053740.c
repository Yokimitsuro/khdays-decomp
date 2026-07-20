/* Draws the mode-dependent 2x2 icon on the sub-scene, wrapped in the object's begin/submit pair.
 *
 * func_02030158 is Obj_InvokeInnerVtable4 (dispatch through the inner object's vtable slot 4) and
 * func_020300f8 is EnqueueObjGfxCommand, so the body between them is one drawing pass: begin the
 * object, emit at most one item, submit.
 *
 * Modes 2 and 3 draw the SAME sprite id (0x8d) at the same 2x2 tile size and differ only in the
 * variant they resolve out of the object at +0x4bb8 (0 vs 1). Every other mode draws nothing at
 * all, yet still runs the begin/submit pair -- which is why the switch has no default rather than
 * an early return: the enqueue has to happen either way.
 */

typedef unsigned char u8;

typedef struct {
    u8 pad_0000[0x4b04];
    u8 draw_object[0xb4];    /* +0x4b04 */
    u8 variant_source[1];    /* +0x4bb8 */
} Ov000SubSceneContext;

extern Ov000SubSceneContext *volatile data_ov000_0205ac28;
extern void func_02030158(void *object);
extern void *func_ov000_02056970(void *object, int variant);
extern void func_ov000_02053d18(void *object, int id, int width, int height,
                                void *variant, int enabled);
extern void func_020300f8(void *object);

void func_ov000_02053740(int mode) {
    void *object = data_ov000_0205ac28->draw_object;

    func_02030158(object);
    switch (mode) {
    case 2:
        func_ov000_02053d18(
            object, 0x8d, 2, 2,
            func_ov000_02056970(data_ov000_0205ac28->variant_source, 0), 1);
        break;
    case 3:
        func_ov000_02053d18(
            object, 0x8d, 2, 2,
            func_ov000_02056970(data_ov000_0205ac28->variant_source, 1), 1);
        break;
    }
    func_020300f8(object);
}
