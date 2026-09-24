/* Ov244_WaitRigIdle -- state step of the ov274-family enemy: once the rig's +0xad busy byte is clear,
 * sets sub-items 0, 4, 1 and 2 to (1, 1) and moves the node's slot on to 020cef68. */
extern void func_0203b9fc(int rig, int idx, int blend, int value);
extern int func_0203c634(int node, int slot, void *handler);
extern void func_ov244_020cef68(int node);

void func_ov244_020ceee8(int node)
{
    int child = *(int *)(node + 4);

    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) == 0) {
        func_0203b9fc(*(int *)(child + 4), 0, 1, 1);
        func_0203b9fc(*(int *)(child + 4), 4, 1, 1);
        func_0203b9fc(*(int *)(child + 4), 1, 1, 1);
        func_0203b9fc(*(int *)(child + 4), 2, 1, 1);
        func_0203c634(node, *(signed char *)(node + 0x20), (void *)&func_ov244_020cef68);
        return;
    }
}
