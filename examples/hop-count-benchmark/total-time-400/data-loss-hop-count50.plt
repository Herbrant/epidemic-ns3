set terminal png size 1920,1080
set output "data-loss-hop-count50.png"
set title "Relationship between data loss and buffer size"
set xlabel "HopCount"
set ylabel "Packet Loss %"

set xrange [0:+50]
plot "-"  title "Packet Loss %" with linespoints
0 100
1 79.8822
2 71.229
3 64.3434
4 59.0741
5 52.4916
6 54.7475
7 57.2391
8 61.5488
9 54.6296
10 62.5084
11 51.9192
12 55.4882
13 46.3973
14 63.9394
15 63.6195
16 56.9192
17 48.8721
18 56.3973
19 56.1279
20 54.0572
21 61.6162
22 67.4242
23 49.3771
24 59.0236
25 50.404
26 58.8384
27 51.9529
28 58.5185
29 47.4916
30 56.936
31 57.6599
32 51.9697
33 58.2997
34 59.6296
35 60.9428
36 54.7138
37 50.2357
38 63.6364
39 51.7172
40 53.2155
41 49.9663
42 57.7441
43 50.101
44 52.7946
45 55.8081
46 56.2963
47 60.8754
48 60.2694
49 66.3636
50 51.1785
e