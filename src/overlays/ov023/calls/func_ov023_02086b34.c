/* func_ov023_02086b34 -- is this record's slot idle? States -1 and 0 are idle outright; state 1
 * defers to func_0202e5c4 on the sub-object at +0x3c; anything else is idle only while the handle
 * at +0xf0 is clear.
 *
 * The state test is a SWITCH on a signed int -- the ROM tests -1, then 0, then 1, which is mwcc's
 * numeric ordering of the case labels. And the `return 0` inside case 1 SHARES the default's exit
 * (a `goto`): written as its own `return 0;` it gets a second inline `movs r0,#0 ; pop` and the
 * function is 4 bytes long. */
extern int func_0202e5c4(int p);

int func_ov023_02086b34(int obj) {
    switch (*(int *)(obj + 0xf8)) {
    case -1:
    case 0:
        return 1;
    case 1:
        if (func_0202e5c4(obj + 0x3c) == 0) {
            goto ret0;
        }
        return 1;
    }
    if (*(int *)(obj + 0xf0) != 0) {
        goto ret0;
    }
    return 1;
ret0:
    return 0;
}
