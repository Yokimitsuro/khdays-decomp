/* Steps the animation cursor at +0x20 through func_0203d040, resolves the resulting frame
 * out of data_02042264 into a 0x10-byte record and applies it to the sub-object at +0xa0.
 *
 * ★ The struct ladder: with the cursor written as `*(int *)(o + 0x20)` mwcc copies the call
 * result into r2 BEFORE storing it; as the struct field `o->a` it stores r0 first and then
 * copies, exactly as the ROM does. */
typedef struct {
    char pad[0x20];
    int cursor;
    int limit;
} Obj;

extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(void *out, void *tbl, int idx);
extern void func_0203c9d0(char *p, void *m);
extern char data_02042264[];

void func_ov245_020d3f34(int *ctx) {
    char m[0x10];
    char *self = (char *)ctx[0];
    Obj *o = (Obj *)ctx[1];
    o->cursor = func_0203d040(o->cursor, o->limit, *(int *)(self + 0x2c), 0);
    func_0202f188(m, data_02042264, o->cursor);
    func_0203c9d0(*(char **)o + 0xa0, m);
}
