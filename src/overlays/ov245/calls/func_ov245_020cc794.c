/* func_ov245_020cc794 -- bind a motion: resets the actor's +0x390 track (0202a440), refreshes the
 * +0x384 item's model (+0x88, 02014b5c on its +0x20 with +0x78), attaches the pool resource
 * `index + 1` to the track (0202a388, slot 0xc), hooks the track onto the item (0203b9ac), starts
 * channel 0 with the given flag (0203b9fc) and halts the item's motion (0203c7ac). */
struct Ov245Model { char pad[0x20]; char anim[0x58]; int pool78; };

extern void func_0202a440(void *track);
extern void func_02014b5c(void *anim, int pool);
extern void *func_ov107_020c9440(int self, int index);
extern void func_0202a388(void *track, struct Ov245Model *model, void *resource, int slot);
extern void func_0203b9ac(int item, void *track);
extern void func_0203b9fc(int item, int channel, int a, int flag);
extern void func_0203c7ac(int item, int a);

void func_ov245_020cc794(int self, int index, int flag) {
    struct Ov245Model *model = *(struct Ov245Model **)(*(int *)(self + 0x384) + 0x88);

    func_0202a440((void *)(self + 0x390));
    func_02014b5c(model->anim, model->pool78);
    func_0202a388((void *)(self + 0x390), model, func_ov107_020c9440(self, index + 1), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), (void *)(self + 0x390));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, flag);
    func_0203c7ac(*(int *)(self + 0x384), 0);
}
