/* NONMATCHING — register-coloring + scheduling tie (28/28, byte-equivalent). The
 * ROM keeps the global base in r2 and schedules the param_1<<2 shift early; mwcc
 * colors the base r1 and hoists the tail-call target load ahead of the shift. Same
 * opcodes and immediates otherwise. Unsteerable; the raw blob keeps it byte-exact.
 *
 * Forward the entry at *(global+4) + 0x200 + param_1*4 to func_02025640. */
extern int func_02025640(int entry);
extern int data_ov002_0207fa20;

int func_ov002_02076968(int param_1) {
    return func_02025640(*(int *)((char *)&data_ov002_0207fa20 + 4) + 0x200 + param_1 * 4);
}
