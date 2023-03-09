#!/usr/bin/python
import os

f = open('mbrotter.c','w')
#standard headers
f.write('#include <stdio.h>\n#include <stdlib.h>\n#include <math.h>')
#main loop
f.write('void mndl(double WIDTH, double HEIGHT, double XCENTER, double YCENTER, double DELTAPIX, double maxit, char* filename) {')
#var declarations
f.write('\ndouble x, y, x1, y1, x2, y2, max=log(maxit), i;')
f.write('\nFILE *fp;')
#file stuff
f.write('fp = fopen(filename, "wb");\nfprintf(fp, "P6\n%d %d\n255\n", (int)WIDTH, (int)HEIGHT);')
    for (int yloc = 0; yloc < HEIGHT; yloc++) {
        cy = YCENTER + ((yloc - HEIGHT / 2) * DELTAPIX); 
	for (int xloc = 0; xloc < WIDTH; xloc++) {
            cx = XCENTER + ((xloc - WIDTH / 2) * DELTAPIX);
	    i = 0;
	    if ((cx + 1)*(cx + 1) + cy*cy <= .0625) {
		    i = maxit;
	    }
	    double q = (cx-.25) * (cx-.25) + cy*cy;
		if (q*(q+(cx-.25)) <= .25*cy*cy) {
			i = maxit;
		}
            x = 0;
            y = 0;
            x2 = 0;
	    y2 = 0;
            while (i < maxit && x2 + y2 <= 40) {
                y = 2 * x * y + cy;
                x = x2 - y2 + cx;
		x2 = x * x;
		y2 = y * y;
                i++;
            }
            if (i == maxit) {
                fputc(0, fp);
                fputc(0, fp);
                fputc(0, fp);
            } else {
		i=256*(log(i)/max);
                fputc((char)sin(1.25*loop), fp);
                fputc((char)sin(3.78*loop), fp);
                fputc((char)sin(7.62*loop), fp);
            }
        }
    }
    fclose(fp);
}

int main(int argc, char* argv[]) {
    if (argc!=9) {
	printf("argc is not 9\n");
        printf("use ./mandelbrot width height xcenter ycenter zoom_i zoom_f frames max_loop");
	exit(EXIT_FAILURE);
   }
    double WIDTH=atof(argv[1]);
    double HEIGHT=atof(argv[2]);
    double XCENTER=atof(argv[3]);
    double YCENTER=atof(argv[4]);
    double ZOOM_I=atof(argv[5]);
    double ZOOM_F=atof(argv[6]);
    int frames=atoi(argv[7]);
    double DELTAZOOM=(ZOOM_F-ZOOM_I)/frames;
    double max_loop=atoi(argv[8]);
    double zoom=ZOOM_I;
    char filename[15];
    for (int z = 0; z <= frames; z++) {
        sprintf(filename, "images/%04d.ppm", z);
        printf("%04d\n", z);
	mndl(WIDTH, HEIGHT, XCENTER, YCENTER, pow(10, zoom), max_loop, filename);
	zoom+=DELTAZOOM;
    }
    return 0;
}

f.close()
