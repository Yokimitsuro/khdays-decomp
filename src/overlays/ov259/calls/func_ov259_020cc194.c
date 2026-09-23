/* Bind an animation to one of the ov259 actor's items: the `work` list is reset (0202a440), the
 * item's +0x88 animation set rewinds (02014b5c), the list is refilled with pose `poseIndex` of the
 * actor's pool (0202a388) and attached to the item, which starts on channel 0 (looping per bit 0 of
 * the actor's +0x311) and is re-initialised. */
typedef unsigned char u8;
struct Flag311 { u8 loop : 1; };

extern void func_0202a440(void *list);
extern void func_02014b5c(int a, int b);
extern void *func_ov107_020c9440(char *self, int index);
extern void func_0202a388(void *list, int b, void *c, int d);
extern void func_0203b9ac(int item, void *list);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern void func_0203c7ac(int item, int a);

void func_ov259_020cc194(char *self, int item, void *work, int poseIndex)
{
    int anim = *(int *)(item + 0x88);

    func_0202a440(work);
    func_02014b5c(anim + 0x20, *(int *)(anim + 0x78));
    func_0202a388(work, anim, func_ov107_020c9440(self, poseIndex), 0xc);
    func_0203b9ac(item, work);
    func_0203b9fc(item, 0, 0, ((struct Flag311 *)(self + 0x311))->loop);
    func_0203c7ac(item, 0);
}
