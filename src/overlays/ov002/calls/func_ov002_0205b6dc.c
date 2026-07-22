/* Reposition the widget when the caller supplies a target: move it to the signed
 * 16-bit coordinates, optionally re-anchor it, and always hand the target on to
 * func_ov002_020536dc. The fifth argument arrives on the stack and is re-read
 * from there for the final call rather than held. */
extern void func_ov002_02053720(void *self, short x, short y);
extern void func_ov002_02053700(void *self);
extern void func_ov002_020536dc(void *self, int target);

void func_ov002_0205b6dc(void *self, int x, int y, int reanchor, int target) {
    if (target != 0) {
        func_ov002_02053720(self, (short)x, (short)y);
        if (reanchor != 0) {
            func_ov002_02053700(self);
        }
    }

    func_ov002_020536dc(self, target);
}
