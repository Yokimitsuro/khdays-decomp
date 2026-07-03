/*
 * func_ov031_020b4930  (x4 family: ov031/ov050/ov070/ov088)  216 bytes
 *
 * Advance a projectile/sub-object: bump its lifetime (param2[4] += dt), build a
 * biased target vector (param2[0xcc] copy, y-=0x5000) and a staging vector
 * (const data_02041dc8, y+=0xa000); while lifetime <= func_0202aef8()-0x9000
 * keep steering via func_ov022_02091b48; then run the death check
 * (func_ov022_02091540) which may set state 3 -> zero lifetime + func_ov022_02091d80.
 *
 * Semantically equivalent, matches at the exact 216-byte size EXCEPT a pure
 * register-coloring tie: the orig holds the timer result in r3 (`mov r3,r0`),
 * computes the threshold early into lr (`sub lr,r3,#0x9000`, held across the loop),
 * and keeps the staging-vector pointer &data_02041dc8 in the callee-saved r7
 * (so its push list is {r3,r4,r5,r6,r7,lr}). mwcc from any equivalent C instead
 * computes the threshold directly (no r3 save -> 1 instr shorter, 212B) or, when
 * `result` is held live to the compare, colors result->ip and the const ptr->r0
 * (216B but push {r4,r5,r6,lr}). Neither spelling reproduces the orig's early
 * threshold + r7-held const ptr. Held-value-vs-late-compute coloring class;
 * unsteerable by source form. asm stub stays byte-exact.
 *
 * NOTE: the staging vector (buf0) is copied and adjusted (y+=0xa000) but never
 * read afterwards in the compiled code; the orig keeps the dead store (atomic
 * struct copy is not DSE'd), which this equivalent reproduces via a struct copy.
 */
extern struct v3 data_02041dc8;

struct v3 { int x, y, z; };
struct frame { struct v3 buf0; struct v3 buf1; };

extern int func_0202aef8(int a, int b);
extern void func_ov022_02091b48(int this, int param2, struct v3 *v);
extern int func_ov022_02091540(int a, int b, int c);
extern void func_ov022_02091d80(int this, int param2);

int func_ov031_020b4930(int this, int param2, int param3) {
    struct frame f;
    int threshold = func_0202aef8(param2 + 0x28, 0) - 0x9000;

    f.buf1 = *(struct v3 *)(param2 + 0xcc);
    f.buf0 = data_02041dc8;
    *(int *)(param2 + 4) += param3;
    f.buf1.y -= 0x5000;
    f.buf0.y += 0xa000;
    if (*(int *)(param2 + 4) <= threshold) {
        func_ov022_02091b48(this, param2, &f.buf1);
    }
    *(char *)(param2 + 2) = 4;
    if (func_ov022_02091540(param2 + 0x28, param3, 4) != 0) {
        *(char *)(param2 + 2) = 3;
    }
    if (*(signed char *)(param2 + 2) == 3) {
        *(int *)(param2 + 4) = 0;
        func_ov022_02091d80(this, param2);
    }
    return 0;
}
