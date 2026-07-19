extern char *data_ov008_02090fac;

/* True when the cursor is inside the given box (x, y, w, h as unsigned bytes). */
int func_ov008_02082cec(unsigned char *box) {
    int hit = 0;
    char *ui = *(char **)&data_ov008_02090fac;
    if ((unsigned short)(*(unsigned short *)(ui + 0xc120) - box[0]) < (unsigned int)box[2]) {
        if ((unsigned short)(*(unsigned short *)(ui + 0xc122) - box[1]) < (unsigned int)box[3]) {
            hit = 1;
        }
    }
    return hit;
}
