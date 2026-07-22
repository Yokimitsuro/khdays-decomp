/* Does `value` still fit the budget at +0x20? A budget with its top bit set is
 * the "unlimited" marker and always fits. Otherwise the measurement helper turns
 * the value into a cost against the descriptor at +0x2c, and anything over
 * budget fails.
 *
 * The budget word is read TWICE -- once as a flag word for the top-bit test and
 * once as a signed magnitude after the call. Caching it in a local would be a
 * stale read across the call as well as a mismatch. */
extern int func_01ff8e94(int value, void *descriptor);

typedef struct {
    char pad0000[0x20];
    unsigned int dwBudget;      /* +0x20, top bit = unlimited */
    char pad0024[8];
    char descriptor[1];         /* +0x2c */
} Ov002BudgetObject;

int func_ov002_0207018c(Ov002BudgetObject *self, int value) {
    if ((self->dwBudget & 0x80000000) != 0) {
        return 1;
    }

    if (func_01ff8e94(value, self->descriptor) > (int)self->dwBudget) {
        return 0;
    }

    return 1;
}
