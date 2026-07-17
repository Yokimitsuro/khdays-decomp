/* NONMATCHING: semantics correct; CSE-recompute tie on &data_020565e4 -- mwcc caches it in a
 * callee-saved reg (r4) and reuses after the call (48B), the ROM keeps it in a caller-saved reg
 * and rematerialises for the store (52B). Same class as func_ov006_02050970. */
/* func_ov006_0204faf0 -- lazily create the Mission Mode-screen sub-controller instance.
 * If the instance slot (&state+4) is already populated, do nothing; otherwise instantiate the
 * class descriptor data_ov006_020563c0 with argument param_1 and store the result there. */
extern int func_02023930(int class_desc, int arg);   /* InstantiateClass */
extern int data_ov006_020565e4;   /* Mission Mode-screen state struct: [1] = instance handle */
extern int data_ov006_020563c0;   /* class descriptor */

void func_ov006_0204faf0(int param_1) {
    if (*(int *)((int)&data_ov006_020565e4 + 4) != 0) {
        return;
    }
    *(int *)((int)&data_ov006_020565e4 + 4) =
        func_02023930((int)&data_ov006_020563c0, param_1);
}
