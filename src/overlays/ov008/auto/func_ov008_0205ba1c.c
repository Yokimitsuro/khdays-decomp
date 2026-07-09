struct ov008_halfword_entry {
    unsigned short value;
    unsigned char _pad[6];
};

extern struct ov008_halfword_entry data_ov008_0208ee86[];
unsigned short func_ov008_0205ba1c(int index)
{
    return data_ov008_0208ee86[index].value;
}
