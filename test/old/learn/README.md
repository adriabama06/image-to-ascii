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

NO, in bmp files to read is like:
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
ok all normal, reverse from (x number > 0) to 0... and why -1 ? -1 is because after will multiply row * width why? <br>
Hmmm.... (· is the position read if the last or readed if is not the last) this happen
```
                ############
Actual row >    #   ·      #
                #          #
                #          #
                #          #
                ############
```
what ? why is not in the end -1? the height is 4, and... if you multiply row * width will happen this:
```
                ############
                #          #
                #          #
                #          #
Actual row >    #·         #
                ############
```
why? OK look:<br>
At the fisrt
```
                ############
Actual row >    #····      #
                #          #
                #          #
                #          #
                ############
```
next in sub loop
```
                ############
Actual row >    #·····     #
                #          #
                #          #
                #          #
                ############
```
then continue to 10
```
                ############
Actual row >    #······    #
                #          #
                #          #
                #          #
                ############
```
```
                ############
Actual row >    #·······   #
                #          #
                #          #
                #          #
                ############
```
```
                ############
Actual row >    #········  #
                #          #
                #          #
                #          #
                ############
```
```
                ############
Actual row >    #········· #
                #          #
                #          #
                #          #
                ############
```
... and 10:
```
                ############
Actual row >    #··········#
                #····      #
                #          #
                #          #
                ############
```
and when do row-- and col go to 0 again:
```
                ############
Actual row >    #···       #
                #          #
                #          #
                #          #
                ############
```
eehh... what, and... if continue?
```
                ############
Actual row >    #····      #
                #          #
                #          #
                #          #
                ############
```
```
                ############
Actual row >    #·····     #
                #          #
                #          #
                #          #
                ############
```
ok this not work, but if i do row * width happen this:
```
                ############
                #··········#
                #··········#
                #··········#
Actual row >    #·         #
                ############
```
```
                ############
                #··········#
                #··········#
                #··········#
Actual row >    #··        #
                ############
```
then wait to 10 in the second loop
```
                ############
                #··········#
                #··········#
                #··········#
Actual row >    #···       #
                ############
```
```
                ############
                #··········#
                #··········#
                #··········#
Actual row >    #··        #
                ############
```
```
                ############
                #··········#
                #··········#
                #··········#
Actual row >    #···       #
                ############
```
```
                ############
                #··········#
                #··········#
                #··········#
Actual row >    #····      #
                ############
```
and the 10
```
                ############
                #··········#
                #··········#
                #··········#
Actual row >    #··········#
                ############
```
and when do row-- and col go to 0 again:
```
                ############
                #··········#
                #··········#
Actual row >    #·         #
                #          #
                ############
```
very good, and if i continue all will go ok
```
                ############
                #··········#
                #··········#
Actual row >    #··        #
                #          #
                ############
```
```
                ############
                #··········#
                #··········#
Actual row >    #···       #
                #          #
                ############
```
```
                ############
                #··········#
                #··········#
Actual row >    #····      #
                #          #
                ############
```
```
                ############
                #··········#
                #··········#
Actual row >    #·····     #
                #          #
                ############
```
and in the 10:
```
                ############
                #··········#
                #··········#
Actual row >    #··········#
                #          #
                ############
```
and... when do row-- and col go to 0 again:
```
                ############
                #··········#
Actual row >    #·         #
                #          #
                #          #
                ############
```
and this will happen to the end and finally will read all the image and in the order to read correctly the image 
## ok and why pos
because has 3 colors the real width and height is the width and height * 3 colors, 3 bytes of color represent 1 pixel