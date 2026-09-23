/* Scene hook of the ov258 enemy: adds its two +0x458 items to the scene (arg 1) and
 * chains to the common handler. */
extern int func_ov107_020c2b20(int scene, int item);
extern int func_ov107_020c7b70(int *self, int scene);

int func_ov258_020cc4fc(int *r0, int r1)
{
    signed char i;

    for (i = 0; i < 2; i++) {
        func_ov107_020c2b20(r1, r0[i + 0x116]);
    }
    return func_ov107_020c7b70(r0, r1);
}
