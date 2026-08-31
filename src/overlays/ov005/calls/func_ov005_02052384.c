typedef unsigned short u16;
typedef struct TileSurface TileSurface;
extern void func_020301c8(TileSurface *,int,int,int,unsigned int,const u16 *);
void func_ov005_02052384(TileSurface *surface,const u16 *text,int x,int y,int color,unsigned int flags,int shadow) {
    if(text==0)return;
    if(shadow)func_020301c8(surface,x+1,y+1,color+1,flags,text);
    func_020301c8(surface,x,y,color,flags,text);
}
