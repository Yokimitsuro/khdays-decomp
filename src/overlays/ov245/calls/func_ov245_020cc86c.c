/* func_ov245_020cc86c -- on a kind-0 message, publish the object's two 32-bit counters (+0x4d0,
 * +0x4d4) into the message's two halfword slots (+0x24, +0x26) before forwarding it.
 * Both sides are written as ARRAY INDICES WITH THE FIELD OFFSET FOLDED IN
 * (`((int *)self)[i + 0x134]`, `((unsigned short *)msg)[i + 0x12]`), which is what keeps the ROM's
 * `add r3, base, i lsl #N` instead of a strength-reduced running pointer. */
extern void func_ov107_020c7a90(int self, void *msg, int arg);

void func_ov245_020cc86c(int self, unsigned char *msg, int arg) {
    int i;
    if (msg[2] == 0) {
        for (i = 0; i < 2; i++) {
            ((unsigned short *)msg)[i + 0x12] = (unsigned short)((int *)self)[i + 0x134];
        }
    }
    func_ov107_020c7a90(self, msg, arg);
}
