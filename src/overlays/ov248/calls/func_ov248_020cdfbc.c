/* Roll a fresh 1..4 timer into (child)+0x50, then pose the actor per its phase byte at
 * (child)+0x5c (ov107 anim + local sub-pose), and register the handler. */
extern int func_02023eb4(int a);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov248_020cd510(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov248_020ce08c(int);
void func_ov248_020cdfbc(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x50) = func_02023eb4(3) + 1;
    switch (*(int *)(child + 0x5c)) {
        case 0:
            func_ov107_020c9264(*(int *)child, 2, 0);
            func_ov248_020cd510(*(int *)child, 1);
            break;
        case 2:
            func_ov107_020c9264(*(int *)child, 8, 0);
            func_ov248_020cd510(*(int *)child, 6);
            break;
        case 3:
            func_ov107_020c9264(*(int *)child, 5, 0);
            func_ov248_020cd510(*(int *)child, 4);
            break;
        case 1:
            func_ov107_020c9264(*(int *)child, 0xb, 0);
            func_ov248_020cd510(*(int *)child, 8);
            break;
    }
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov248_020ce08c);
}
