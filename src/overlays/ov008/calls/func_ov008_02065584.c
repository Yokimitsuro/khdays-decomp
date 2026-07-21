/* Set obj+0x4c to 1 if any active game slot (1..0x276) is currently flagged in the shared state
 * bitmap at data_0204be18[+0x810]; otherwise leave it 0. */
extern int func_ov008_0205ccd8(int slot);
extern unsigned char *data_0204be18;

void func_ov008_02065584(int obj) {
    int i;
    *(int *)(obj + 0x4c) = 0;
    i = 1;
    do {
        if (func_ov008_0205ccd8(i) != 0 && data_0204be18[i + 0x810] != 0) {
            *(int *)(obj + 0x4c) = 1;
            return;
        }
        i++;
    } while (i < 0x277);
}
