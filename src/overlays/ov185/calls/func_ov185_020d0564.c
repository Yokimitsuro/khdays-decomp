/* c634 handler: clear owner hw60 hi bits 0x8c, set bit0 of owner+0x1ae, clear bit0 of the
 * low byte at *(owner+0x388)+8, then query the aim target (func_ov107_020cab14). If found,
 * fetch its transform into obj[6..9] (func_ov185_020d0028) and copy it to obj[2..5]. Finally
 * notify func_ov107_020c9264(owner,0,0) and dispatch via func_0203c634. */
struct hw60 { unsigned short lo:8, hi:8; };
struct b8 { unsigned int b:8; };
struct vec4 { int a, b, c, d; };
extern int func_ov107_020cab14(int owner, int a);
extern void func_ov185_020d0028(int *obj, int *out);
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov185_020d0634(void);
void func_ov185_020d0564(int self) {
    int *obj = *(int **)(self + 4);
    ((struct hw60 *)(*obj + 0x60))->hi &= ~0x8c;
    *(unsigned short *)(*obj + 0x1ae) |= 1;
    ((struct b8 *)(*(int *)(*obj + 0x388) + 8))->b &= ~1;
    obj[1] = func_ov107_020cab14(*obj, 0);
    if (obj[1] != 0) {
        func_ov185_020d0028(obj, obj + 6);
        *(struct vec4 *)(obj + 2) = *(struct vec4 *)(obj + 6);
    }
    func_ov107_020c9264(*obj, 0, 0);
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov185_020d0634);
}
