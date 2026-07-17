/* ★ func_020235e8 takes THREE arguments. This file declared two, and the dropped 0 is the ROM's
 * `mov r2, #0` at +0x0c -- the same 0 that zeroes obj->f48, kept live across to the call as its 3rd
 * argument. (2026-07-17)
 *
 * This file previously carried a confident write-up claiming "an r4/r5 register-allocation tie...
 * No source form (raw cast or int* obj) flips it", and reasoned at length about why the sibling
 * ov256_020ce778 allocates differently. All of that was wrong: it was a dropped argument, and the
 * register swap was a symptom. Kept here as a warning -- a nonmatching write-up is one person's
 * failed attempt at one moment, not a property of the function.
 *
 * c634 state-entry handler: init obj fields (f48=0, f14=0x23000, f78=1, f7c=1), fire
 * func_020235e8(0x20b7, 8, 0), latch owner->+0x1c7 = obj->f74 + 2, then dispatch state with a null
 * callback. self->+0x20 = slot index. */
extern void func_020235e8(int a, int b, int c);
extern void func_0203c634(int self, int index, void *cb);
void func_ov256_020cd8f0(int self) {
    int obj = *(int *)(self + 4);
    *(int *)(obj + 0x48) = 0;
    *(int *)(obj + 0x14) = 0x23000;
    *(int *)(obj + 0x78) = 1;
    *(int *)(obj + 0x7c) = 1;
    func_020235e8(0x20b7, 8, 0);
    *(unsigned char *)(*(int *)obj + 0x1c7) = *(int *)(obj + 0x74) + 2;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
