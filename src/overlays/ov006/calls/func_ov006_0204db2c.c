/* func_ov006_0204db2c -- Mission Mode: drive the ov105 sound state from the scene state.
 * State 0 (still booting) arms the "intro jingle started" latch at obj+0x49c once the
 * sound engine reports ready; states 1 and 3 are quiet; 9 and 10 fade out; every other
 * state stops the sound outright. */
extern int  func_02001030(void);
extern void func_ov105_020bf90c(void);
extern int  func_ov105_020bf5a8(void);
extern void func_ov105_020bf928(void);
extern int  data_ov006_020565e4;

#define OBJ (*(int **)&data_ov006_020565e4)

void func_ov006_0204db2c(void) {
    switch (func_02001030()) {
    case 9:
    case 10:
        func_ov105_020bf90c();
        return;
    case 0:
        if (OBJ[0x127] != 0) {
            return;
        }
        if (func_ov105_020bf5a8() == 0) {
            return;
        }
        OBJ[0x127] = 1;
        return;
    case 1:
        break;
    case 3:
        break;
    default:
        func_ov105_020bf928();
        return;
    }
}
