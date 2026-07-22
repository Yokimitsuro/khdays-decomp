extern int func_01fffd8c(int list);
extern void func_0203bfb4(int ctx, int *subscriber);
extern void func_ov107_020c4e9c(int obj, int scene);

void func_ov107_020c7b70(int obj, int scene) {
    int i;

    if (*(int *)(obj + 0x50) == 1 && *(void (**)(void))(obj + 0x30) != 0) {
        (*(void (**)(void))(obj + 0x30))();
    }
    {
        int sign = (*(int *)(scene + 0x40) << 0x1e) >> 0x1f;
        void (*cb)(int, int) = *(void (**)(int, int))(obj + 0x14);
        if (cb != 0) {
            cb(obj, sign);
        }
    }
    {
        int seq = 0;
        int node = func_01fffd70(obj + 0x22c);
        while (node != 0) {
            *(char *)(node + 4) = seq;
            seq++;
            node = func_01fffd8c(obj + 0x22c);
        }
    }
    func_0203bfb4(*(int *)(scene + 0x104), *(int **)(obj + 0x1a8));
    {
        int *node = (int *)func_01fffd70(obj + 0x260);
        while (node != 0) {
            func_0203bfb4(*(int *)(scene + 0x104), (int *)*node);
            node = (int *)func_01fffd8c(obj + 0x260);
        }
    }
    {
        int cur = obj;
        for (i = 0; i < 8; i++) {
            if (*(int *)(cur + 0x350) != 0) {
                int *sub = *(int **)(*(int *)(cur + 0x350) + 0x14);
                if (sub != 0) {
                    func_0203bfb4(*(int *)(scene + 0x104), sub);
                }
            }
            cur += 4;
        }
    }
    func_ov107_020c4e9c(obj, scene);
}

/* PARK -- 4 bytes, down from 16, and the old note's diagnosis was wrong.
 *
 * Previous note: "register-allocation/scheduling tie ... residue is ~8 instructions of
 * callee-saved coloring (cb in r7 where the ROM uses r2 and re-reads) and temp scheduling
 * across a 172B body with three loops." It was 188 bytes against 172 at the time.
 *
 * The size was a PHANTOM THIRD ARGUMENT. func_0203bfb4 takes TWO arguments -- eight call
 * sites in the tree agree, including func_ov294_020d1a24 which is byte-exact -- and this
 * file declared it with three, passing `cb` as a "marker" at all three call sites. That is
 * also the whole reason cb sat in a callee-saved register: with the third argument gone it
 * is live only inside its own block, exactly as the old note observed the ROM behaving
 * ("uses r2 and re-reads"). Found by tools/audit_arity.py. Worth 12 of the 16 bytes.
 *
 * The remaining 4 came from `char seq`: the ROM keeps the sequence counter in a plain int
 * and narrows only at the `strb`, while a `char` counter costs lsl#24/asr#24 on every
 * increment. `int seq` with the store left as `*(char *)(node + 4) = seq;` fixes it.
 *
 * WHAT IS ACTUALLY LEFT is two instructions at the top, and it is an ordering question, not
 * a size one:
 *     ROM   adds r4,r0,#0 ; adds r6,r1,#0 ; ldr r1,[r4,#0x50] ; cmp r1,#1
 *     mwcc  adds r4,r0,#0 ; ldr r0,[r4,#0x50] ; adds r6,r1,#0 ; cmp r0,#1
 * The ROM banks BOTH parameters into callee-saved registers before touching anything, which
 * frees r1 as the scratch; mwcc defers the `scene` copy because scene is not read until
 * later, and so has to use r0. Ruled out this round, all failing identically at 0x4:
 * `i` declared inside the for; the guard value hoisted into a local; the `&&` split into
 * nested ifs; and the callback pulled into a local before the null test.
 *
 * So the search space is now two instructions wide and the semantics are settled. The next
 * axis to try is something that makes `scene` live early -- not more permutations of the
 * first block.
 */
