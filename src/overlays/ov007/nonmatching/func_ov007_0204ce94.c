/* Equivalent, readable C. NOT byte-exact: 4B short (128 vs 132). The original
 * holds the cursor index in ip and converts it to idx*2 in place (lsl ip,ip,#1),
 * reusing that for both the newline test and the copy source, an idx-caching +
 * register-coloring shape mwcc does not reproduce from clean C (no mwcc
 * generation matches — verify_sweep). The asm stub keeps the blob byte-exact. */
/* Copy one line (until a NUL or a 0x0a newline) from the source buffer at +0x74,
 * starting at cursor +0x78, into the +0x7c line buffer; advances the cursor past
 * the consumed chars (and past the newline) and NUL-terminates the destination. */
void func_ov007_0204ce94(int p) {
    int idx = *(int *)(p + 0x78);
    int base = *(int *)(p + 0x74);
    unsigned short s = *(unsigned short *)(base + idx * 2);
    int n = 0;

    if (s != 0) {
        do {
            if (*(unsigned short *)(base + idx * 2) == 10) {
                *(int *)(p + 0x78) = *(int *)(p + 0x78) + 1;
                break;
            }
            *(int *)(p + 0x78) = *(int *)(p + 0x78) + 1;
            *(unsigned short *)(p + n * 2 + 0x7c) = *(unsigned short *)(*(int *)(p + 0x74) + idx * 2);
            n++;
            idx = *(int *)(p + 0x78);
            base = *(int *)(p + 0x74);
            s = *(unsigned short *)(base + idx * 2);
        } while (s != 0);
    }
    *(unsigned short *)(p + n * 2 + 0x7c) = 0;
}
