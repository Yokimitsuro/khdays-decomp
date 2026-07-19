extern int func_ov025_020b09fc(void);
extern int CARD_GetResultCode(void);
extern void func_0200e164(int id);
extern void func_020208f0(void);
extern void func_ov025_020b09d4(int arg0, int arg1, int arg2);

extern unsigned char data_ov025_020b5760[];
extern unsigned short data_0204be10;
extern void *data_0204be14;

/* Step a CARD transfer over two 0x2018-byte blocks.
 *   poll not finished            -> return 1 (busy)
 *   CARD_GetResultCode != 0      -> record it at +4, clean up, return 3 (error)
 *   ++counter reaches 2          -> clean up, return 0 (done)
 *   otherwise issue block (counter + slot*2) at index*0x2018 + 0x20, return 1
 *
 * Byte-identical (modulo relocs) to the ov008/ov009/ov025 siblings.
 *
 * Two things are load-bearing and were each got wrong first:
 *  - the block issuer takes THREE args; 0x2018 is the third, not scheduling
 *    debris left in r2.
 *  - the context global must be written out at every use.  Caching it in a
 *    local `ctx` is hand-CSE and moves it from r1 to r2. */
int func_ov025_020b0db0(void) {
    int rc;
    unsigned int done;

    if (func_ov025_020b09fc() != 0) {
        rc = CARD_GetResultCode();
        *(int *)(data_ov025_020b5760 + 4) = rc;
        if (rc != 0) {
            func_0200e164(data_0204be10);
            func_020208f0();
            return 3;
        }
        data_ov025_020b5760[0] = data_ov025_020b5760[0] + 1;
        done = data_ov025_020b5760[0];
        if (done >= 2) {
            func_0200e164(data_0204be10);
            func_020208f0();
            return 0;
        }
        func_ov025_020b09d4((done + (data_ov025_020b5760[1] << 1)) * 0x2018 + 0x20,
                            (int)data_0204be14, 0x2018);
    }
    return 1;
}
