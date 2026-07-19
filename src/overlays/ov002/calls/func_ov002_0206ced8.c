extern int func_02023588(int id);
extern void func_020235a8(int id);
extern int func_ov022_02086ef4(void);
extern int func_ov022_02086f24(void);
extern int func_ov002_0206b7a4(void);
extern void func_ov022_02083fa4(int a);
extern char *data_ov002_0207fa00;

/* Keeps the field music in step with the mission state: switches to the alternate track while
 * the trigger is armed, otherwise restores the normal one and re-arms the ambience. */
void func_ov002_0206ced8(void) {
    char *self = data_ov002_0207fa00 + 0x8c94;
    if (func_02023588(0x2086) != 0 && func_ov022_02086ef4() != 0 &&
        func_ov022_02086f24() == 0) {
        func_020235a8(0x20e2);
    } else if (func_02023588(0x20e2) == 0 && func_ov002_0206b7a4() == 0) {
        func_020235a8(0x20e2);
        if (*(int *)(self + 0xc) > 0) {
            func_ov022_02083fa4(0);
        }
    }
    func_02023588(0x20e2);
}
