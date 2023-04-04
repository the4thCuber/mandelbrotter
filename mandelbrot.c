#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void mndl(int WIDTH, int HEIGHT, double XCENTER, double YCENTER, double DELTAPIX, double m, char* filename) {
    double cx,cy,x,y,x2,y2,i,q,px,py,pc,l=log(2);
    FILE *fp;
    fp = fopen(filename, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    for (int yy = 0; yy < HEIGHT; yy++) {
        cy = YCENTER + ((yy - HEIGHT / 2) * DELTAPIX); 
	for (int xx = 0; xx < WIDTH; xx++) {
            cx = XCENTER + ((xx - WIDTH / 2) * DELTAPIX);
            x = cx;
            y = cy;
            x2 = x*x;
	    y2 = y*y;
            i = 1;
            q = (x-.25)*(x-.25)+y2;
	    if ((x+1)*(x+1)+y2<=.0625){i=m;}
	    if (q*(q+(x-.25))<=.25*y2){i=m;}
	    px=x;
	    py=y;
	    pc=1;
            while (i < m && x2 + y2 <= 400) {
                y = 2 * x * y + cy;
                x = x2 - y2 + cx;
		x2 = x * x;
		y2 = y * y;
                i++;
		pc++;
		if (pc>=23) {
		    pc=0;
		    if (px==x && py==y) {i=m;}
		    else {px=x;py=y;}
		}
            }
            if (i == m) {
                fputc(0, fp);
                fputc(0, fp);
                fputc(0, fp);
            } else {
		double logz=log(x2+y2)/2;
		double n=log((logz/l))/l;
		i=log(i+log(random())/40-n);
                fputc((char)128*(1+sin(2.4*i)), fp);
                fputc((char)128*(1+sin(2.8*i)), fp);
                fputc((char)128*(1+sin(3.7*i)), fp);
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
    int WIDTH=atoi(argv[1]);
    int HEIGHT=atoi(argv[2]);
    double XCENTER=atof(argv[3]);
    double YCENTER=atof(argv[4]);
    double ZOOM_I=atof(argv[5]);
    double ZOOM_F=atof(argv[6]);
    int frames=atoi(argv[7]);
    double DELTAZOOM=(ZOOM_F-ZOOM_I)/frames;
    double m=atoi(argv[8]);
    double zoom=ZOOM_I;
    char filename[15];
    for (int z = 0; z <= frames; z++) {
        sprintf(filename, "images/%04d.ppm", z);
        printf("%04d\n", z);
	mndl(WIDTH, HEIGHT, XCENTER, YCENTER, pow(10, zoom), m, filename);
	zoom+=DELTAZOOM;
    }
    return 0;
}
