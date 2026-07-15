/* FrameStep_UpdateTaskQueue: drain the GFX command queue (ctx @ data_02047370). If the
 * time budget (ctx+0x10) is exhausted (>= 0x2400) flush the data cache once; then for each
 * queued command call func_020114ac(cmd, underBudget) and debit its cost (cmd[3]) from the
 * budget. func_02011538 fetches the next command, func_02011558 advances/decrements. */
extern int *func_02011538(int *q);
extern int func_02011558(int *q);
extern void func_020114ac(int *cmd, int flag);
extern void DC_StoreAll(void);
extern char data_02047370;

void func_020115b8(void) {
    int *ctx = (int *)&data_02047370;
    unsigned int *bud = (unsigned int *)((char *)&data_02047370 + 0x10);
    int *cmd;
    unsigned char flag;
    cmd = func_02011538(ctx);
    flag = *bud < 0x2400;
    if (flag == 0) {
        DC_StoreAll();
    }
    if (func_02011558(ctx) != 0) {
        do {
            func_020114ac(cmd, flag);
            *(int *)((char *)ctx + 0x10) -= cmd[3];
            cmd = func_02011538(ctx);
        } while (func_02011558(ctx) != 0);
    }
}
