extern int WM_EndKeySharing_0x02032444();
extern void func_0203281c();
extern void func_02032710();

int func_ov011_0205d664(int this_, int arg1) {
    int obj = WM_EndKeySharing_0x02032444(this_, arg1, 0);
    func_0203281c(this_, obj, 0);
    func_02032710(this_, obj, 0);
    return obj;
}
