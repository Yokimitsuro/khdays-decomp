/* Wait for the state machine to go quiet, then kick the idle animation. The
 * wait is a genuine SPIN: the bne at the end of the poll branches BACKWARDS to
 * the call, not forwards to a return, and the constant 0 argument is parked in a
 * callee-saved register precisely because it has to survive each iteration. */
extern int func_ov002_0205e9e8(int which);
extern void func_020300f8(void *animator);

typedef struct {
    char pad0000[0x6f8];
    char animator[1];       /* +0x6f8 */
} Ov002RequestContext;

extern Ov002RequestContext *data_ov002_0207f624;

void func_ov002_0205ed24(void) {
    Ov002RequestContext *ctx = data_ov002_0207f624;

    do {
    } while (func_ov002_0205e9e8(0) != 0);

    func_020300f8(ctx->animator);
}
