set title 'Feasible Region of Linear Inequalities'
set xlabel 'x1'
set ylabel 'x2'
set grid
set xrange [0:11]
set yrange [0:26]
set key outside
plot (18 - 2*x) title '2x1 + x2 = 18' lc rgb 'red' lw 2, \
     (42 - 2*x)/3 title '2x1 + 3x2 = 42' lc rgb 'blue' lw 2, \
     (24 - 3*x) title '3x1 + x2 = 24' lc rgb 'green' lw 2, \
     'feasible_points.csv' using 1:2 with dots title 'Feasible Region' lc rgb 'dark-grey'
