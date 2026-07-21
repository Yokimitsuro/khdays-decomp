extern int func_02023930(int desc, int arg);
extern char data_ov002_0207fa18[];
extern char data_ov002_0207f40c[];
/* Lazily instantiate the subsystem's class (descriptor data_0207f40c) into the slot at
 * data_0207fa18+4. */
void func_ov002_02075f98(void) {
    if (*(int *)(data_ov002_0207fa18 + 4) == 0) {
        *(int *)(data_ov002_0207fa18 + 4) = func_02023930((int)data_ov002_0207f40c, 0);
    }
}
