/* Copy the record into this machine's own 16-byte slot of the shared block. The
 * slot index is a THREE-BIT field in the low bits of the halfword at +0xc.
 * Clients other than the host have nothing to write. */
extern int func_02030788(void);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

extern char *data_ov022_020b2ea4;

typedef struct {
    char pad0000[0xc];
    unsigned short wSlot : 3;
} Ov022Record;

void func_ov022_0208973c(char *self, unsigned int size) {
    char *shared = data_ov022_020b2ea4;
    unsigned int slot = ((Ov022Record *)self)->wSlot;

    if (func_02030788() != 0) {
        return;
    }

    MI_CpuCopy8(self, shared + 0x58 + slot * 16, size);
}
