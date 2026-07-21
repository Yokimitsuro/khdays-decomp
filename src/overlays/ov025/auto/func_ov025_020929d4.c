/* Scan the 64-bit "slot in use" bitmap at +0x58 for the first free slot (bit clear); return its
 * id (index + 0x65), or -1 if all 40 slots are taken. */
int func_ov025_020929d4(int obj) {
    unsigned int i = 0;
    do {
        if ((*(long long *)(obj + 0x58) & (1LL << i)) == 0) {
            return i + 0x65;
        }
        i++;
    } while ((int)i < 0x28);
    return -1;
}
