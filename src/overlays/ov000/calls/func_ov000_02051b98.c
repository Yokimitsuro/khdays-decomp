/* func_ov000_02051b98 -- park the two selection markers on their side of the screen.
 *
 * Walks the two marker ids in data_ov000_0205a6bc, looks each one up in the scene's selection
 * object (+0x4c), keeps the y it already has and rewrites x to one of two columns.  Which
 * column depends on the layout flag at +0x4b70 and on whether the marker is id 0x15: the pair
 * swaps sides when the flag is set.
 *
 * CODEGEN NOTE -- three shapes are load-bearing here.  The loop counter is UNSIGNED (the ROM
 * ends with `blo`, not `blt`).  The x assignment has to be a real if/else, not a ternary, or
 * mwcc computes into a scratch register instead of emitting the ROM's predicated `streq`/`strne`
 * straight to the stack slot.  And the global must NOT be volatile: it is re-read inside the
 * loop anyway, and qualifying it costs enough register pressure to shuffle the whole prologue
 * (17 differing bytes vs 7).  Declaration order ctx, position, i, entry, id is the one of 120
 * that colours entry/id into sb/sl the ROM's way.
 */
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct OverlayVector {
    int x;
    int y;
} OverlayVector;

typedef struct Ov000SceneContext {
    u8 pad_0000[0x4c];
    u8 selectionObject[0x4b24];
    int alternatePosition;
} Ov000SceneContext;

extern Ov000SceneContext *data_ov000_0205ac24;
extern const int data_ov000_0205a6bc[2];
extern int *func_ov000_02055b48(void *object, int id);
extern OverlayVector *func_ov000_02055bc4(void *object, int *entry);
extern void func_ov000_02055bfc(void *object, int *entry, const OverlayVector *position);

void func_ov000_02051b98(void) {
    Ov000SceneContext *ctx;
    OverlayVector position;
    u32 i;
    int *entry;
    int id;
    ctx = data_ov000_0205ac24;
    for (i = 0; i < 2; i++) {
        id = data_ov000_0205a6bc[i];
        entry = func_ov000_02055b48(ctx->selectionObject, id);
        position.y = func_ov000_02055bc4(ctx->selectionObject, entry)->y;
        if (data_ov000_0205ac24->alternatePosition != 0) {
            if (id == 0x15) {
                position.x = 0x28000;
            } else {
                position.x = 0x88000;
            }
        } else {
            if (id == 0x15) {
                position.x = 0x88000;
            } else {
                position.x = 0x28000;
            }
        }
        func_ov000_02055bfc(ctx->selectionObject, entry, &position);
    }
}
