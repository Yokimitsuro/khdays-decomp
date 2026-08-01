/*
 * Game_ActionInitObject - action-command handler that (re)initialises the object slot owned by the
 * current actor. Returns the interpreter result 2 (advance/clear) when it runs, or 0 when the slot's
 * object id is still in use.
 *
 * The slot lives at param_1 + 0x594 + param_1[0] (a per-actor block). If its id is not free
 * (Obj_IsIdFree), the command yields (return 0). Otherwise, when the slot already holds the tag
 * 'CAKP' (0x504b4143) it is torn down first (func_02025464), then the command's operand descriptor
 * at param_2[4] (byte +8) is resolved (func_02021948) - or null when absent - and the slot is
 * (re)built via func_02021ef4 with the actor's active parameter block
 * (param_1[(param_1[0x49]+1)*0x12+2]).
 *
 * THUMB. Matching notes: the slot base (param_1+0x594) and param_1[0] are held in registers and
 * re-added at each use rather than caching the summed pointer; param_2 is a short* so it stays in a
 * callee-saved register across the calls (as an int it is spilled to the stack instead); the
 * operand test is written `if (desc != 0) resolve; else null;` so the null case is the branch
 * target; and the active-parameter index uses the byte form (x+1)*0x48+8.
 */

extern int  func_0201eea8(int id);
extern void func_02025464(int *slot, int a);
extern int  func_02021948(int *self, unsigned short *desc);
extern void func_02021ef4(int *self, int *slot, int a, unsigned int *operand);

int func_020220dc(int *param_1, short *param_2)
{
    char *slotBase = (char *)param_1 + 0x594;
    int base = *param_1;
    int iVar2;
    unsigned int *operand;

    if (func_0201eea8((int)(slotBase + base)) == 0) {
        return 0;
    }
    if (*(int *)(slotBase + base) == 0x504b4143) {
        func_02025464((int *)(slotBase + base), 0);
    }
    iVar2 = *(int *)((char *)param_1 + (param_1[0x49] + 1) * 0x48 + 8);
    if (param_2[4] != 0) {
        operand = (unsigned int *)func_02021948(param_1, (unsigned short *)(param_2 + 4));
    } else {
        operand = 0;
    }
    func_02021ef4(param_1, (int *)(slotBase + base), iVar2, operand);
    return 2;
}
