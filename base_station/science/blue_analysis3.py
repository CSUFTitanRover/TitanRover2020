import numpy as np
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.pyplot as plt
import colorsys
import cv2

from PIL import Image

# (1) Import the file to be analyzed!

img_file = Image.open("D3.jpg")

spec_sample = img_file.crop((1350, 300, 550+1200, 400+300))
spec_sample.save("spec_sample_3.png")
image = cv2.imread("spec_sample_3.png")
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
thresh = cv2.threshold(gray, 0, 255, cv2.THRESH_OTSU + cv2.THRESH_BINARY)[1]

# Find contour and sort by contour area
cnts = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
cnts = cnts[0] if len(cnts) == 2 else cnts[1]
cnts = sorted(cnts, key=cv2.contourArea, reverse=True)

# Find bounding box and extract region of interest (ROI)
for c in cnts:
    x,y,w,h = cv2.boundingRect(c)
    ROI = image[y:y+h, x:x+w]
    break

cv2.imshow('Cropped #3',ROI)
cv2.imwrite('crop_spec_sample_3.jpg',ROI)
cv2.waitKey()
crop_spec_sample = Image.open("crop_spec_sample_3.png")
img = crop_spec_sample.load()

[xs, ys] = crop_spec_sample.size
max_intensity = 100
hues = {}

# (3) Examine each pixel in the image file
for x in range(0, xs):
  for y in range(0, ys):
    # (4)  Get the RGB color of the pixel
    [r, g, b] = img[x, y]

    # (5)  Normalize pixel color value
    r /= 255.0
    g /= 255.0
    b /= 255.0
    # (6)  Convert RGB color to HSV
    [h, s, v] = colorsys.rgb_to_hsv(r, g, b)

    # (7)  Marginalize s; count how many pixels have matching (h, v)
    if h not in hues:
      hues[h] = {}
    if v not in hues[h]:
      hues[h][v] = 1
    else:
      if hues[h][v] < max_intensity:
        hues[h][v] += 1


# (8)   Decompose the hues object into a set of one dimensional arrays we can use with matplotlib
h_ = []
v_ = []
i = []
colours = []

for h in hues:
  for v in hues[h]:
    h_.append(h)
    v_.append(v)
    i.append(hues[h][v])
    [r, g, b] = colorsys.hsv_to_rgb(h, 1, v)
    colours.append([r, g, b])

# (9)   Plot the graph!
fig = plt.figure()
ax = p3.Axes3D(fig)
ax.scatter(h_, v_, i, s=5, c=colours, lw=0)

ax.set_xlabel('Hue')
ax.set_ylabel('Value')
ax.set_zlabel('Intensity')
fig.add_axes(ax)
plt.show()
