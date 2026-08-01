/*
 * Game_ActionTurnHandler - action-slot handler for a "turn" command; one of the two cancel
 * sentinels the action system recognises by address (see Game_UnwindActionStack /
 * Game_RunActionScript). param_1 is the action-system state, param_2 the turn angle.
 *
 * A negative angle is the cancel/finish path: -0x63 is normalised to 0, the residual angle is
 * released via func_0202ba44((-angle) & 0xffff), and it returns 1 (slot done). Otherwise, when the
 * controlled actor is still active (func_0201eea8 on the actor at *(*(state+0x128)+0x28)+0xc), it
 * fires the turn effect func_0202b984(angle, actor, 0, 0) and applies the rotation via
 * func_020219b4(state, -angle) - using -0x63 as the marker when the angle is 0 - and returns 0
 * (keep the slot). If the actor is inactive it just returns 0.
 *
 * THUMB. The angle is signed (branch-if-negative selects the cancel path); the -0x63 sentinel is
 * built with mvns (~0x62); the two func_020219b4 calls share the return-0 tail.
 */

extern void func_0202ba44(int angle);
extern int  func_0201eea8(int arg);
extern void func_0202b984(int id, int obj, int a, int b);
extern void func_020219b4(int param_1, int angle);

int func_020225f0(int param_1, int param_2)
{
    if (param_2 < 0) {
        if (param_2 == -0x63) {
            param_2 = 0;
        }
        func_0202ba44(-param_2 & 0xffff);
        return 1;
    }
    if (func_0201eea8(*(int *)(*(int *)(*(int *)(param_1 + 0x128) + 0x28) + 0xc)) != 0) {
        func_0202b984(param_2 & 0xffff, *(int *)(*(int *)(param_1 + 0x128) + 0x28), 0, 0);
        if (param_2 == 0) {
            func_020219b4(param_1, -0x63);
        } else {
            func_020219b4(param_1, -param_2);
        }
    }
    return 0;
}
