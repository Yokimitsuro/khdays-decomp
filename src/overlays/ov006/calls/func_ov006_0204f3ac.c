/* func_ov006_0204f3ac -- Mission Mode: which menu entry is the cursor on?
 * Returns 0 while the scene is locked out (obj+0x4e8 set), the live cursor index
 * (func_02030788) once the entry is selectable, and 0xff otherwise. */
extern int func_ov006_0204d5f8(void);
extern int func_02030788(void);
extern int data_ov006_020565e4;

#define OBJ (*(int **)&data_ov006_020565e4)

int func_ov006_0204f3ac(void) {
    unsigned short entry = 0xff;
    if (OBJ[0x13a] != 0) {
        entry = 0;
    } else if (func_ov006_0204d5f8() != 0) {
        entry = (unsigned short)func_02030788();
    }
    return entry;
}
