/* Counts the entries of the list at +0x44 whose bit 1 at +0x40 is set.
 *
 * The flag is a SIGNED one-bit bitfield: the ROM extracts it with `lsl #30 / asrs #31`
 * (which yields -1 or 0) and branches on `ne`.  An unsigned bitfield would give lsr, and
 * a plain `& 2` would give a tst. */
typedef struct {
    int pad[16];
    signed int b0 : 1;
    signed int b1 : 1;
} Flags;

extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);

int func_ov107_020c2034(char *self) {
    int n = 0;
    void *node = func_01fffd70(self + 0x44);
    while (node != 0) {
        if (((Flags *)(*(char **)node))->b1 != 0) {
            n = n + 1;
        }
        node = func_01fffd8c(self + 0x44);
    }
    return n;
}
