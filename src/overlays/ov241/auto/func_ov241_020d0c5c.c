/* Target hook caller of the ov241 enemy: hands the +0x30 target's +0x1b4 kind to
 * the actor's +0x3b4 target hook when one is installed. */
void func_ov241_020d0c5c(int *node)
{
    int *state = (int *)node[1];

    /* the hook takes the target kind and the actor (r1 keeps the actor live) */
    if (*(void (**)(int, int))(*state + 0x3b4) != 0) {
        (*(void (**)(int, int))(*state + 0x3b4))(*(unsigned char *)(state[0xc] + 0x1b4), *state);
    }
}
