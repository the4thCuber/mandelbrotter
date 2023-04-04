#!/bin/bash

start=$EPOCHREALTIME

# Parameters for the Mandelbrot set image
width=3840
height=2160
maxit=10000

# Parameters for the zoom sequence
xcenter=-0.74757647291674
ycenter=-0.08137850467218
num_frames=7000

#deltapix math stuff
zoom_i=-2.5
zoom_f=-15.58

# Create a directory to store the images
mkdir images

# Generate the images for the zoom sequence
gcc -o mandelbrot mandelbrot.c -lm
./mandelbrot $width $height $xcenter $ycenter $zoom_i $zoom_f $num_frames $maxit

# Use ffmpeg to turn the images into a video
ffmpeg -f image2 -framerate 30 -i images/%04d.ppm -s  odnwepodhr.avi

# Clean up the images
#rm -r images

echo "$EPOCHREALTIME-$start" | "bc -l" >> data.txt
