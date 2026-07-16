/* NONMATCHING: THUMB (symbols.txt: kind:function(thumb,size=0xe4)) -- verify with --thumb,
 * otherwise you get a meaningless 392-vs-228 "gap" from an ARM compile. Real gap: 234 vs 228,
 * 3 THUMB instructions.
 *
 * Switch-dispatch register-allocation tie. The ROM keeps db in r5 and the jump-table temp in
 * r4 (push {r3,r4,r5,lr}); mwcc 3.0/139 keeps db in r4 and uses r1 for the temp (push {r4,lr}),
 * needing two callee-saved registers fewer. The compiler generates the whole table-dispatch
 * preamble (cmp #32 / bhi / adds / add pc), so the register choice is not C-steerable. */
/* MsgDb_FetchRecord: dispatch a message-record fetch by db kind (param_2). Db
 * 0..0x12 use the generic decoder; 0x13..0x20 each have a dedicated decoder. */
extern int func_02034e3c(int rec, int a, int b, int c);
extern int func_02034730(int rec, int a, int b);
extern int func_020349ec(int rec, int a, int b);
extern int func_0203445c(int rec, int a, int b);
extern int func_02034660(int rec, int a, int b, int c);
extern int func_02034d40(int rec, int a, int b, int c);
extern int func_020347ec(int rec, int a, int b);
extern int func_0203488c(int rec, int a, int b);
extern int func_02034918(int rec, int a, int b);
extern int func_0203498c(int rec, int a, int b);
extern int func_02034ac0(int rec, int a, int b);
extern int func_02034b5c(int rec, int a, int b);
extern int func_02034c04(int rec, int a, int b);
extern int func_02034ca0(int rec, int a, int b);
int func_020342e8(int param_1, int param_2, int param_3, int param_4) {
    switch (param_2) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
    case 0xa: case 0xb: case 0xc: case 0xd: case 0xe: case 0xf: case 0x10: case 0x11: case 0x12:
        return func_02034e3c(param_1, param_3, param_4, param_2);
    case 0x13:
        return func_02034730(param_1, param_3, param_4);
    case 0x14:
        return func_020349ec(param_1, param_3, param_4);
    case 0x15:
        return func_0203445c(param_1, param_3, param_4);
    case 0x16:
        return func_02034660(param_1, param_3, param_4, param_4);
    case 0x17:
    case 0x18:
        return func_02034d40(param_1, param_3, param_4, param_2);
    case 0x19:
        return func_020347ec(param_1, param_3, param_4);
    case 0x1a:
        return func_0203488c(param_1, param_3, param_4);
    case 0x1b:
        return func_02034918(param_1, param_3, param_4);
    case 0x1c:
        return func_0203498c(param_1, param_3, param_4);
    case 0x1d:
        return func_02034ac0(param_1, param_3, param_4);
    case 0x1e:
        return func_02034b5c(param_1, param_3, param_4);
    case 0x1f:
        return func_02034c04(param_1, param_3, param_4);
    case 0x20:
        return func_02034ca0(param_1, param_3, param_4);
    default:
        return 0;
    }
}
