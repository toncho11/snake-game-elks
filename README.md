# What is this fork?

This fork has an objective to compile this Snake game to [ELKS](https://github.com/jbruchon/elks) Linux by porting Turbo C functions to ELKS Linux. This way we can enojoy the Snake game in ELKS and also create a mechanism to port Turbo C code to ELKS.

Tasks:

* change the code to C
  * disable file management code for now
* use conio.h provided by [libi86 project](https://github.com/tkchia/libi86/)
* comment sound functions from out dos.h, port only delay() for now, a port from [libi86 project](https://github.com/tkchia/libi86/) could be useful
* create a port for graphics.h on top of Nano-X
  * [usage of Nano-X](https://github.com/jbruchon/elks/tree/master/elkscmd/nano-X/demos)
  * Functions needed for this game are: `fillpoly`, `drawpoly`, `settextstyle`, `outtextstyle`, `outtextxy`, `setfillstyle`, `floodfill`, `setcolor`, `rectangle`
  * The port should be something like that:
    * [outtextxy ](https://www.geeksforgeeks.org/outtextxy-function-c/) -> [GrText](http://embedded.centurysoftware.com/docs/nx/GrText.html)
    * [rectangle](https://www.geeksforgeeks.org/draw-rectangle-c-graphics/) -> [GrRect](http://embedded.centurysoftware.com/docs/nx/GrRect.html)
  * Running over Nano-X port will be slow and it will probably require at least 286 to be playable
    
Alternatively I could use [this](https://github.com/jbruchon/elks/issues/871#issuecomment-1303608547).
