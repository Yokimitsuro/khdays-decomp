/*
 * Game_PushObjectSlot - append a new object slot entry to the actor's slot array (param_1) and
 * fill it from a command descriptor. Each slot entry is 0x48 bytes; the count is param_1[0x49] and
 * the entries start at param_1+4. Advances the actor's byte cursor param_1[0] by size.
 *
 * The new entry (index param_1[0x49]+1) records the descriptor pointer and size, then wires up its
 * data cursors: when the descriptor starts with the tag 'CAKP' (0x504b4143) the payload is an
 * archive member resolved through func_020255d4(desc, 1, sub) - sub coming from the command operand
 * via func_02020ab4 when present, else 0 - so the data pointer is the member and the end pointer is
 * member + *member; otherwise the descriptor itself is the inline payload (data at desc+4, end at
 * desc + *desc). The remaining state words are zeroed and the trailing 0x28 bytes MemSet to 0.
 *
 * THUMB. Matching notes: the entry pointer (param_1+4 + (count+1)*0x48) is held in a register and
 * indexed by byte offset; the optional-operand test is written `if (operand != 0) resolve; else 0;`
 * so the null case is the branch target; the end-pointer reloads the stored data pointer (entry[2])
 * rather than reusing the local.
 */

extern int  func_02020ab4(int desc, unsigned *operand);
extern int  func_020255d4(int desc, int a, int b);
extern void MI_CpuFill8(void *dst, int val, int n);

void func_02021ef4(int *param_1, int *param_2, int param_3, unsigned *param_4)
{
    int iVar2 = param_1[0x49] + 1;
    int *e = (int *)((char *)param_1 + 4 + iVar2 * 0x48);
    int iVar1;

    *param_1 = *param_1 + param_3;
    e[1] = param_3;
    e[0] = (int)param_2;
    if (*param_2 == 0x504b4143) {
        if (param_4 != 0) {
            iVar1 = func_02020ab4((int)param_2, param_4);
        } else {
            iVar1 = 0;
        }
        iVar1 = func_020255d4((int)param_2, 1, iVar1);
        e[2] = iVar1;
        e[3] = iVar1 + 4;
        e[4] = iVar1 + 4;
        e[5] = e[2] + *(int *)e[2];
    } else {
        e[2] = (int)param_2;
        e[3] = (int)param_2 + 4;
        e[4] = (int)param_2 + 4;
        e[5] = (int)param_2 + *(int *)e[2];
    }
    e[6] = 0;
    e[7] = 0;
    MI_CpuFill8((char *)e + 0x20, 0, 0x28);
    param_1[0x49] = param_1[0x49] + 1;
}
