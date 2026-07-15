/* func_ov000_0205324c -- store a value into the logo scene block, ov000.
 * If the scene block (*data_ov000_0205ac24) exists, writes `value` to its field
 * @+0x4af8 only when the gate field @+0x6a48 (low 16 bits) is zero; otherwise it
 * clears that field to 0. */
extern char *data_ov000_0205ac24;
void func_ov000_0205324c(int value) {
    char *base = data_ov000_0205ac24;
    if (base == 0) {
        return;
    }
    if ((short)*(int *)(base + 0x6a48) == 0) {
        *(short *)(base + 0x4af8) = value;
        return;
    }
    *(short *)(base + 0x4af8) = 0;
}
