/* Sweep all 0x18 slots and retire every list entry that still carries a pending
 * word at +0x28, then mark the sweep done by setting +0x58 of the shared record.
 * Sibling of func_ov002_02078f60, which sweeps the same lists on the kind byte
 * instead. The next pointer is read before the callee runs because the callee
 * unlinks the entry. */
extern int func_ov002_0207285c(int slot);
extern void func_ov002_02077df0(void *entry);

extern char *data_ov002_0207fa28;

void func_ov002_02077e68(void) {
    char *next;
    int i = 0;
    int offset = 0;

    for (; i < 0x18; i++) {
        if (func_ov002_0207285c(i) >= 0) {
            char *entry = *(char **)((&data_ov002_0207fa28)[1] + offset + 0xc4);

            if (entry != 0) {
                do {
                    next = *(char **)entry;

                    if (*(int *)(entry + 0x28) != 0) {
                        func_ov002_02077df0(entry);
                    }
                    entry = next;
                } while (entry != 0);
            }
        }
        offset += 0x184;
    }

    *(int *)((&data_ov002_0207fa28)[1] + 0x58) = 1;
}
