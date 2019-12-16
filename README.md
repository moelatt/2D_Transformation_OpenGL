(Grade A+) Project

![alt text](image.png)


Window size: 
	width = 550
	height = 550
			
			
			User-Guide
 
	step(1): enter ==> " make " <== to compile

	step(2): enter ==> " ./a.out " <== to run the program

	step(3): type file name ==> " input.txt " <== to get data from file 
		 (you can use your own data file if you want)

	step(4): Choose Bresenhem or DDA Algorithm: Enter 1 or 2. 

	step(5): Right click anywhere  on the viewport window to see menu 
		 (All the function work on any selected polygon object.)
		 
		 

On Menu: you will see 4 categories such as: Rasterization, 
					    Transformations, 
					    Clipping,
					    Continue, 
					    Exist

Each categories have sub-menu:

For rasterization, there is a (on, off) function you can turn on or turn off whatever you like.
	Rasterization 	==> on
	      		==> off 

For Transformations, there are 3 type of sub menu: Translation, Rotation, Scaling

Each sub menu can manipulate specific object polygon up to 15 polygon object.
	For example: Translation ==> object-1
				 ==> object-2
				 ==> object-3
you can manipulate whichever object you want. (object order is depend on polygon index in data file)

To Translate: enter x value to move left(negative) or right(positive) and 
		    y value to move up(positive) or down(negative)

To Rotate: enter any degree. Positive degree will rotate the selected polygon to counter-		       clockwise. Negative will rotate opposite direction.(eg. 45 degree)

To Scale: enter the magnitude to scale the specific polygon. Scale Greater the 1 will give 	  you large polygon and scale between 0 to 1 will give you small polygon.  

Clipping: It can also manipulate specific object polygon. In order to clip,
	  Enter four window clip area value min and max for width and height.

	  For example: Polygon has four point {(0,0), (0,100), (100,100), (100,0)} than
		       you enter four value 0 50 0 50 ==> {(0,0), (0,50), (50,50), (50, 0)		       clip function will be clipped anyting excess from your enter value.
          warning: selected Polygon area must be in you enter value area.
Continue: restart to the procedure.

Exit: It has exit-program sub menu. When you click, it will exit immediately. Any change will be saved in the original file the data is read in. Thanks


