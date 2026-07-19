extern int func_ov002_0207285c(int slot);
extern int func_ov002_0207298c(int id);
extern int func_ov002_02072754(int id);
extern char data_ov002_0207fa28;

/* Records whether any spawn slot is currently running state 9 of routine 3, and clears the
 * pending-request field. */
void func_ov002_02077eb4(void) {
    int found = 0;
    int i;
    int id;
    for (i = 0; i < 0x18; i++) {
        id = func_ov002_0207285c(i);
        if (id >= 0 && func_ov002_0207298c(id) == 3 && func_ov002_02072754(id) == 9) {
            found = 1;
        }
    }
    *(int *)(*(char **)((char *)&data_ov002_0207fa28 + 4) + 0x2524) = found;
    *(int *)(*(char **)((char *)&data_ov002_0207fa28 + 4) + 0x58) = 0;
}
