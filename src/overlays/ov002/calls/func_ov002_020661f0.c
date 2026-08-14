/* Advance the alternating page value, unless the scene is shutting down.
 *
 * The owner points at a record 0x14 bytes into the table per index; its first word is a counter,
 * and what gets handed on is that counter plus one reduced modulo two, so the value alternates
 * between zero and one. The four-instruction shift and reverse-subtract sequence in the original
 * is exactly that signed modulo, not a bit trick.
 *
 * The value is computed before the shutdown check, which is why the original keeps it in a
 * callee-saved register across the call.
 */

extern char *data_ov002_0207f99c;
extern char data_ov002_0207f9a0[];
extern int func_ov002_0206b7a4(void);
extern void func_ov002_02065940(int parity, int arg);

void func_ov002_020661f0(int arg) {
    int parity = (*(int *)(data_ov002_0207f9a0 + *(int *)(data_ov002_0207f99c + 4) * 0x14) + 1) % 2;

    if (func_ov002_0206b7a4() != 0) {
        return;
    }
    func_ov002_02065940(parity, arg);
}
