## BIG ERROR:
In the code I call nanoseconds instance of microseconds:
SECOND - MILISECOND - MICROSECOND - NANOSECONDS
I got confused and thought i was using nanoseconds instead of microseconds

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
image-to-ascii --help
image-to-ascii -i <input file/folder> -o <output file/folder>
  (Optional) --help - Show this menu
  -i <file/folder> - Input file or folder, if the input is a folder you can use multithread or play, only supports bitmap (.bmp) format
  -o <file/folder> - Output file or folder, optional if you just want to play it, if you play the input it will not save any file
  -p - Play the input file / folder, optional if you just want to convert it
  -fps <number> - Set framerate in frames per second, example: 30, 24, 60, 23.976023976 (for cinema using float numbers use: "1000 / (1001 / fps)"), optional if you just want to convert it
  (Optional) -pallete <string> - Set custom color pallete for ascii, the default is: " .,-~:=$#@"
  (Optional) -clear-console - Linux only, clear console before new frame draw, good for clean console to make it look better, bad for ssh connections
  (Optional) -t <number> - Threads for paralel frame conversion, sometimes can be slow than single thread, recomended on slow computers or if the folder has plenty of files        
  (Optional) -v - Verbose output



# One image:
image-to-ascii -i image.bmp -o image.txt

# A folder:
image-to-ascii -i frames -o convert_frames

# Realtime playback:
image-to-ascii -i frames -fps 30 -p -clear-console

# Realtime playback, custom pallete:
image-to-ascii -i frames -fps 30 -p -clear-console -pallete " .-#"
```

## Libraries used
All the program is created from 0, only C Standard Library Functions
