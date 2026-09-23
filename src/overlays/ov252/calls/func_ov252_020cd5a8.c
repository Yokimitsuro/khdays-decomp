/* Rebind a rig to its work list for a new pose: reset the list (param_2) and its +0xc cursor, bind
 * the rig's *(+0x88) owner list, append the pose with tag 0xc, attach the list to the rig, set
 * channel 0 = (0, flag) and re-init the rig. */
extern void func_0202a440(int list);
extern void func_02014b5c(int a, int b);
extern void func_0202a388(int list, int owner, int pose, int tag);
extern void func_0203b9ac(int rig, int list);
extern void func_0203b9fc(int rig, int channel, int a, int b);
extern void func_0203c7ac(int rig, int a);

void func_ov252_020cd5a8(int rig, int list, int pose, int flag)
{
    int owner = *(int *)(rig + 0x88);

    func_0202a440(list);
    *(int *)(list + 0xc) = 0;
    func_02014b5c(owner + 0x20, *(int *)(owner + 0x78));
    func_0202a388(list, owner, pose, 0xc);
    func_0203b9ac(rig, list);
    func_0203b9fc(rig, 0, 0, flag);
    func_0203c7ac(rig, 0);
}
