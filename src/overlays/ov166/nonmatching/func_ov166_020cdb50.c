/* NONMATCHING — equivalent C, one scheduling tie.
 *
 * The func_ov107_020c0b90 struct-by-value (Vec3) marshaling is byte-exact; the
 * only difference vs the ROM is a load-use hoist in the guard block: mwcc 3.0
 * emits `ldr r0,[r4]; mov r1,#2; mov r2,#0` ABOVE the `bne` (hiding the
 * ldr->strb stall), whereas every source form we can write keeps that setup
 * inside the fall-through block. Confirmed unreproducible across all 26 mwcc
 * generations, 7 source structures, and the scheduling pragmas. Otherwise
 * byte-identical (correct size, all relocs aligned). */
struct vec3 { int x, y, z; };

extern int func_ov107_020cab14(int obj, int b);
extern void func_0203c634(int obj, int slot, void *cb);
extern void func_ov107_020c9264(void);
extern void func_ov107_020c0b90(int obj, int cmd, struct vec3 v, int flag);
extern void func_ov166_020cdbec(void);

/* Begin the grab/throw pose: acquire the target (020cab14); if none, fall back to
 * sub-state 2. Otherwise play the pose, reset the timer and a flag byte, push the
 * target's stored offset vector to the render hook, and advance to the hold
 * handler (020cdbec). */
void func_ov166_020cdb50(int param_1) {
    int *piVar3 = *(int **)(param_1 + 4);
    int iVar1 = func_ov107_020cab14(*piVar3, 0);

    piVar3[3] = iVar1;
    if (iVar1 == 0) {
        *(unsigned char *)(*piVar3 + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
        return;
    }
    func_ov107_020c9264();
    piVar3[0x12] = 0;
    *(unsigned char *)((char *)piVar3 + 0x84) = 0;
    {
        struct vec3 v = *(struct vec3 *)piVar3[2];
        func_ov107_020c0b90(*piVar3, 0, v, 0);
    }
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), func_ov166_020cdbec);
}
