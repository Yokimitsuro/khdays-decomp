/* NONMATCHING: semantics correct, codegen tie. mwcc 3.0/139 folds the index
 * multiply `idx * 0x4030` into a single `ldr 0x4030; muls`, but the ROM keeps the
 * factored form `(idx << 1) * 0x2018` (extra lsls + mov, +4 bytes). No natural C
 * form reproduces the split (constant*constant always folds; tried raw *0x30,
 * *0x4030, (idx<<1)*0x2018, materialized intermediate, and variable/inline array
 * subscript with a 0x2018-stride struct — all fold to one muls). Same tie for the
 * whole family (ov000_02054e48, and its byte-identical twins).
 *
 * Notify func_02020904, stash param_1 as the active byte index in the global
 * (data_0205ac2c[1], clearing [0]), then dispatch func_ov000_020549fc with the
 * byte offset of slot data[1]'s +0x20 field (slot stride 0x4030) and data_0204be14. */
extern void func_02020904(int param_1);
extern void func_ov000_020549fc(int offset, int arg);
extern unsigned char data_ov000_0205ac2c[];
extern int data_0204be14;
void func_ov000_02054e48(int param_1) {
    func_02020904(param_1);
    data_ov000_0205ac2c[0] = 0;
    data_ov000_0205ac2c[1] = (unsigned char)param_1;
    func_ov000_020549fc(data_ov000_0205ac2c[1] * 0x4030 + 0x20, data_0204be14);
}
