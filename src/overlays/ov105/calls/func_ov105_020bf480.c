/* func_ov105_020bf480 -- emit a scene event (id 0x11, prio 3, ttl 0x1e), ov105. */
extern void func_ov105_020be378(int target, int prio, int id, int arg, int ttl);
void func_ov105_020bf480(int target, int arg) {
    func_ov105_020be378(target, 3, 0x11, arg, 0x1e);
}
