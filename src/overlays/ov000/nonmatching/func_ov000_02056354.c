/* NONMATCHING (if-conversion tie): body is semantically exact but mwcc 139 predicates
 * the outer `02056144(...) && k.c != target` (ldrhne/cmpne, 292B) whereas the ROM keeps
 * two separate branches (teq + beq to the shared tail, 296B). Resisted nested-if,
 * flag-first-decl, and explicit goto restructuring. 8-member family ov000/002/005/006/
 * 008/009/025/026. Re-resolve param_1's active target and snapshot/notify on change. */
typedef void (*fn0)(void);
typedef void (*fn1)(int);
struct key { unsigned short a, b, c, d; };
struct bit0 { unsigned int b : 1; };
extern int func_ov000_02056144(int obj, struct key *out);
extern void *NNS_FndGetNextListObject(void *list, void *prev);
extern int func_ov000_02055f84(unsigned int a, unsigned int b, int e);
extern void MI_CpuCopy8(void *dst, void *src, unsigned int n);
void func_ov000_02056354(unsigned int *param_1, unsigned int param_2, unsigned int param_3,
                         unsigned int param_4) {
    int flag = 1;
    struct key k;
    int e;
    if (!func_ov000_02056144((int)param_1, &k)) goto done;
    if (k.c == *(unsigned short *)((char *)param_1 + 0x20)) goto done;
    if (k.c == 0) {
        if (param_1[6] != 0 && *(int *)(param_1[6] + 0x28) != 0) {
            (*(fn0)param_1[0xf])();
            param_1[6] = 0;
        }
    } else if (k.d == 0) {
        for (e = (int)NNS_FndGetNextListObject(param_1, 0); e != 0;
             e = (int)NNS_FndGetNextListObject(param_1, (void *)e)) {
            if (*(int *)(e + 0x24) != 0 && ((struct bit0 *)(e + 0x20))->b == 0 &&
                func_ov000_02055f84(k.a, k.b, e)) {
                MI_CpuCopy8(&k, (char *)param_1 + 0x1c, 8);
                flag = 0;
                (*(fn1) * (int *)(e + 0x24))(e);
                param_1[6] = e;
                if (*(int *)(e + 0x28) != 0) {
                    (*(fn0)param_1[0xf])();
                }
                break;
            }
        }
    }
done:
    if (flag) {
        MI_CpuCopy8(&k, (char *)param_1 + 0x1c, 8);
    }
}
