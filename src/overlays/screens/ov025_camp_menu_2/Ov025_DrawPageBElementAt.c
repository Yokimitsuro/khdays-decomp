/* Draws page B element arg2 with the argument. */

extern int Ov025_DrawPageBElement(int param_1, int param_2, ...);

int Ov025_DrawPageBElementAt(int arg0, int arg1, int arg2) {
    return Ov025_DrawPageBElement(arg2, 0, arg1);
}
