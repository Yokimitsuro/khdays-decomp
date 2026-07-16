/* func_ov006_02055d80 -- title: start tween number `slot` (0..4) on the title object.
 * Each tween lives at OBJ+0x9614 + slot*0x1c; `val` is the Q12 target. Returns 0 if the
 * title object is gone or the slot is out of range. */
extern void func_02035fb0(int *tween, int a, int b, int target, int mode);
extern void func_02035ffc(int tween);
extern int *data_ov006_02056664;

int func_ov006_02055d80(int val, unsigned int slot, int mode) {
    if (data_ov006_02056664 == 0) {
        return 0;
    }
    if (slot > 4) {
        return 0;
    }
    func_02035fb0((int *)((char *)data_ov006_02056664 + 0x9614 + slot * 0x1c),
                  0, 0, val << 12, mode);
    func_02035ffc((int)((char *)data_ov006_02056664 + 0x9614 + slot * 0x1c));
    return 1;
}
