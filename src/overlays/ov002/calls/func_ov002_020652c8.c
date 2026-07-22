/* Resolve the ov022 row for `self` and hand it to the row formatter along with
 * the pair built from the current ov022 selection. The scratch pair lives on the
 * stack and is filled by func_ov002_02064cd8 before the second lookup runs. */
extern int func_ov022_020881f8(void);
extern void func_ov002_02064cd8(void *out, int value);
extern int func_ov022_02088254(int self);
extern void func_ov002_02064f00(int self, void *pair, int row);

void func_ov002_020652c8(int self) {
    int pair[2];

    func_ov002_02064cd8(pair, func_ov022_020881f8());
    func_ov002_02064f00(self, pair, func_ov022_02088254(self));
}
