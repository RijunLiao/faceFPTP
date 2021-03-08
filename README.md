# faceFPTP
Code for matching detections and annotations and computing the resulting scores to generate the performance curves for face detection.

## Prerequisites
- C++
- Opencv


## result.txt (The detection result of face detector)
```
filename1.jpg   # image name
6               # numbe of face
1 2 4 2 0.1     # [x y w h, s], x,y: coordinates of the upper left corner of bounding box, w: width, h: height，s: Confidence score
8 1 4 2 0.4 
1 1 4 2 0.9 
1 15  2 1 0.4
8 1 2 2 0.5 
15 15 4 2 0.1
```

## Ground Truth.txt (annotations of imges)
```
filename1.jpg   # image name
6               # numbe of face
1 2 4 2 0.1     # [x y w h, s], x,y: coordinates of the upper left corner of bounding box, w: width, h: height，s: Confidence score
8 1 4 2 0.4 
1 1 4 2 0.9 
1 15  2 1 0.4
8 1 2 2 0.5 
15 15 4 2 0.1
```

## output.txt
```
FP	TP	Confidence 
7	5	0.1
5	5	0.4
4	4	0.5
4	3	0.9
4	2	2.1
2	2	3.1
1	2	4.4
1	1	5.1
0	1	5.4
```
