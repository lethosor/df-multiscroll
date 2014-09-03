#ifndef _RENDERER_TWBT_H
#define _RENDERER_TWBT_H

// This is from g_src/renderer_opengl.hpp
struct _renderer_opengl : public df::renderer
{
    void *sdlscreen;
    int dispx, dispy;
    float *vertexes, *fg, *bg, *tex;
    int zoom_steps, forced_steps;
    int natural_w, natural_h;
    int off_x, off_y, size_x, size_y;

    virtual void allocate(int tiles) {};
    virtual void init_opengl() {};
    virtual void uninit_opengl() {};
    virtual void draw(int vertex_count) {};
    virtual ~_renderer_opengl() {};
    virtual void reshape_gl() {};
};
typedef _renderer_opengl renderer_opengl; // This is to make Linux happy

struct renderer_cool : renderer_opengl
{
    uint32_t dummy;

    float *gvertexes, *gfg, *gbg, *gtex;
    int gdimx, gdimy, gdimxfull, gdimyfull;
    int gdispx, gdispy;
    float goff_x, goff_y, gsize_x, gsize_y;
	bool needs_reshape;
    int needs_zoom;
    bool needs_full_update;
    unsigned char *gscreen;
    float goff_y_gl;

    renderer_cool();

    void reshape_graphics();
    void display_new(bool update_graphics);
    void gswap_arrays();
    void allocate_buffers(int tiles);
    void update_map_tile(int x, int y);
    void reshape_zoom_swap();

    virtual void update_tile(int x, int y);
    virtual void draw(int vertex_count);
    virtual void reshape_gl();

    virtual bool get_mouse_coords(int32_t *x, int32_t *y);

    virtual void update_tile_old(int x, int y) {}; //17
    virtual void reshape_gl_old() {}; //18

    virtual void _last_vmethod() {};

    bool is_twbt() {
        return (this->dummy == 'TWBT');
    };

    void output_string(int8_t color, int x, int y, std::string str)
    {

    };

    void output_char(int8_t color, int x, int y, unsigned char ch)
    {
        const int tile = (x-1) * gdimy + (y-1);
        unsigned char *s = gscreen + tile*4;
        s[0] = ch;
        s[1] = color % 16;
        s[2] = 0;
        s[3] = (color / 16) | (s[3]&0xf0);
    };    

    DFHack::Gui::DwarfmodeDims map_dims()
    {
        //7              int map_x1, map_x2, menu_x1, menu_x2, area_x1, area_x2;
  //128              int y1, y2;
  
        DFHack::Gui::DwarfmodeDims dims = { .map_x1=1, .map_x2=gdimx, .menu_x1=0, .menu_x2=0, .area_x1=0, .area_x2=0, .y1=1, .y2=gdimy };
        return dims;

        //return return mkrect_xy(1, 1, gdimx, gdimy);
    };
};

#endif