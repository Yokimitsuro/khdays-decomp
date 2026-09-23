/* Replay the ov218 actor's animation: layer 0 of its +0x384 rig restarts on the +0x310 kind with the
 * +0x311 loop bit, layer 2 on the +0x398 pose, and the rig pose resets. */
typedef unsigned char u8;
typedef struct { u8 b0 : 1; } Bit0;

extern void func_0203b9fc(int rig, int channel, int a, int b);
extern void func_0203c7ac(int rig, int a);

void func_ov218_020ce3a8(char *actor)
{
    func_0203b9fc(*(int *)(actor + 0x384), 0, *(signed char *)(actor + 0x310), ((Bit0 *)(actor + 0x311))->b0);
    func_0203b9fc(*(int *)(actor + 0x384), 2, (short)*(int *)(actor + 0x398), 0);
    func_0203c7ac(*(int *)(actor + 0x384), 0);
}
