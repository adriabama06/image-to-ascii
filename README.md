# Download:
[Here](https://github.com/adriabama06/image-to-image-of-characters/releases/tag/v0.0.1)

For complie create build folder and run: `cmake .. && cmake --build .` In the build directory

What is this? A conversor of any image to charecters.

For a video, create a folder with name `input` and here put the .bmp files, if you have [ffmpeg](https://ffmpeg.org/) installed on your computer can run:
```
ffmpeg -i <video> -pix_fmt bgr24 input/%04d.bmp
```

## Warning for Windows !!!
Only on Windows using **folders** only work if you have installed https://sourceforge.net/projects/mingw/ and add gcc and gdb, or for me in my case. If is direcly a .bmp file no problem

```
Try:
gdb -ex r --batch --args image-to-image-of-characters.exe -i multiple_input\input -o multiple_input\output

If the command not run, try:
gdb -ex r --batch --args "image-to-image-of-characters.exe" "-i" ".\\multiple_input\\input\\" "-o" ".\\multiple_input\\output\\"
```

# Example usage

```bash
# Help:
image-to-image-of-characters --help
image-to-image-of-characters -i <input file/folder> -o <output file/folder>
  (Optional) --help - Show this help menu
  -i - Input file or folder, ONLY .bmp FILE SUPPORT
  -o - Output file or folder if the input is a folder
  (Optional) -t - Define number of threads for multithread, only work if the input is a folder



# One image:
image-to-image-of-characters -i my_image.bmp -o my_image_as_chars.txt

# A folder:
image-to-image-of-characters -i my_folder -o my_output_folder
```
