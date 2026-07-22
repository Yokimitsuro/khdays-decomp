/* Copies the 44-byte transform from the source block at ctx[1] into +4 of ctx[0] and, when
 * ctx[0]'s busy byte at +0xad is clear, hands over to func_0203c640.
 * (The eleven-word block copy is a plain struct assignment -- see func_ov236_020cc110.) */
typedef struct { int w[11]; } Blk44;

extern void func_0203c640(char *self);

void func_ov107_020c0acc(char *self) {
    char **ctx = *(char ***)(self + 4);
    *(Blk44 *)((char *)ctx[0] + 4) = *(Blk44 *)ctx[1];
    if (*(unsigned char *)(ctx[0] + 0xad) != 0) {
        return;
    }
    func_0203c640(self);
}
