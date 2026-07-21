extern unsigned char data_ov107_020cbb20[];
extern void *data_ov107_020cbb08[];
/* Callback registration: look the overlay's slot up in the index table (0cbb20) and store the
 * handler into the 1-based handler table (0cbb08). */
void func_ov107_020c2f7c(int idx, void *handler) {
    data_ov107_020cbb08[data_ov107_020cbb20[idx] - 1] = handler;
}
