/*
 * func_ov002_020582d0 - run a per-index callback then submit a selected preset value (ARM).
 *
 * Snapshots a 3-word preset table (data_ov002_0207dda8) onto the stack, invokes the callback `cb`
 * once per index i in 0..param_3-1 as cb(param_1, i, param_5), then submits the preset selected by
 * param_5 to func_ov002_02057260(param_2, preset[param_5]). The preset copy is kept as a local so
 * the indexed read is bounds-local to the snapshot.
 */
typedef struct { int a, b, c; } Ov002Triple;

extern Ov002Triple data_ov002_0207dda8;
extern void func_ov002_02057260(int a, int b);

void func_ov002_020582d0(int param_1, int param_2, int param_3,
                         void (*cb)(int, int, int), int param_5)
{
    Ov002Triple local = data_ov002_0207dda8;
    int i;
    for (i = 0; i < param_3; i++) {
        cb(param_1, i, param_5);
    }
    func_ov002_02057260(param_2, ((int *)&local)[param_5]);
}
