/* Note that a peer acknowledged: raise that peer's bit in the mask at +0x8d9d,
 * skipping our own slot. Outside a live session there are no peers, so the
 * standalone flag at +0x8d9c is set instead. The sender's slot is the byte at
 * +1 of the message. */
extern int func_02030694(void);
extern int func_02030788(void);

extern char *data_ov002_0207fa00;

void func_ov002_0206c764(char *message) {
    char *root = data_ov002_0207fa00;
    int slot;

    if (func_02030694() != 0) {
        slot = *(unsigned char *)(message + 1);

        if (slot == func_02030788()) {
            return;
        }

        *(unsigned char *)(root + 0x8d9d) |= 1 << slot;
        return;
    }

    *(unsigned char *)(root + 0x8d9c) = 1;
}
