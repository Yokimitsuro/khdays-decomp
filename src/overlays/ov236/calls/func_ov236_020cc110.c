/* Copies the 44-byte transform block and hands over to the follow-up.
 *
 * ★ The eleven-word ldm/stm block copy IS reachable from C: it is a plain struct
 * assignment of a `struct { int w[11]; }`.  mwcc emits exactly the ROM's
 * `ldm!{r0-r3} / stm!{r0-r3}` twice plus `ldm{r0-r2} / stm{r0-r2}`.  This retires the
 * "11-word block-copy" class that had five functions parked against it. */
typedef struct { int w[11]; } Blk44;

extern void func_0203bc78(char *self, int a);

void func_ov236_020cc110(char *self, int a) {
    *(Blk44 *)(self + 0x30) = *(Blk44 *)(*(char **)(*(char **)(self + 0x84) + 0x384) + 0x30);
    func_0203bc78(self, a);
}
