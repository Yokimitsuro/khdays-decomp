/* Sweep all 0x18 slots: for each one the id resolver accepts, walk the object
 * list hanging off +0xc4 of its 0x184-byte record and retire every entry whose
 * kind byte at +0x2c is below 6. The next pointer is read BEFORE the callee runs,
 * because the callee may unlink the entry. */
extern int func_ov002_0207285c(int slot);
extern void func_ov002_02077df0(void *entry);

extern char *data_ov002_0207fa28;

void func_ov002_02078f60(void) {
    char *next;
    int i = 0;
    int offset = 0;

    for (; i < 0x18; i++) {
        if (func_ov002_0207285c(i) >= 0) {
            char *entry = *(char **)((&data_ov002_0207fa28)[1] + offset + 0xc4);

            if (entry != 0) {
                do {
                    next = *(char **)entry;

                    if (*(unsigned char *)(entry + 0x2c) < 6) {
                        func_ov002_02077df0(entry);
                    }
                    entry = next;
                } while (entry != 0);
            }
        }
        offset += 0x184;
    }
}
