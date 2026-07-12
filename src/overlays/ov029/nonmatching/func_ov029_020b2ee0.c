extern void func_0201e470();
extern char data_ov029_020b30b0[];
extern int data_ov029_020b320c[];
extern int data_ov029_020b3200[];
extern char data_ov029_020b2f70[];
int func_ov029_020b2ee0(int arg0, int idx)
{
    int r = -1;
    int off = idx << 4;
    int *entry = (int *)(data_ov029_020b30b0 + off);
    int *t = data_ov029_020b320c;
    int *e = entry + 3;
    int k = 3;
    do {
        if (*t == -1 && *e != -1) {
            r = entry[k];
            data_ov029_020b3200[k] = r;
            break;
        }
        t--; e--; k--;
    } while (k >= 0);
    func_0201e470(0, r);
    (*(void (**)())(data_ov029_020b2f70 + off + k * 4))();
    return r;
}
