/* Ping-pong alpha pulse on the selection highlight, self-restarting at each end.
 *
 * The object at +0x4d74 is a Tween (the 0x1c interpolator driven by Tween_Configure/Tween_Start).
 * The word the flags below sit on is that Tween's own dwFlags at Tween+0x18 = +0x4d8c, and bit 2
 * is the finished flag -- func_0203602c raises it with `dwFlags |= 4` once elapsed >= duration.
 * So the test is not "a transition is running", it is "the tween has ENDED", and the branch
 * restarts it the other way round. The geometry closes exactly: 0x4d74 + 0x1c = 0x4d90, which is
 * where nDirection sits.
 *
 * The tween runs between Q12 0x8000 and 0x2000 (8.0 and 2.0) over 500 ms. The sampled value is
 * shifted down by 12 to yield 8..2, and func_020327e0 clamps that to [0,16] before storing -- 0..16
 * being the DS blend-coefficient range, so the pulse is an alpha level, not a position.
 *
 * NOTE the type below deliberately splits the Tween into a 0x18 body plus a bitfield word rather
 * than using the Tween type. That split is what makes mwcc emit the single ldr+tst the ROM has;
 * it is a codegen tool, and the honest layout is the one described above and modelled in Ghidra.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u8 pad_0000[0x4c];
    u8 selection_object[0x4d28]; /* +0x4c   receives the pulsed blend level */
    u8 tween_body[0x18];         /* +0x4d74 Tween, first 0x18 bytes */
    u32 tween_flags_0_1 : 2;
    u32 tween_finished : 1;      /* +0x4d8c Tween.dwFlags bit 2 */
    u32 tween_flags_3_31 : 29;
    int nDirection;              /* +0x4d90 */
} Ov000SceneContext;

extern Ov000SceneContext *volatile data_ov000_0205ac24;
extern void func_02035fb0(void *tween, int mode, int from, int to,
                           int duration);
extern void func_02035ffc(void *tween);
extern void func_0203602c(void *tween, int *value);
extern void func_020327e0(void *object, int value);

void func_ov000_0205157c(void) {
    Ov000SceneContext *context = data_ov000_0205ac24;
    int value = 0;

    if (context->tween_finished) {
        func_02035fb0(context->tween_body, 0,
                      context->nDirection != 0 ? 0x8000 : 0x2000,
                      context->nDirection != 0 ? 0x2000 : 0x8000, 500);
        func_02035ffc(data_ov000_0205ac24->tween_body);
        {
            Ov000SceneContext *current = data_ov000_0205ac24;
            current->nDirection = current->nDirection == 0 ? 1 : 0;
        }
        return;
    }

    func_0203602c(context->tween_body, &value);
    func_020327e0(context->selection_object, value >> 12);
}
