/*
 * Obj_IsIdFree - test whether an object id is not currently in use in the object registry
 * (data_0204bc1c). The "current" entry is data_0204bbfc's owner at +4 -> +0x448.
 *
 * id 0 is a special query: returns true only when the registry is empty AND there is no current
 * entry. For a real id, returns false if the current entry owns it (entry+0x28 == id) or if any of
 * the registry's `count` (data_0204bc1c+0x1c) live slots owns it; the slots are visited by hashing a
 * running sequence value (data_0204bc1c+0x18, incremented) against the salt (+0x14) through
 * func_02020400 (a 64-bit divide; the quotient high word indexes the slot table at +0x10). Returns
 * true when the id is found in none of them.
 *
 * ARM. Matching notes: the registry base (data_0204bc1c) is held in one register across both the
 * id==0 path and the scan (hoisted to a local pointer, else mwcc re-materialises it per access); the
 * loop counter i is initialised before the `count > 0` guard so it takes the low callee-saved
 * register ahead of seq/table/salt; and func_02020400 is declared returning a 64-bit value so the
 * slot index is (int)(result >> 32).
 */

extern char data_0204bbfc[];
extern char data_0204bc1c[];
extern unsigned long long func_02020400(unsigned a, unsigned b);

int func_0201eea8(int param_1)
{
    char *reg = data_0204bc1c;
    int cur;
    int count;

    cur = *(int *)(*(int *)(data_0204bbfc + 4) + 0x448);
    if (param_1 == 0) {
        return *(int *)(reg + 0x1c) == 0 && cur == 0;
    }
    if (cur != 0 && *(int *)(cur + 0x28) == param_1) {
        return 0;
    }
    count = *(int *)(reg + 0x1c);
    {
        int i = 0;
        if (count > 0) {
            unsigned seq = *(unsigned *)(reg + 0x18);
            int *tbl = *(int **)(reg + 0x10);
            unsigned salt = *(unsigned *)(reg + 0x14);
            do {
                int e = tbl[(int)(func_02020400(seq, salt) >> 0x20)];
                if (e != 0 && *(int *)(e + 0x28) == param_1) {
                    return 0;
                }
                i++;
                seq++;
            } while (i < count);
        }
    }
    return 1;
}
