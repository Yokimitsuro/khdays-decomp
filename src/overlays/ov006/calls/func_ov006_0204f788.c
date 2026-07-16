/* func_ov006_0204f788 -- Mission Mode: menu-open tick, returns the next scene state (0 = stay).
 * While the scene is locked out (obj+0x4e8) it drives the sound and waits for the intro
 * jingle latch at obj+0x49c to clear, then clears the pending transition at obj+0x2c.
 * Otherwise an unselectable entry sends it straight to func_ov006_0204ece4. Once no
 * transition is pending it commits the entry and advances to func_ov006_0204f810. */
extern void func_ov006_0204dbb4(void);
extern int  func_ov006_0204d5f8(void);
extern void func_ov006_0204e114(void);
extern void func_020307b8(int a);
extern void func_ov006_0204ece4(void);
extern void func_ov006_0204f810(void);
extern int  data_ov006_020565e4;

#define OBJ (*(int **)&data_ov006_020565e4)

void *func_ov006_0204f788(void) {
    void *next = 0;
    if (OBJ[0x13a] != 0) {
        int *obj;
        func_ov006_0204dbb4();
        obj = OBJ;
        if (obj[0x127] != 0) {
            return next;
        }
        obj[0xb] = (int)next;
    } else if (func_ov006_0204d5f8() == 0) {
        return (void *)func_ov006_0204ece4;
    }
    if (OBJ[0xb] == 0) {
        func_ov006_0204e114();
        func_020307b8(0);
        next = (void *)func_ov006_0204f810;
    }
    return next;
}
