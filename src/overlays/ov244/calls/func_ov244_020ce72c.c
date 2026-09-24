/* Ov244_WaitRigIdleBlendOut -- state step: once the rig's +0xad busy byte is clear, sets sub-items
 * 0, 2, 4 and 1 to (2, 0), refreshes the rig's callbacks and moves the node's slot on to 020ce7b8. */
extern void func_0203b9fc(int rig, int idx, int blend, int value);
extern void func_0203c7ac(int rig, int value);
extern int func_0203c634(int node, int slot, void *handler);
extern void func_ov244_020ce7b8(int node);

void func_ov244_020ce72c(int node)
{
    int child = *(int *)(node + 4);

    if (*(unsigned char *)(*(int *)child + 0xad) == 0) {
        func_0203b9fc(*(int *)child, 0, 2, 0);
        func_0203b9fc(*(int *)child, 2, 2, 0);
        func_0203b9fc(*(int *)child, 4, 2, 0);
        func_0203b9fc(*(int *)child, 1, 2, 0);
        func_0203c7ac(*(int *)child, 0);
        func_0203c634(node, *(signed char *)(node + 0x20), (void *)&func_ov244_020ce7b8);
        return;
    }
}
