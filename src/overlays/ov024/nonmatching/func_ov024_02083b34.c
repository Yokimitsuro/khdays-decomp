/* func_ov024_02083b34 -- MobiClip: fetch and present one record from a stream.
 * Spins on func_ov024_02083744 while it reports 1 (not ready yet) and gives up if it reports 0.
 * The record's own duration lives in its signed byte at +2, biased by the stream's +0x88, and
 * that is what the stream position (+0x58) advances by at the end.
 * If presenting it would run past the stream's limit (+0x40), the stream is stepped first and a
 * failed step aborts the whole thing.
 * The record is then handed to func_0202fb58 twice: once at (pos+1, pos2+1) with mode 2, once at
 * (pos, pos2) with the stream's own mode (+0x60) -- the +1 pass first. Both take the record by
 * address as a fifth argument on the stack.
 *
 * NONMATCHING: 240/244 bytes. Everything matches except ONE redundant instruction the ROM has and
 * mwcc coalesces away: the ROM copies the status into r2 and compares r2 twice
 * (`mov r2,r0 ; cmp r2,#1 ; beq loop ; cmp r2,#0`), where mwcc just compares r0 in place. Dead
 * register copy -- the same class as the `movs r4,r0 ; cmpne r4,#0` note in state.md.
 * Tried and rejected: `switch (status) { case 0: ... default: ... }` instead of the if, on the
 * theory that a switch selector would earn its own register. It does not; still 240.
 *
 * Two things here DID matter and must be kept if anyone retries:
 * 1. The out-param is an 8-BYTE struct, not a bare pointer. Only the record pointer is ever read,
 *    but the ROM reserves 0xc of locals (4 for the outgoing 5th argument + 8 for the struct). With
 *    a bare `signed char *rec` you get `push {r3,r4,r5,lr} ; sub sp,#8` -- same total stack, wrong
 *    split -- instead of the ROM's `push {r4,r5,lr} ; sub sp,#0xc`.
 * 2. The `status != 0` case must be an if/else with `return 0` LAST, so the zero-exit lands out of
 *    line at the end. Written as an early `if (status == 0) return 0;` guard, mwcc predicates it
 *    inline (addeq/moveq/popeq) and comes out 4 B shorter.
 */
/* The out-param is 8 bytes -- the ROM reserves 0xc of locals for it plus the outgoing fifth
 * argument -- but only the record pointer is ever read here. */
typedef struct {
    signed char *rec;
    int unk4;
} Ov024_RecordRef;

extern int func_ov024_02083744(int stream);
extern void func_0202fafc(int stream, Ov024_RecordRef *out);
extern int func_ov024_02083600(int stream);
extern void func_0202fb58(int stream, int a, int b, int mode, Ov024_RecordRef *ref);

int func_ov024_02083b34(int stream) {
    Ov024_RecordRef ref;
    int status;
    int advance;

    do {
        status = func_ov024_02083744(stream);
    } while (status == 1);

    if (status != 0) {
        func_0202fafc(stream, &ref);
        advance = ref.rec[2] + *(int *)(stream + 0x88);
        if (*(int *)(stream + 0x58) + advance > *(int *)(stream + 0x40)) {
            if (func_ov024_02083600(stream) == 0) {
                return 0;
            }
        }

        func_0202fb58(stream,
                      *(int *)(stream + 0x58) + *(unsigned short *)(stream + 0x48) + 1,
                      *(int *)(stream + 0x5c) + *(unsigned short *)(stream + 0x4c) + 1,
                      2, &ref);
        func_0202fb58(stream,
                      *(int *)(stream + 0x58) + *(unsigned short *)(stream + 0x48),
                      *(int *)(stream + 0x5c) + *(unsigned short *)(stream + 0x4c),
                      *(int *)(stream + 0x60), &ref);

        *(int *)(stream + 0x58) += advance;
        return 1;
    }
    return 0;
}
