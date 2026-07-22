/* Fills one command slot and queues it; silently drops the command when the pool is dry. */
extern char *SND_AllocCommand(int wait);
extern void func_02008788(char *cmd);

void PushCommand_impl(int cmd, int a, int b, int c, int d) {
    char *slot = SND_AllocCommand(1);
    if (slot == 0) {
        return;
    }
    *(int *)(slot + 4) = cmd;
    *(int *)(slot + 8) = a;
    *(int *)(slot + 0xc) = b;
    *(int *)(slot + 0x10) = c;
    *(int *)(slot + 0x14) = d;
    func_02008788(slot);
}
