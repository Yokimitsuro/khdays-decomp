/* Scene hook of the ov258 enemy: removes its two +0x458 items from the scene (arg 1) and
 * chains to the common handler. */
extern int func_ov107_020c2b38(int scene, int item);
extern int func_ov107_020c7c1c(int *self, int scene);

int func_ov258_020cc540(int *r0, int r1)
{
    signed char i;

    for (i = 0; i < 2; i++) {
        func_ov107_020c2b38(r1, r0[i + 0x116]);
    }
    return func_ov107_020c7c1c(r0, r1);
}
