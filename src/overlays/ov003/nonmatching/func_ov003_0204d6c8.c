/* NONMATCHING: loop strength-reduction tie, ~12 bytes long. The original keeps
 * row and i as live counters and recomputes the 2D address `ptr + row*0x40 + i*2`
 * with shifts each iteration; mwcc strength-reduces it into walking pointers
 * (row += 0x40, i-offset += 2), forcing extra callee-saved registers. Neither the
 * flat `*(u16*)(...+row*0x40+i*2+0x17b8)` nor the array-index
 * `((u16*)(ptr+0x17b8))[row*0x20+i]` form suppresses the induction variables.
 * Same class as the other loop-rotation ties. Semantics exact: fills a 3x4 grid
 * of tiles (base id 0x54++) with palette (param_2+5) at ptr+0x17b8. */
extern char data_ov003_0204f9a0[];
extern int func_ov003_0204cadc(int a);

void func_ov003_0204d6c8(int obj, short param_2) {
    int base = func_ov003_0204cadc(obj);
    unsigned short v = 0x54;
    int row = 0;
    int i;
    do {
        for (i = base + 2; i < base + 6; i++) {
            *(unsigned short *)(*(int *)data_ov003_0204f9a0 + row * 0x40 + i * 2 + 0x17b8) =
                v | (param_2 + 5) * 0x1000;
            v++;
        }
        row++;
    } while (row < 3);
}
