# What is this fork?

This fork has an objective to compile this Snake game to [https://github.com/jbruchon/elks](ELKS) Linux by porting Turbo C functions to ELKS Linux.

Tasks:

* change the code to C
  * disable file management code for now
* use conio.h provided by [https://github.com/tkchia/libi86/](libi86 project)
* comment out dos.h for now (port it later)
* create a port for graphics.h on top of Nano-X
  * [https://github.com/jbruchon/elks/tree/master/elkscmd/nano-X/demos](usage of Nano-X)
  * The port should be something like that:
    * [outtextxy ](https://www.geeksforgeeks.org/outtextxy-function-c/) -> [GrText](http://embedded.centurysoftware.com/docs/nx/GrText.html)
    * [rectangle](https://www.geeksforgeeks.org/draw-rectangle-c-graphics/) -> [GrRect](http://embedded.centurysoftware.com/docs/nx/GrRect.html)
    
Alternatively I could use [https://github.com/jbruchon/elks/issues/871#issuecomment-1303608547](this).
