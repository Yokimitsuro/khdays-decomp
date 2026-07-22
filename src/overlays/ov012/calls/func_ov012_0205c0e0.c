/* func_ov012_0205c0e0 -- MobiClip: fetch and present one record from a stream.
 * Spins on func_ov012_0205bcf0 while it reports 1 (not ready yet) and gives up if it reports 0.
 * The record's own duration lives in its signed byte at +2, biased by the stream's +0x88, and
 * that is what the stream position (+0x58) advances by at the end.
 * If presenting it would run past the stream's limit (+0x40), the stream is stepped first and a
 * failed step aborts the whole thing.
 * The record is then handed to func_0202fb58 twice: once at (pos+1, pos2+1) with mode 2, once at
 * (pos, pos2) with the stream's own mode (+0x60) -- the +1 pass first. Both take the record by
 * address as a fifth argument on the stack.
 *
 * Parked at ONE instruction described as a "dead register copy the ROM has and mwcc coalesces
 * away" (`mov r2,r0 ; cmp r2,#1 ; beq loop ; cmp r2,#0` against mwcc's compares straight on r0),
 * with a `switch` form ruled out. It is not a dead copy: r2 is the THIRD ARGUMENT of
 * func_0202fafc, which is declared with two here and defined with three
 * (tools/audit_extern_sig.py names it). The spin's status code is what the fetch is called with,
 * so the copy has to survive both compares. A register copy that looks dead is the arity smell --
 * the same lesson as the trailing-zero argument, from the other end: here the value is live and
 * the ARGUMENT was missing, not the constant.
 *
 * Two things that were already right and must be kept:
 * 1. The out-param is an 8-BYTE struct, not a bare pointer: the ROM reserves 0xc of locals
 *    (4 for the outgoing 5th argument + 8 for the struct), giving `push {r4,r5,lr} ; sub sp,#0xc`.
 * 2. The `status != 0` case must be an if/else with `return 0` LAST, so the zero-exit lands out of
 *    line; as an early `if (status == 0) return 0;` guard mwcc predicates it inline.
 */
typedef struct {
    signed char *rec;
    int unk4;
} Ov024_RecordRef;

extern int func_ov012_0205bcf0(int stream);
extern void func_0202fafc(int stream, Ov024_RecordRef *out, int status);
extern int func_ov012_0205bbac(int stream);
extern void func_0202fb58(int stream, int a, int b, int mode, Ov024_RecordRef *ref);

int func_ov012_0205c0e0(int stream) {
    Ov024_RecordRef ref;
    int status;
    int advance;

    do {
        status = func_ov012_0205bcf0(stream);
    } while (status == 1);

    if (status != 0) {
        func_0202fafc(stream, &ref, status);
        advance = ref.rec[2] + *(int *)(stream + 0x88);
        if (*(int *)(stream + 0x58) + advance > *(int *)(stream + 0x40)) {
            if (func_ov012_0205bbac(stream) == 0) {
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
