/* func_ov006_02056030 -- reset the two title-screen BG text layers (ctx+0x976c, +0x97b8, mode 0). */
extern void func_0202fa20(int layer, int mode);
extern int  data_ov006_02056664;   /* -> title-screen context */

void func_ov006_02056030(void) {
    func_0202fa20(data_ov006_02056664 + 0x976c, 0);
    func_0202fa20(data_ov006_02056664 + 0x97b8, 0);
}
