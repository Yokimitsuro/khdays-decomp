/* UPDATE 2026-07-18 -- the size is now RIGHT; only one register differs.
 *
 * ⚠ The old note here said the ROM's split signed load
 * (`add r1,r3,#0x100; ldrsb [r1,#0xc9]`) could not be reproduced -- "No C form keeps the
 * signed". That was WRONG, and the answer was already in the skill's codegen-cracks.md:
 * on a byte-to-byte copy the DESTINATION's signedness decides too. The source read was
 * already `signed char`, but the destination was `unsigned char`, which lets mwcc collapse
 * the whole thing to one `ldrb [r3,#0x1c9]` (-4 B). Making BOTH sides signed keeps the
 * ROM's two-instruction split.
 *
 * What is left: the ROM materialises the `1` into r1 (`mov r1,#1 ; str r1,[r5,#0x58]`),
 * keeping r0 free for the `ldr r0,[r5,#8]` that feeds the next call; mwcc uses r0 and
 * reloads. Ruled out: `int one = 1;` temp, and the word-index spelling `((int *)obj)[0x16]`.
 */
extern void func_ov146_020ce298(int arg);
extern void func_0203c634(int self, int index, void *cb);
struct hw60 { unsigned short lo:8, hi:8; };
void func_ov146_020ccdf4(int self) {
    int obj = *(int *)(self + 4);
    if ((((struct hw60 *)(*(int *)obj + 0x60))->lo & 1) == 0) {
        return;
    }
    *(int *)(obj + 0x58) = 1;
    func_ov146_020ce298(*(int *)(obj + 8));
    *(signed char *)(*(int *)obj + 0x1c7) = *(signed char *)(*(int *)obj + 0x1c9);
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
