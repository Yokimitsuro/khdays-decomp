/* func_ov008_02080770 -- title screen per-frame state function, ov006.
 * Copies the 15-entry sub-state handler table (data_ov008_0208fd8c) to the stack, runs the
 * per-frame title helpers (func_ov008_02080e74 input/logic, func_ov008_02080ad8 animation),
 * updates the shared object (func_ov008_020554e4 on obj+8), then dispatches the current
 * sub-state's handler (obj[0x94f4] indexes the table) when it is valid (>= 0), and finishes
 * with the three render/commit passes (func_ov008_0207fac4 / 02054ab0 / 02053fd0). */
struct Table15 { void (*fn[15])(void); };
extern struct Table15 data_ov008_0208fd8c;
extern int *data_ov008_02090fa4;
extern void func_ov008_02080e74(void);
extern void func_ov008_02080ad8(void);
extern void func_ov008_020554e4(void *p);
extern void func_ov008_0207fac4(void);
extern void func_ov008_02080820(void);
extern void func_ov008_0207fd40(void);

int func_ov008_02080770(void) {
    struct Table15 tbl = data_ov008_0208fd8c;
    int st;
    func_ov008_02080e74();
    func_ov008_02080ad8();
    func_ov008_020554e4((char *)data_ov008_02090fa4 + 8);
    st = *(int *)((char *)data_ov008_02090fa4 + 0x94f4);
    if (-1 < st) {
        tbl.fn[st]();
    }
    func_ov008_0207fac4();
    func_ov008_02080820();
    func_ov008_0207fd40();
    return 0;
}
