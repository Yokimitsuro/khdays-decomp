/* func_ov006_02055e04 -- Mission Mode: show or hide the currently selected 3D draw slot.
 * The slot index lives at OBJ+0x96dc (negative = none) and the 0x8c-byte slot array starts
 * at OBJ+0x4b08; bit 2 of a slot's first word is its visible flag. The slot is registered
 * with or removed from the renderer list at OBJ+0x4a8c either way. */
extern void func_020326a8(int list, int idx);
extern void func_020326cc(int list, int idx);
extern int *data_ov006_02056664;

struct Ov006DrawSlot {
    unsigned pad0 : 2;
    unsigned visible : 1;
    unsigned pad1 : 29;
    char rest[0x88];
};

void func_ov006_02055e04(int on) {
    int idx = *(int *)((char *)data_ov006_02056664 + 0x96dc);
    if (idx >= 0) {
        struct Ov006DrawSlot *slots =
            (struct Ov006DrawSlot *)((char *)data_ov006_02056664 + 0x4b08);
        slots[idx].visible = on != 0;
    }
    if (on != 0) {
        func_020326a8((int)((char *)data_ov006_02056664 + 0x4a8c),
                      *(int *)((char *)data_ov006_02056664 + 0x96dc));
        return;
    }
    func_020326cc((int)((char *)data_ov006_02056664 + 0x4a8c),
                  *(int *)((char *)data_ov006_02056664 + 0x96dc));
}
