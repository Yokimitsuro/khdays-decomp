/* GFXi_SaveStateTo: copies the two-word graphics state from data_02047364 into dst. */

extern int data_02047364;

void GFXi_SaveStateTo(int *dst) {
    dst[0] = *(int *)&data_02047364;
    dst[1] = *(int *)((int)&data_02047364 + 4);
}
