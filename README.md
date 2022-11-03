## Limiatations:
- Only support .bmp image
- The .bmp file can't be compressed

For complie create build folder and run: `cmake .. && cmake --build .` In the build directory

What is this? A conversor of any image to charecters.

For a video, create a folder with name `input` and here put the .bmp files, if you have [ffmpeg](https://ffmpeg.org/) installed on your computer can run:
```
ffmpeg -i <video> -pix_fmt bgr24 input/%04d.bmp
```

# Example usage

```bash
# Help:
In work



# One image:
In work

# A folder:
In work

# Realtime playback:
In work
```

## Libraries used
All the program is created from 0, only C Standard Library Functions