/* ScriptVm_ResolveOperand - resolves a bytecode operand reference (cmd) against the current
 * action-state context entry (st->entries[st->ctx], stride 0x48) into an 8-byte OperandSlot
 * {kind; pad; value}. See src/calls/func_02021948.c, func_02021980.c, func_02021994.c and
 * func_020222bc.c for consumers that already establish this slot layout and kind values
 * (1 = immediate, 0x10 = ?, 0x40 = table-indexed, 0 = empty).
 *
 * cmd->mode is the addressing mode:
 *  - 8: the slot already lives at cur->table + cmd->field; return that computed address
 *       directly.
 *  - 4: cmd->field is a raw literal; convert it via func_020235d0 (split into its low and high
 *       halfwords) and store the immediate slot {kind=1, value=result} in the per-state scratch
 *       slot; return that scratch slot.
 *  - bit 0x80 clear: the command words already form a valid slot in place; return cmd itself.
 *  - bit 0x80 set: further decode using cmd->sel as a byte offset into cur->table: the index
 *       comes from func_020235d0(cmd->field) when bit 4 is set, from
 *       *(cur->table + cmd->field + 4) when bit 8 is set, otherwise straight from cmd->field.
 *       Store {kind = cmd->mode & ~0x8c, value = *(cur->table + sel + index*4)} into the
 *       per-state scratch slot and return it.
 *
 * THUMB.
 */

typedef struct {
    short kind;
    short pad;
    int   value;
} OperandSlot;

typedef struct {
    short mode;   /* addressing mode */
    short sel;    /* byte offset into cur->table, used when mode has bit 0x80 set */
    int   field;  /* literal / offset payload, meaning depends on mode */
} OperandCmd;

typedef struct {
    char  pad[0x14];
    char *table;  /* +0x14: base of this context's index-lookup table */
} CtxEntry;

typedef struct {
    char        pad0[0x124];
    int         ctx;    /* +0x124: index of the active context entry */
    char        pad1[0x578 - 0x128];
    OperandSlot slot;   /* +0x578: per-state scratch slot for resolved literals */
} ScriptVmState;

extern int func_020235d0(unsigned short lo, unsigned short hi);

OperandSlot *func_020218a4(ScriptVmState *st, OperandCmd *cmd)
{
    CtxEntry *cur = (CtxEntry *)((char *)st + 4 + st->ctx * 0x48);
    int mode = cmd->mode;
    OperandSlot *result;

    if (mode == 8) {
        result = (OperandSlot *)(cur->table + cmd->field);
    } else if (mode == 4) {
        unsigned v;
        st->slot.kind = 1;
        v = (unsigned)cmd->field;
        st->slot.value = func_020235d0((unsigned short)v, (unsigned short)(v >> 16));
        result = &st->slot;
    } else if ((mode & 0x80) == 0) {
        result = (OperandSlot *)cmd;
    } else {
        int sel = cmd->sel;
        int idx;
        if (mode & 4) {
            unsigned v = (unsigned)cmd->field;
            idx = func_020235d0((unsigned short)v, (unsigned short)(v >> 16));
        } else if (mode & 8) {
            idx = *(int *)(cur->table + cmd->field + 4);
        } else {
            idx = cmd->field;
        }
        {
            short kind = (short)(cmd->mode & ~0x8c);
            st->slot.kind = kind;
            st->slot.value = *(int *)(cur->table + sel + (idx << 2));
        }
        result = &st->slot;
    }
    return result;
}
