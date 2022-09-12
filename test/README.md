any image has this structure:
```c
typedef struct rgb_struct
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
} rgb;


typedef struct image_struct
{
    unsigned int width;
    unsigned int height;
    rgb* pixels;
} image;
```

For read this structure this is an example:
```c
int main()
{
    image* img = (image*) malloc(sizeof(image));

    FILE* input_image = fopen("my_image.bin", "rb");

    fread(&img->width, sizeof(unsigned int), 1, input_image);
    fread(&img->height, sizeof(unsigned int), 1, input_image);

    unsigned int pixels_len;
    fread(&pixels_len, sizeof(unsigned int), 1, input_image);

    img->pixels = (rgb*) malloc(pixels_len);

    fread(img->pixels, pixels_len, 1, input_image);

    /*
    use img as you like
    */

    rgb pixel = img->pixels[0];

    printf("rgb(%d, %d, %d)\n", pixel.r, pixel.g, pixel.b); // read values of pixel 0

    free(img); // bye

    return 0;
}
```
