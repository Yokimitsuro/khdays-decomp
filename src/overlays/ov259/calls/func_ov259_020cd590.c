/* Pick the ov259 actor's +8 target: kind 0 takes the nearest foe (020cab14), kind 1 the helper
 * pick of 020d15bc. */
extern int func_ov107_020cab14(int obj, int kind);
extern int func_ov259_020d15bc(int obj, int kind);

void func_ov259_020cd590(int *node, int kind)
{
    int *state = (int *)node[1];

    switch (kind) {
    case 0:
        state[2] = func_ov107_020cab14(*state, 0);
        break;
    case 1:
        state[2] = func_ov259_020d15bc(*state, 0);
        break;
    }
}
