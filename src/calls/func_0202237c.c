/*
 * Game_ActionEnqueueCmdIfChanged - action-command handler (opcode table data_020425ec). Reads a
 * command id (cmd[0]) and an argument (cmd[4]) from the command stream. If the id differs from the
 * last one enqueued (the signed-byte global data_020425e8), it is dispatched to one of two queues
 * and recorded as the new last id:
 *   - ids in {1,6,8,0xa,0xc,0xe,0x11,0x22} go to func_02033770;
 *   - every other id goes to func_02033758.
 * Both queues receive (id & 0xff, arg). When the id is unchanged nothing happens. Returns 1.
 *
 * THUMB. The last-id global is read signed (ldrsb) and rewritten as a byte; the id byte is
 * materialised with the lsl#24/lsr#24 zero-extend pair, i.e. (unsigned char)id.
 */

typedef unsigned short u16;

extern int  func_02021980(int st, u16 *cmd);   /* ScriptVm_ReadOperandInt */
extern void func_02033770(int id, int arg);
extern void func_02033758(int id, int arg);
extern char data_020425e8;                      /* last enqueued command id */

int func_0202237c(int param_1, u16 *param_2)
{
    int uVar1 = func_02021980(param_1, param_2);
    int uVar2 = func_02021980(param_1, param_2 + 4);
    if (uVar1 != data_020425e8) {
        if (uVar1 == 1 || uVar1 == 6 || uVar1 == 8 || uVar1 == 0xa ||
            uVar1 == 0xc || uVar1 == 0xe || uVar1 == 0x11 || uVar1 == 0x22) {
            func_02033770((unsigned char)uVar1, uVar2);
        } else {
            func_02033758((unsigned char)uVar1, uVar2);
        }
        data_020425e8 = (char)uVar1;
    }
    return 1;
}
