/*
 * func_ov002_0206c834 - raise a pending-request flag from a queued command (ARM).
 *
 * Dispatches on the command's sub-op byte against the global request word at base+0x8b64
 * (base = *(int*)&data_ov002_0207fa00): sub-op 0 sets bit 2 and kicks the audio cue
 * func_020235a8(0x2087); sub-op 1 sets bit 6. Any other sub-op is ignored.
 */
typedef struct {
    unsigned char _0;
    unsigned char subOp;   /* +1 */
} Ov002Cmd;

extern int data_ov002_0207fa00;
extern void func_020235a8(int cueId);

void func_ov002_0206c834(Ov002Cmd *cmd)
{
    int base = *(int *)&data_ov002_0207fa00;
    switch (cmd->subOp) {
    case 0:
        *(int *)(base + 0x8b64) |= 4;
        func_020235a8(0x2087);
        break;
    case 1:
        *(int *)(base + 0x8b64) |= 0x40;
        break;
    }
}
