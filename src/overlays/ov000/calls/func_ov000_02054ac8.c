#pragma thumb on
/* Scene 1 (boot/logo) save-signature check. Allocates a 0x20-byte scratch buffer, fills it from
 * the save device, and answers 1 only if all four 8-byte blocks match the reference signature.
 * A read error answers 0. The scratch buffer is freed on every path.
 *
 * Parked as a register-allocation tie -- mwcc was spilling the buffer pointer to the stack and
 * holding the constant 8 in a register instead. The whole difference is `r = offset;` in place of
 * `r = 0;`. The original copies its already-zeroed offset into the counter (`movs r5,#0` then
 * `adds r4,r5,#0`) rather than materialising a second zero, and that one extra live constant is
 * what pushed the pointer out of a register. When the original moves one just-zeroed register
 * into another, the source assigned one variable FROM the other. */

extern char data_ov000_0205ab80[];
extern void *NNS_FndAllocFromDefaultExpHeapEx(int size, int align);
extern int  func_ov000_02054914(int dev, void *buf, int size);
extern int  func_0201f844(void *a, void *b, int n);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

int func_ov000_02054ac8(void) {
    int r;
    char *buf = (char *)NNS_FndAllocFromDefaultExpHeapEx(0x20, 0x20);
    if (func_ov000_02054914(0, buf, 0x20) != 0) {
        r = 0;
    } else {
        void *ref = *(void **)data_ov000_0205ab80;
        int offset = 0;
        r = offset;
        do {
            if (func_0201f844(buf + offset, ref, 8) != 0) {
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
