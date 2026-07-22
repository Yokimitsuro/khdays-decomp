/* func_ov023_02084c30 -- script VM command: re-run the actor whose index the operand names.
 * Actors are 0x104 bytes apart in the table at +0x128 of the VM state; the command ticks the
 * actor's +0x6c block (func_0202e3c4) and then its +0x30 block (func_02021060). Always reports 1
 * (command finished). */
extern int func_02021980(void *vm);
extern void func_0202e3c4(int p);
extern void func_02021060(int p);

int func_ov023_02084c30(void *vm) {
    int idx = func_02021980(vm);
    int off = (idx + idx * 64) * 4;
    func_0202e3c4(*(int *)((char *)vm + 0x128) + 0x6c + off);
    func_02021060(*(int *)((char *)vm + 0x128) + 0x30 + off);
    return 1;
}
