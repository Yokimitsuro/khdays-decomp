/* func_ov000_02053524 -- (re)load the logo confirm-dialog art, ov000. Builds a resource
 * descriptor {char addr, 2, 0, 0, 8, palette addr} from the scene block (*data_ov000_0205ac28,
 * base[0x28]) and hands it to func_ov000_020556c8, then refreshes the list
 * (func_ov000_02055e54) and the caret (func_ov000_02053c3c). */
extern char *data_ov000_0205ac28;
extern void func_ov000_020556c8(void *widget, int *desc);
extern void func_ov000_02055e54(void *widget, int arg);
extern void func_ov000_02053c3c(int);
void func_ov000_02053524(void) {
    int *base = (int *)data_ov000_0205ac28;
    int desc[6];
    desc[0] = ((base[0xa] + 0x8000 & 0xfffffc) << 7) | 0x80000001;
    desc[1] = 2;
    desc[2] = 0;
    desc[3] = 0;
    desc[4] = 8;
    desc[5] = ((base[0xa] + 0x8000 & 0xfffffc) << 7) | 0x80000003;
    func_ov000_020556c8((char *)base + 0x78, desc);
    func_ov000_02055e54((char *)base + 0x78, 2);
    func_ov000_02053c3c(2);
}
