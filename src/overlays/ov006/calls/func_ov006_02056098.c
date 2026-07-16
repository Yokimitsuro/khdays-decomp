/* func_ov006_02056098 -- hide/flush the two title-screen BG text layers (ctx+0x976c, +0x97b8). */
extern void func_0202f9f8(int layer);
extern int  data_ov006_02056664;   /* -> title-screen context */

void func_ov006_02056098(void) {
    func_0202f9f8(data_ov006_02056664 + 0x976c);
    func_0202f9f8(data_ov006_02056664 + 0x97b8);
}
