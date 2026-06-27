extern int data_02047364;

void GFXi_SaveStateTo(int *dst)
{
    int *src = &data_02047364;
    dst[0] = src[0];
    dst[1] = src[1];
}
