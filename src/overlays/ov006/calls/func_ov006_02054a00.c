/* func_ov006_02054a00 -- Mission Mode per-frame state function, ov006.
 * Copies the 15-entry sub-state handler table (data_ov006_020562d0) to the stack, runs the
 * per-frame Mission Mode helpers (func_ov006_02055104 input/logic, func_ov006_02054d68 animation),
 * updates the shared object (func_ov006_0204d110 on obj+8), then dispatches the current
 * sub-state's handler (obj[0x94f4] indexes the table) when it is valid (>= 0), and finishes
 * with the three render/commit passes (func_ov006_02053d54 / 02054ab0 / 02053fd0). */
struct Table15 { void (*fn[15])(void); };
extern struct Table15 data_ov006_020562d0;
extern int *data_ov006_02056664;
extern void func_ov006_02055104(void);
extern void func_ov006_02054d68(void);
extern void func_ov006_0204d110(void *p);
extern void func_ov006_02053d54(void);
extern void func_ov006_02054ab0(void);
extern void func_ov006_02053fd0(void);

int func_ov006_02054a00(void) {
    struct Table15 tbl = data_ov006_020562d0;
    int st;
    func_ov006_02055104();
    func_ov006_02054d68();
    func_ov006_0204d110((char *)data_ov006_02056664 + 8);
    st = *(int *)((char *)data_ov006_02056664 + 0x94f4);
    if (-1 < st) {
        tbl.fn[st]();
    }
    func_ov006_02053d54();
    func_ov006_02054ab0();
    func_ov006_02053fd0();
    return 0;
}
