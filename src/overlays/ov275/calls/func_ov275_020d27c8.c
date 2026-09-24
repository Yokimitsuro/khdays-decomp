/* Ov275_WaitNotStaggered -- state step of the ov274-family enemy: unless the owner's +0x310 state is
 * 3 or 4, sets sub-items 0, 1, 2 and 4 to (2, 0) and moves the node's slot on to 020d2854. */
extern void func_0203b9fc(int rig, int idx, int blend, int value);
extern int func_0203c634(int node, int slot, void *handler);
extern void func_ov275_020d2854(int node);

void func_ov275_020d27c8(int node)
{
    int child = *(int *)(node + 4);
    signed char nState = *(signed char *)(*(int *)child + 0x310);

    if (nState != 4 && nState != 3) {
        func_0203b9fc(*(int *)(child + 4), 0, 2, 0);
        func_0203b9fc(*(int *)(child + 4), 1, 2, 0);
        func_0203b9fc(*(int *)(child + 4), 2, 2, 0);
        func_0203b9fc(*(int *)(child + 4), 4, 2, 0);
        func_0203c634(node, *(signed char *)(node + 0x20), (void *)&func_ov275_020d2854);
        return;
    }
}
