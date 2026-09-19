/* Rebind the three collision items (+0x384 / +0x388 / +0x38c) to the resources of pose slot
 * `slot`: the kinds come from the data_ov244_020d3680 / 020d3658 / 020d36a8 tables (10 entries
 * each, copied to the stack), the entries live at +0x390 / +0x394 / +0x398. */
struct Tbl10 { int w[10]; };
extern int func_ov107_020c9440(int obj, int kind);
extern void func_ov244_020cd258(int item, int tag, int flag, int *pEntry);
extern const struct Tbl10 data_ov244_020d3658;
extern const struct Tbl10 data_ov244_020d3680;
extern const struct Tbl10 data_ov244_020d36a8;

void func_ov244_020cc7b0(int obj, int slot, int flag) {
    struct Tbl10 kindsA = data_ov244_020d3680;
    struct Tbl10 kindsB = data_ov244_020d3658;
    struct Tbl10 kindsC = data_ov244_020d36a8;

    func_ov244_020cd258(*(int *)(obj + 0x384), func_ov107_020c9440(obj, kindsA.w[slot]), flag, (int *)(obj + 0x390));
    func_ov244_020cd258(*(int *)(obj + 0x388), func_ov107_020c9440(obj, kindsB.w[slot]), flag, (int *)(obj + 0x394));
    func_ov244_020cd258(*(int *)(obj + 0x38c), func_ov107_020c9440(obj, kindsC.w[slot]), flag, (int *)(obj + 0x398));
}
