extern int data_ov022_020b2ec0;
struct Ent020b2240 { char pad0[4]; unsigned char tag; unsigned char v; char pad6[6]; };
int func_ov022_020b2240(int arg0) {
    struct Ent020b2240 *e = (struct Ent020b2240 *)(data_ov022_020b2ec0 + 0xc) + arg0;
    if (e->tag != 0) return e->v;
    return -1;
}
