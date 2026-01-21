/*!
    @brief   Convert separate red, green and blue values into a single
             "packed" 32-bit RGB color.
    @param   r  Red brightness, 0 to 255.
    @param   g  Green brightness, 0 to 255.
    @param   b  Blue brightness, 0 to 255.
    @return  32-bit packed RGB value, which can then be assigned to a
             variable for later use or passed to the setPixelColor()
             function. Packed RGB format is predictable, regardless of
             LED strand color order.
  */
static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

//     Color(255, 0, 0)    // Red
//     Color(255, 106, 0)  // Orange
//     Color(255, 216, 0)  // Yellow
//     Color(0, 255, 33)  // Green
//     Color(255, 255, 255) // White

uint32_t frames[2][256] = {
    // Frame 1
    {
       /*0*/  Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0),
       /*1*/  Color(255, 0, 0), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 0, 0),
       /*2*/  Color(255, 0, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 255, 255), Color(255, 0, 0),
       /*3*/  Color(255, 0, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 0, 0),
       /*4*/  Color(255, 0, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 0, 0),
       /*5*/  Color(255, 0, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 216, 0), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 216, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 0, 0),
       /*6*/  Color(255, 0, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 216, 0), Color(255, 255, 255), Color(0, 255, 33), Color(0, 255, 33), Color(0, 255, 33), Color(0, 255, 33), Color(255, 255, 255), Color(255, 216, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 0, 0),
       /*7*/  Color(255, 0, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 216, 0), Color(255, 255, 255), Color(0, 255, 33), Color(255, 255, 255), Color(255, 255, 255), Color(0, 255, 33), Color(255, 255, 255), Color(255, 216, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 0, 0),
       /*8*/  Color(255, 0, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 216, 0), Color(255, 255, 255), Color(0, 255, 33), Color(255, 255, 255), Color(255, 255, 255), Color(0, 255, 33), Color(255, 255, 255), Color(255, 216, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 0, 0),
       /*9*/  Color(255, 0, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 216, 0), Color(255, 255, 255), Color(0, 255, 33), Color(0, 255, 33), Color(0, 255, 33), Color(0, 255, 33), Color(255, 255, 255), Color(255, 216, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 0, 0),
       /*10*/ Color(255, 0, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 216, 0), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 216, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 0, 0),
       /*11*/ Color(255, 0, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 0, 0),
       /*12*/ Color(255, 0, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 106, 0), Color(255, 255, 255), Color(255, 0, 0),
       /*13*/ Color(255, 0, 0), Color(255, 255, 255), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 106, 0), Color(255, 255, 255), Color(255, 0, 0),
       /*14*/ Color(255, 0, 0), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255), Color(255, 0, 0),
       /*15*/ Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0)
    },
    // Frame 2
    {
       /*0*/  Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*1*/  Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*2*/  Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*3*/  Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*4*/  Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*5*/  Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*6*/  Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*7*/  Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*8*/  Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*9*/  Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*10*/ Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*11*/ Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*12*/ Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*13*/ Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*14*/ Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
       /*15*/ Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0), Color(255, 106, 0), Color(255, 216, 0), Color(0, 255, 33), Color(255, 255, 255), Color(255, 0, 0),
    },
};

double frame_time = 0.5; // seconds per frame