#!/bin/bash

# Parameters for the Mandelbrot set image
width=720
height=1560
max_loop=150000

# Parameters for the zoom sequence
xcenter=-.442928
ycenter=.567027
num_frames=1500

#deltapix math stuff
zoom_i=-6
zoom_f=1

# Create a directory to store the images
mkdir images

# Generate the images for the zoom sequence
gcc -o mandelbrot mandelbrot.c -lm
./mandelbrot $width $height $xcenter $ycenter $zoom_i $zoom_f $num_frames $max_loop

# Use ffmpeg to turn the images into a video
ffmpeg -f image2 -framerate 30 -i images/%04d.ppm -s $width x$height seoing.avi

# Clean up the images
#rm -r images
