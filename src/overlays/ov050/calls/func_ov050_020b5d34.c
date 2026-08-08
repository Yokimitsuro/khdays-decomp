/* Mode change for the ov050 actor, the handler installed in slot 0 of the table its
 * constructor builds. State 0x2e re-inits the block at +0x2c2c; 0x2f and 0x30 share an
 * arm that records which of the two the mode is at +0x2c2c, sets the matching timer
 * ceiling at +0x2c34, requests sound 0xcb with a different variant for each, and
 * retimes one or two sub-objects. All three only act when the mode actually changes.
 * The new mode is then handed down.
 *
 * The block address is declared WHOLE, as self + 0x2c2c, not built in two steps at the
 * point of use. 0x2c2c is not an encodable immediate, so mwcc has to split it into
 * `add #0x2c` and `add #0x2c00` -- and because the local is declared before the switch
 * it leaves the first half in the entry block, in the slot between the cmp and the beq,
 * and sinks the second half into the arm that uses it. That split is what puts the
 * value in r1: computed as a whole it stays a temporary and coalesces onto the argument
 * register, whereas a local spelled `self + 0x2c` is a variable and lands in r2, which
 * then pushes the guard's load down from r2 to r1. Writing the argument inline instead
 * keeps both adds inside the arm and reverses the parameter copies.
 */
extern void func_ov050_020b61d4(char *self, char *pBlock);
extern void func_ov022_020a4490(char *self, int nSound, int nVariant);
extern void func_ov050_020b6220(char *pObj, int nTime);
extern void func_ov022_020a384c(char *self, int nState);

void func_ov050_020b5d34(char *self, int nState)
{
    char *pBlock = self + 0x2c2c;

    switch (nState) {
    case 0x2e:
        if (nState != *(int *)(self + 0x6bc)) {
            func_ov050_020b61d4(self, pBlock);
        }
        break;

    case 0x2f:
    case 0x30:
        if (nState == *(int *)(self + 0x6bc)) {
            break;
        }
        if (nState == 0x2f) {
            *(int *)(self + 0x2000 + 0xc2c) = 0;
            *(int *)(self + 0x2000 + 0xc34) = 0x9000;
            func_ov022_020a4490(self, 0xcb, 2);
            func_ov050_020b6220(self + 0xd50 + 0x2000, 0);
        } else {
            *(int *)(self + 0x2000 + 0xc2c) = 1;
            *(int *)(self + 0x2000 + 0xc34) = 0x12000;
            func_ov022_020a4490(self, 0xcb, 3);
            func_ov050_020b6220(self + 0x38 + 0x2c00, 0x9000);
            func_ov050_020b6220(self + 0xd50 + 0x2000, 0x9000);
        }
        break;
    }
    func_ov022_020a384c(self, nState);
}
