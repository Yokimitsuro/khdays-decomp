/* func_ov024_02085fec -- virtual call thunk, ov024. Invokes the object's vtable
 * method at +0x14 with the object as `this`. */
typedef void (*Method)(void *);
void func_ov024_02085fec(void *obj) {
    (*(Method *)((char *)*(void **)obj + 0x14))(obj);
}
