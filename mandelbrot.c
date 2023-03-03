#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void mndl(double WIDTH, double HEIGHT, double XCENTER, double YCENTER, double DELTAPIX, double max_loop, char* filename) {
    double x, y, x1, y1, x2, y2;
    double max=log(max_loop);
    double loop;
    FILE *fp;
    fp = fopen(filename, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", (int)WIDTH, (int)HEIGHT);
    for (int yy = 0; yy < HEIGHT; yy++) {
        y = YCENTER + ((yy - HEIGHT / 2) * DELTAPIX); 
	for (int xx = 0; xx < WIDTH; xx++) {
            x = XCENTER + ((xx - WIDTH / 2) * DELTAPIX);
            x1 = 0;
            y1 = 0;
            x2 = 0;
	    y2 = 0;
            loop = 0;
            while (loop < max_loop && x2 + y2 <= 4) {
                y1 = 2 * x1 * y1 + y;
                x1 = x2 - y2 + x;
		x2 = x1 * x1;
		y2 = y1 * y1;
                loop++;
            }
            if (loop == max_loop) {
                fputc(0, fp);
                fputc(0, fp);
                fputc(0, fp);
            } else {
		loop=256*(log(loop)/max);
                fputc((char)loop % 8 * 32, fp);
                fputc((char)loop % 4 * 64, fp);
                fputc((char)loop % 2 * 128, fp);
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
    for (int z = 187; z <= frames; z++) {
        sprintf(filename, "images/%04d.ppm", z);
        printf("%04d\n", z);
	mndl(WIDTH, HEIGHT, XCENTER, YCENTER, pow(10, zoom), max_loop, filename);
	zoom+=DELTAZOOM;
    }
    return 0;
}
