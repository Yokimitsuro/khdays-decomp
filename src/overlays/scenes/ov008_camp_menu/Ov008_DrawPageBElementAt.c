/* Draws page B element arg2 with the argument. */

extern int Ov008_DrawPageBElement(int param_1, int param_2, ...);
void Ov008_DrawPageBElementAt(void *arg0, void *arg1, void *arg2)
{
    Ov008_DrawPageBElement((int)arg2, 0, arg1);
}
