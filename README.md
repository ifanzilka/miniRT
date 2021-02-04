# MiniRT (*Mini*mal *R*ay *T*racer)

This 42 school project is a preview of the graphic programming world.  
Here, we learned to compute visibility and color of 3D objects, casting rays
on a 3D scene.



## Installation

We need :
* On Linux : clang/gcc, Xlib (v11) and his extension (already installed on Ubuntu distros)
* On Mac OS : clang/gcc  
(you can change CC value in Makefile to set clang)  

Clone this repo :  
```bash
git clone https://github.com/ifanzilka/miniRT
```

Compile :
```bash
cd miniRT
make
```

## Usage

### GUI mode

The program takes a .rt file. More information about this format below...  
```bash
./miniRT [a format .rt scene file]
```

Keybinds :  
- In qwerty layout, **L** enable low-resolution mode to load the scene quickly.  
Hit this an other time to deactivate.  
- **AWSD** for horizontal moving, and **Q/E** for Down/Up move
- **Arrows** to turn camera up/down and left/right, **N/M** for rolling camera ccw/cw.  
- **Tab** switch camera if you define more than one.  
- Finally, **Esc** to quit.  

### BMP mode

You can just save the generated image of scene (RT.bmp) with :  
```bash
./miniRT yourfavoritescene.rt -save
```
**Caution** : this erases precedent RT.bmp  
The output image resolution is no longer limited by your display size in this mode !

### About .rt format

We have to run miniRT with a valid .rt file. Here is an example of valid *(and ugly)* .rt file.  
![This is a alt text.](https://github.com/ifanzilka/miniRT/blob/main/miniRT/screen/1.png)
The school project subject defines how the input file must be formatted.

Each line defines one property or scene object, lines begin with uppercase letter  
mean a unique property and lowercase lines define a scene object:  
- **R** stands for image resolution. Here we have a resolution of 1920x1080
- **A** defines ambient light. It has a light ratio and a rgb code
- **c** places a camera, it is defined by :
	- his position vector
	- his orientation vector (sight-direction)
	- his field of view (FOV) in degrees
- **l** is an omnilight, its properties comprise :
	- a position vector
	- a light-ratio
	- a rgb code
- **pl** is a plane defined by :
	- his position vector
	- his orientation (one of their normals orientation)
	- his rgb color
- **sp** is a sphere, it is defined by :
	- a position vector
	- a diameter
	- an rgb color
- **sq** is a square with :
	- a position vector (one of his vertices)
	- an orientation vector
	- his side size
	- an rgb color
Actually, the subject underdefines the square, so i choose an arbitrary 2nd orientation vector,
and i planned to modify the file format to fix this flaw.
- **cy** places a cylinder with :
	- his position vector (i.e. his base center)
	- his axis orientation vector
	- his diameter
	- his height
- **tr** defines a triangle with his three vertices and his color.

If you want to create a scene, you have to pay attention at :
- vector format : f,f,f ; with f, an arbitrary float 
- rgb format : n,n,n ; with n in range [0,255]
- ratio : f, a float between [-1.0,1.0]
- fov is comprise between [0,180]
- each property must be separated by spaces/tabs

You can write empty lines and object order is meaningless, just don't forget
ambient and resolution. (If you dont like ambient light effect you can deactivate putting a 0 in ratio).

Enjoy !  








# miniRT

https://elearning.intra.42.fr/notions/minilibx/subnotions

https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html

https://habr.com/ru/post/342510/

http://www.graph.unn.ru/rus/materials/CG/CG15_RayTracing.pdf

https://ru.qaz.wiki/wiki/Ray_tracing_(graphics)

https://elar.urfu.ru/bitstream/10995/21457/1/koptelov_1.2.2.3.pdf

https://github.com/42Paris/minilibx-linux
