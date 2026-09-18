/* func_ov245_020d583c -- pose sync: runs the +0x3a0 item's motion (020c9ec8 with the argument),
 * the base sync (020c6980), then copies the +0x39c source's +4 transform (44 bytes) into the
 * +0x38c item's +0x10 and that one's +0x10 into the +0x388 target's +0x10. Codegen: typed struct
 * member copies (destination address evaluated first, ip before lr). */
typedef struct { int m[11]; } Pose44;
struct Ov245Item { char pad[0x10]; Pose44 pose; };
struct Ov245Src { char pad[4]; Pose44 pose; };

extern void func_ov107_020c9ec8(int item, int a);
extern void func_ov107_020c6980(int self, int a);

void func_ov245_020d583c(int self, int a) {
    func_ov107_020c9ec8(*(int *)(self + 0x3a0), a);
    func_ov107_020c6980(self, a);
    ((struct Ov245Item *)*(int *)(self + 0x38c))->pose = ((struct Ov245Src *)*(int *)(self + 0x39c))->pose;
    ((struct Ov245Item *)**(int **)(self + 0x388))->pose = ((struct Ov245Item *)*(int *)(self + 0x38c))->pose;
}
