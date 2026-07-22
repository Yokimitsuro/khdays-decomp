/* Opens sub-object `id`: resets its counter at +0x1e8, records the id, arms it (+0x1f0 = 1),
 * pushes the per-id parameter word into the sub-block at +0x200, runs the fallback when
 * func_ov025_020af364 reports nothing pending, and finally kicks func_ov025_020af748. */
extern char *func_ov025_02084b14(int id);
extern void func_ov025_020b0818(char *p, unsigned short v);
extern int func_ov025_020af364(void);
extern void func_ov025_020af3ac(void);
extern void func_ov025_020af748(void);
extern int data_ov025_020b5588[];

void func_ov025_020afd4c(int id) {
    char *o = func_ov025_02084b14(id);
    *(int *)(o + 0x1e8) = 0;
    *(int *)o = id;
    *(int *)(o + 0x1f0) = 1;
    func_ov025_020b0818(o + 0x200, (unsigned short)data_ov025_020b5588[id]);
    if (func_ov025_020af364() == 0) {
        func_ov025_020af3ac();
    }
    func_ov025_020af748();
}
