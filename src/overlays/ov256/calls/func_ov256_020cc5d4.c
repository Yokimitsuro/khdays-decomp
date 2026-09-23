/* Update of the ov256 model: +0x460 takes the body's (+0x384) current frame on track 0; while the body
 * animates (+0xad) its track-0 frame and the +0x3ac part's are clamped to +0x460 plus the +0x45c
 * offset (x 512). Then the +0x450 part and the base update run. */
typedef unsigned char u8;

extern int func_0203bec0(int model, int track);
extern int func_0203be68(int model, int track, int a);
extern void func_0203be9c(int model, int track, int frame);
extern void func_ov107_020c9ec8(int part, int arg);
extern void func_ov107_020c6980(char *self, int arg);

void func_ov256_020cc5d4(char *self, int arg)
{
    *(int *)(self + 0x460) = func_0203bec0(*(int *)(self + 0x384), 0);
    if (*(u8 *)(*(int *)(self + 0x384) + 0xad) != 0) {
        int frame = func_0203be68(*(int *)(self + 0x384), 0, 0);

        if (frame > *(int *)(self + 0x460) + (*(int *)(self + 0x45c) << 9)) {
            func_0203be9c(*(int *)(self + 0x384), 0, *(int *)(self + 0x460) + (*(int *)(self + 0x45c) << 9));
            func_0203be9c(*(int *)(self + 0x3ac), 0, *(int *)(self + 0x460) + (*(int *)(self + 0x45c) << 9));
        } else {
            func_0203be9c(*(int *)(self + 0x384), 0, frame);
            func_0203be9c(*(int *)(self + 0x3ac), 0, frame);
        }
    }
    func_ov107_020c9ec8(*(int *)(self + 0x450), arg);
    func_ov107_020c6980(self, arg);
}
