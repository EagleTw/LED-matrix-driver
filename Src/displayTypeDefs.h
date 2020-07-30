//------------------------------------------------------------------------------------------
// font structure
//------------------------------------------------------------------------------------------
typedef struct {
  unsigned char width;
  unsigned char height;
  unsigned char first_char;
  unsigned char last_char;
  const unsigned char *chars;
} type_font_t;
#define font_t type_font_t

//------------------------------------------------------------------------------------------
// Color type Define "RGB332"
//------------------------------------------------------------------------------------------
#define DEFAULT_FORMAT      (1) //1 byte per pixel 
#define PPB                 (1) //1 pixel per 1 byte
#define BPC                 (2) //3 bits per channel - R3,G3,B3 (B is extended with lsb 0) 

#define rCh(c)              ((c.color&192)>>6)            // red channel
#define gCh(c)              ((c.color&24)>>3)            // green channel
#define bCh(c)              (c.color&3)            // blue channel

#define chMask              (0x07)                  // channel mask
#define mixCh(r,g,b)        ((b>>1)|(g<<2)|(r<<5))  // mix channels
#define getFRAMEpx(i,j)       (FRAME_BUFF[i][j])
#define setFRAMEpx(i,j,v)     (FRAME_BUFF[i][j]=v)
#define color2px(px)        (color_t){{px&0x03,(px>>2)&0x07,(px>>5)&0x07}}
#define COLOR(c)            (color_t){{((c&0x0000FF)>>6),((c&0x00FF00)>>8)>>5,((c&0xFF0000)>>16)>>5}}

typedef union {
  struct {
    uint8_t b: 2;
    uint8_t g: 3;
    uint8_t r: 3;
  } bits;
  uint8_t color;
} type_color332_t;
#define color_t type_color332_t
//------------------------------------------------------------------------------------------
// image structure
//------------------------------------------------------------------------------------------
    typedef struct{
        unsigned char width;
        unsigned char height;
        unsigned char bytes_per_px;
        unsigned char px_per_bytes;
        const unsigned char *pixels; 
    }type_image_t; 
    #define image_t type_image_t
