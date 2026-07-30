/* func_ov008_0206e410 -- Ov008_AddListEntry (188 B, 4 relocs).
 * Adds or merges one entry into the menu list. Looks up the node with matching (kind=param_3,
 * id=param_2) via func_ov008_0206e05c; if none exists it draws a fresh entry through
 * func_ov008_0206e0e4 (forwarding params 2..9). If the node already exists it merges extents into
 * it: field 0xc is raised to at least param_4 (signed max) and field 0x10 accumulates param_5.
 * When param_10 is set it then refreshes the layout: func_ov008_0206c29c(self) followed by
 * func_ov008_0206cdb4(self, self->field_0x48). */
extern int *func_ov008_0206e05c(int a, int b, int c, int *d);
extern void func_ov008_0206e0e4(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, short *p9);
extern void func_ov008_0206c29c(int p);
extern void func_ov008_0206cdb4(int p, int a);

void func_ov008_0206e410(int param_1, int param_2, int param_3, int param_4, int param_5,
                         int param_6, int param_7, int param_8, short *param_9, int param_10)
{
    int *node = func_ov008_0206e05c(param_1, param_3, param_2, 0);
    if (node == 0) {
        func_ov008_0206e0e4(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8, param_9);
    } else {
        if (param_4 < node[3])
            param_4 = node[3];
        node[3] = param_4;
        node[4] += param_5;
    }
    if (param_10 != 0) {
        func_ov008_0206c29c(param_1);
        func_ov008_0206cdb4(param_1, *(int *)(param_1 + 0x48));
    }
}
