#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include <stdio.h>
#include <png.h>

typedef struct
{
    png_byte red;
    png_byte green;
    png_byte blue;
    png_byte alpha;
} rgba;

int width, height;
png_byte color_type;
png_structp png_ptr;
png_infop info_ptr;
png_bytep *row_pointers;
png_byte bit_depth;

TEST_CASE("Load Image")
{
    const char *filename = "../image.png";

    //read file
    FILE *fp = fopen(filename, "rb");
    REQUIRE(fp);

    //initialize
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    REQUIRE(png_ptr);

    info_ptr = png_create_info_struct(png_ptr);
    REQUIRE(info_ptr);

    //png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    REQUIRE(!setjmp(png_jmpbuf(png_ptr)));

    png_init_io(png_ptr, fp); //initialize input for the PNG file
    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    CAPTURE(width);
    CAPTURE(height);
    CAPTURE(bit_depth);

    color_type = png_get_color_type(png_ptr, info_ptr);
    CAPTURE(PNG_COLOR_TYPE_RGB_ALPHA);
    REQUIRE(color_type == PNG_COLOR_TYPE_RGB_ALPHA);

    row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    REQUIRE(row_pointers != nullptr);

    for (int i = 0; i < height; i++)
    {
        row_pointers[i] = (png_byte *)malloc(png_get_rowbytes(png_ptr, info_ptr));
    }

    png_read_image(png_ptr, row_pointers);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
}

TEST_CASE("Write Image")
{
    const char *filename = "../copy.png";

    //read file
    FILE *fp = fopen(filename, "wb");
    REQUIRE(fp);

    //initialize
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    REQUIRE(png_ptr);

    info_ptr = png_create_info_struct(png_ptr);
    REQUIRE(info_ptr);
    REQUIRE(!setjmp(png_jmpbuf(png_ptr)));

    png_init_io(png_ptr, fp); //initialize output for the PNG file

    /*set the PNG_IHDR chunk information*/
    png_set_IHDR(png_ptr, info_ptr, width, height,
                 bit_depth, color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);      //write png info to file
    png_write_image(png_ptr, row_pointers); // write the given image data
    png_write_end(png_ptr, NULL);           //finish writing the file

    REQUIRE(png_ptr != nullptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    for (int y = 0; y < height; y++)
    {
        REQUIRE(row_pointers[y] != nullptr);
        free(row_pointers[y]);
    }
    free(row_pointers);
    fclose(fp);
}
