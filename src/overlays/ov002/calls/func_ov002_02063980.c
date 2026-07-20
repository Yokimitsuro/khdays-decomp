/* Commit the page and hand its image to the graphics queue. With no context the
 * page is just released. Otherwise the page's block header is fetched, the image
 * is submitted through func_ov002_02053d28, and -- when nothing is pending and
 * the counter is positive -- the pending slots are cleared and any queued sound
 * stopped. The 0x412 tag-tracker refresh runs unless the global at
 * data_0204c240 has a non-zero value with bit 0 clear. */
extern int data_ov002_0207f634;
extern unsigned char data_0204c240;

extern void *func_ov002_020636ac(void);
extern void func_ov002_02052af4(void *page, int a);
extern int func_02011a20(int block, void *out);
extern void func_ov002_02053d28(int a, int b, int c, int d, int e);
extern int *func_ov002_02063698(void);
extern int func_ov002_020575d0(void);
extern void func_02033bb4(int a, int b, int c);
extern void func_ov002_02064328(void);
extern int func_ov002_0206e33c(void);
extern int func_ov002_02053558(int tag);
extern void func_ov002_020535a4(int a);
extern void func_ov002_02064808(void);
extern void GFXi_EnqueueCommand(int cmd, int a, int b, int c);

void func_ov002_02063980(int *page) {
    int *hdr;
    int *ctx = *(int **)&data_ov002_0207f634;
    int *pending = (int *)func_ov002_020636ac();
    int *counter;

    if (ctx == 0) {
        func_ov002_02052af4(page, 1);
        return;
    }

    func_02011a20(page[2], &hdr);
    func_ov002_02053d28(0x1f, 0, hdr[3], hdr[2], page[2]);
    func_ov002_02052af4(page, 0);

    counter = func_ov002_02063698();
    if (func_ov002_020575d0() == 0 && *counter > 0) {
        pending[4] = 0;
        pending[5] = 0;
        if (pending[2] != 0) {
            func_02033bb4(0, 0x32, 0);
            pending[2] = 0;
        }
        func_ov002_02064328();
    }

    if (data_0204c240 == 0 || (data_0204c240 & 1) != 0) {
        if (func_ov002_0206e33c() > 0) {
            func_ov002_020535a4(func_ov002_02053558(0x412));
        }
    }

    func_ov002_02064808();
    GFXi_EnqueueCommand(0x16, 0x1a60, ctx[7], 0x40);
}
