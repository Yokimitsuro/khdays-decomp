extern int ScriptVm_ReadOperandInt(void *state, void *operands);
extern int GameState_GetField(int query, int kind);
extern int GameState_SetField(int query, int kind, int value);
extern int Ov002_RetireAllSlotEntries(void);

/* Record a high-water mark: pick the stat key for the current party slot
 * (0->0x140b, 1->0x1415, else 0x141f) and, if the live value exceeds the stored
 * one, write it back. Then refresh the ov002 summary. A script op: the slot is its operand, read
 * with the interpreter's state and the op's operands as they come. */
int Ov019_RecordStatHighWater(void *state, void *operands) {
    int slot = ScriptVm_ReadOperandInt(state, operands);
    int cur = GameState_GetField(0x208f, 0xa);
    int key;

    if (slot == 0) {
        key = 0x140b;
    } else if (slot == 1) {
        key = 0x1415;
    } else {
        key = 0x141f;
    }
    if (cur > GameState_GetField(key, 0xa)) {
        GameState_SetField(key, 0xa, (unsigned short)cur);
    }
    Ov002_RetireAllSlotEntries();
    return 1;
}
