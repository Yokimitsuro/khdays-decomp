extern int ScriptVm_ReadOperandInt(void *state, void *operands);
extern int GameState_SetField(int query, int kind, int value);

/* Script op: store its operand, the current party-slot index, into stat key 0x2080 (kind 5). The
 * interpreter calls it with its state and the op's operands, which go straight on to the reader. */
int Ov019_StoreSlotIndex(void *state, void *operands) {
    int slot = ScriptVm_ReadOperandInt(state, operands);
    GameState_SetField(0x82 << 6, 5, (unsigned short)slot);
    return 0;
}
