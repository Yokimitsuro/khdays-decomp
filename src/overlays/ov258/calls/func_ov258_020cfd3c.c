extern void func_ov258_020cff94(int target, int a, int b, int c);
/* If the object is in state 1 (obj+0x50), forward (a,b,c) to the sub-target (obj+0x214) handler. */
void func_ov258_020cfd3c(int obj, int a, int b, int c) {
    if (*(int *)(obj + 0x50) != 1) {
        return;
    }
    func_ov258_020cff94(*(int *)(obj + 0x214), a, b, c);
}
