## Ok what is the stuff happen in double for loop?
Ok my first time to know was hard and wtf, the images not go like:
```
############
#From here #
#          #
#          #
#   to here#
############
```
(top left to bottom right) like:
```
############
#>         #
#          #
#          #
#          #
############
```
```
############
#>>        #
#          #
#          #
#          #
############
```
```
############
#>>>       #
#          #
#          #
#          #
############
```
## ...
```
############
#>>>>>>>>>>#
#>>>>>     #
#          #
#          #
############
```

NO in bmp files to read is like:
```
############
#          #
#          #
#          #
#>         #
############
```
```
############
#          #
#          #
#          #
#>>        #
############
```
```
############
#          #
#          #
#          #
#>>>       #
############
```
```
############
#          #
#          #
#          #
#>>>>      #
############
```
## ... look at this:
```
############
#          #
#          #
#>>>       #
#>>>>>>>>>>#
############
```
```
############
#          #
#          #
#>>>>      #
#>>>>>>>>>>#
############
```
```
############
#          #
#          #
#>>>>>     #
#>>>>>>>>>>#
############
```
## .. yes! the image is horizontally fliped
like:
```
Original:
############
#Hello Wo  #
#rld       #
#          #
#          #
############

in bmp:
############
#          #
#          #
#rld       #
#Hello Wo  #
############
```
## ok will now explain the double for loop:
```c
// this is the for loop
for(int row = height - 1; row >= 0; row--)
{
    for(int col = 0; col < width; col++)
    {
        int pos = ((row * width) + col) * 3;
        
        printf("bgr(%d, %d, %d)", data[pos], data[pos + 1], data[pos + 2]);
    }
}
```
First:
```c
for(int row = height - 1; row >= 0; row--)
```