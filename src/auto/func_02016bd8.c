/* ⚠ The `idx` PARAMETER is reused as the element pointer. That is not a liberty -- it is
 * what the ROM does: the mla writes its result into r1, the register `idx` arrived in, and
 * the whole downstream allocation follows from that. Giving the element its own local makes
 * mwcc pick r0 (the dead `obj` register) instead and every later register shifts.
 * Reads like macro-generated accessor code. */
void func_02016bd8(int obj, unsigned int idx, unsigned int val, int slot) {
    int container;
    int result;
    if (obj != 0 && (slot = *(int *)(obj + 8)) != 0) container = obj + slot;
    else container = 0;
    if (container != 0) {
        int base = container + 4;
        if (base != 0 && idx < *(unsigned char *)(container + 5)) {
            unsigned int off = *(unsigned short *)(container + 10);
            idx = (idx * *(unsigned short *)(base + off) + (base + off + 4));
        } else {
            idx = 0;
        }
        if (idx != 0) {
            result = container + *(int *)idx;
            goto done;
        }
    }
    result = 0;
done:
    *(unsigned int *)(result + 0xc) = *(unsigned int *)(result + 0xc) & ~0x1f0000U | (val << 16);
}
