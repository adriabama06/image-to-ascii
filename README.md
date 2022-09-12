## Read bmp is easy than .png or other format in C

For complie create build folder and run: `cmake .. && cmake --build .` in the build directory

what is this? aaa... a conversor of any image to charecters

to use, create a folder with name `input` and here put the .bmp files, if you have a `video` and [ffmpeg](https://ffmpeg.org/) installed your computer can run:
```
ffmpeg -i <video> -pix_fmt bgr24 input/%04d.bmp
```