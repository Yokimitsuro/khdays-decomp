#pragma thumb on
/* func_ov000_02054ac8 -- Scene 1 (boot/logo) save-signature check, ov000. THUMB.
 * NONMATCHING: register-allocation tie. The retail build keeps the scratch buffer
 * in a callee-saved register across the loop (re-materializing the constant 8 per
 * iteration); our mwcc instead holds 8 in a register, strength-reduces buf+offset
 * to an advancing pointer, and spills buf to the stack (+2 THUMB instr). Logic is
 * byte-exact otherwise. Kept readable for the PC port.
 *
 * Allocates a scratch 0x20-byte buffer, fills it from the save device
 * (func_ov000_02054914); on read error returns 0. Otherwise it compares all four
 * 8-byte blocks of the buffer against the reference signature (*data_ov000_0205ab80)
 * via func_0201f844, returning 1 only if every block matches, else 0. Frees the
 * scratch buffer before returning. */

extern char data_ov000_0205ab80[];
extern void *NNS_FndAllocFromDefaultExpHeapEx(int size, int align);
extern int  func_ov000_02054914(int, void *buf, int size);
extern int  func_0201f844(void *a, void *b, int n);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

int func_ov000_02054ac8(void) {
    int r;
    void *buf = NNS_FndAllocFromDefaultExpHeapEx(0x20, 0x20);
    if (func_ov000_02054914(0, buf, 0x20) != 0) {
        r = 0;
    } else {
        void *ref = *(void **)data_ov000_0205ab80;
        int offset = 0;
        r = 0;
        do {
            if (func_0201f844((char *)buf + offset, ref, 8) != 0) {
                break;
            }
            r++;
            offset += 8;
        } while (r < 4);
        r = (r == 4);
    }
    NNSi_FndFreeFromDefaultHeap(buf);
    return r;
}
