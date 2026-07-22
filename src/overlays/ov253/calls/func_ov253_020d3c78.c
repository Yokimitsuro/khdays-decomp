/* Copies the 44-byte transform block and hands over to the follow-up.
 *
 * ★ The eleven-word ldm/stm block copy IS reachable from C: it is a plain struct
 * assignment of a `struct { int w[11]; }`.  mwcc emits exactly the ROM's
 * `ldm!{r0-r3} / stm!{r0-r3}` twice plus `ldm{r0-r2} / stm{r0-r2}`.  This retires the
 * "11-word block-copy" class that had five functions parked against it. */
typedef struct { int w[11]; } Blk44;

extern void func_ov107_020c6980(char *self, int flag);

void func_ov253_020d3c78(char *self, int flag) {
    func_ov107_020c6980(self, flag);
    *(Blk44 *)(*(char **)(self + 0x39c) + 0x10) = *(Blk44 *)(self + 0xa0);
}
