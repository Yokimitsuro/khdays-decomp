/* Enemy spawn hook: cancel the current action (mode 1), roll a random facing
 * (-1 or +1) into the model field at +0x84, and register the reaction handler.
 *
 * The `+ (pad - pad)` is load-bearing, not noise. mwcc folds a literal `+ 0`
 * away and emits `cmp r0,#0`; the difference of an uninitialised local against
 * itself survives folding and produces the ROM's `adds r0,r0,#0` -- an ADD that
 * sets flags. Same trick as func_ov114_020ccf28, which this family shares a
 * shape with. */
extern void func_ov107_020c9264(int model, int mode, int b);
extern int func_02023eb4(int range);
extern void func_0203c634(void *self, int script, void *handler);
extern void func_ov250_020d09d4(void);

void func_ov250_020d0988(int *self) {
    int *model = (int *)self[1];
    int pad;

    func_ov107_020c9264(*model, 1, 1);

    *(int *)((char *)model + 0x84) =
        (func_02023eb4(2) + (pad - pad) != 0) ? -1 : 1;

    func_0203c634(self, *(signed char *)((char *)self + 0x20), &func_ov250_020d09d4);
}
