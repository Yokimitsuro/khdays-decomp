typedef struct Ov005MenuQuad {
    unsigned int texture[2];
    short x,y,z,width,height,u,v,texWidth,texHeight,alpha,polygonId;
    short pad1e;int dimmed;
} Ov005MenuQuad;
void func_ov005_02051eb8(Ov005MenuQuad *quad,short x,short y,short z,short alpha) {
    quad->u=quad->v=0;
    quad->width=quad->height=quad->texWidth=quad->texHeight=16;
    quad->x=x;
    quad->y=y;
    quad->z=z;
    quad->alpha=alpha;
    quad->dimmed=0;
    quad->polygonId=0;
}
