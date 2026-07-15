/* NONMATCHING: semantics correct, r4/r5 register-allocation tie. The ROM keeps
 * self in r5 and obj in r4; mwcc 3.0/139 assigns the opposite (self->r4, obj->r5),
 * so every base register is swapped (size identical, byte diff @0x5). The matched
 * sibling ov256_020ce778 gets obj->r4 because its first call takes an obj-derived
 * value (obj urgently needed in a callee-saved reg); here the only intervening call
 * (func_020235e8) uses neither self nor obj, so mwcc falls back to param-first
 * (self->r4). No source form (raw cast or int* obj) flips it.
 *
 * c634 state-entry handler: init obj fields (f48=0, f14=0x23000, f78=1, f7c=1),
 * fire func_020235e8(0x20b7, 8), latch owner->+0x1c7 = obj->f74 + 2, then dispatch
 * state with a null callback. self->+0x20 = slot index. */
extern void func_020235e8(int a, int b);
extern void func_0203c634(int self, int index, void *cb);
void func_ov256_020cd8f0(int self) {
    int obj = *(int *)(self + 4);
    *(int *)(obj + 0x48) = 0;
    *(int *)(obj + 0x14) = 0x23000;
    *(int *)(obj + 0x78) = 1;
    *(int *)(obj + 0x7c) = 1;
    func_020235e8(0x20b7, 8);
    *(unsigned char *)(*(int *)obj + 0x1c7) = *(int *)(obj + 0x74) + 2;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
