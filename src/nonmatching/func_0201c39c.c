/*
 * SndLoadWaveData (func_0201c39c) -- NON-MATCHING (kept as asm_stub for byte-exactness).
 *
 * This C is semantically exact and compiles to the SAME 200 bytes as the original,
 * but mwcc's register allocator assigns a register PERMUTATION we cannot steer from
 * source: the four saved params colour to r4-r7 while the original reserves r4 for
 * `start` and places the params at r5-r8 (with size at r9). Every instruction, immediate
 * and control-flow edge is identical -- only the callee-saved register numbers differ.
 * Tried: declaration order, `register`, split count/end vars, compute-order permutations,
 * pointer-typed handle, start-loaded-early. None move `start` off r8/r9 onto r4.
 *
 * Loads (and decompresses) the wave data for entry `idx` of a sound bank if it is not
 * already resident. The bank keeps an entry table at handle+(handle[0x38]+idx)*4 whose
 * fields hold each wave's start offset (+0x3c) and the next entry's start (+0x40); the
 * size is end-start (end = the next entry's start, or the bank end handle[8] for the last
 * entry). A scratch buffer of size+0x20 is allocated, the wave is decoded into it, the
 * data cache is flushed, and the resolved address is stored back into the bank.
 */

extern int   SND_GetWaveDataAddress(int handle, unsigned int idx);   /* func_02009230 */
extern int   SND_GetWaveDataCount(int handle);                        /* func_020091f4 */
extern void  SND_SetWaveDataAddress(int handle, unsigned int idx, void *buf); /* func_020091fc */
extern void  DC_StoreRange(void *buf, unsigned int size);             /* func_0200275c */
extern unsigned int func_0201b6f4(unsigned int a, void *buf, unsigned int size, int start);
extern void *func_0201b9a0(void *dest, unsigned int size, void *cb, int handle, unsigned int idx);
extern void  func_0201c354(void);   /* per-load callback passed to the allocator */

int func_0201c39c(int handle, unsigned int idx, unsigned int param3, void *dest)
{
    unsigned int end;
    int start;
    unsigned int size;
    int *entry;
    void *buf;

    if (SND_GetWaveDataAddress(handle, idx) != 0)
        return 1;

    end = SND_GetWaveDataCount(handle) - 1;                     /* reused: count-1, then end */
    entry = (int *)(handle + (*(int *)(handle + 0x38) + idx) * 4);
    if (idx < end)
        end = *(unsigned int *)((char *)entry + 0x40);         /* next entry's start */
    else
        end = *(unsigned int *)(handle + 8);                    /* bank end for the last entry */
    start = *(int *)((char *)entry + 0x3c);
    size = end - start;

    if (dest == 0)
        return 0;

    buf = func_0201b9a0(dest, size + 0x20, func_0201c354, handle, idx);
    if (buf == 0)
        return 0;

    if (func_0201b6f4(param3, buf, size, start) == size) {
        DC_StoreRange(buf, size);
        SND_SetWaveDataAddress(handle, idx, buf);
        return 1;
    }
    return 0;
}
