#!/usr/bin/env gnuplot

# mkdir -p plotData; inotifywait -r -e create --exclude "\.git" -m . -q | grep --line-buffered -E "\.c$|\.h$|\.sh$|\.gnu$" | grep --line-buffered -v "tmp_pio_test_transport.c" | while read -r directory events filename; do echo "file changed: $directory/$filename"; make test | grep -P "PLOTTITLE.*|PLOTDATA" > plotData/output && head -n1 plotData/output | sed 's/PLOTTITLE: //' > plotData/title && tail -n+2 plotData/output | sed 's/PLOTDATA: //' | sort -n -s -k 1,1 > plotData/rgb.csv && ./plot.gnu; echo "done"; done

#set term svg
#set output "plot.svg"

inputFile = "plotData/rgb.csv"
titleFile = "plotData/title"
set multiplot layout 2, 1 title system("cat ".titleFile) font ",14"

set lmargin at screen 0.05

# move the key out of the graph area
set yrange [0:350]
# don't add extra space to end of plot
set autoscale xfix

plot inputFile using 1:2 title 'red' with lines linecolor "red", \
     inputFile using 1:3 title 'green' with lines linecolor "green", \
     inputFile using 1:4 title 'blue' with lines linecolor "blue"

# https://stackoverflow.com/a/69563403/2423187
# convert file of numerical RGB components (0-255) to 24-bit hex representation
# $RGBtable will be a datablock containing Ncol string values
set table $RGBtable
plot inputFile using (sprintf("0x%02x%02x%02x", $2, $3, $4)) with table
unset table
Ncol = |$RGBtable|

unset colorbox
unset key
#unset ytics
#unset xtics

round(x) = x > 0 ? 1 * floor(real(x)/1+0.5) : 1 * ceil(real(x)/1-0.5)
bigger(a, b) = a > b ? a : b
set view map
set yrange [0:1]
# If samples is Ncol, it looks wierd/misses stuff at Ncol=4ish
# Dunno why, this works, whatever.
set samples bigger(1000,Ncol*10)
# we sample between .5 and Ncol + .4999, and round the values
# so from .5 to 1.5 is color 1, from 1.5 to 2.5 is color 2, etc
set urange [.5:Ncol+.4999]
splot '++' using 1:2:(0):(int($RGBtable[round($1)])) with pm3d lc rgb variable

unset multiplot

pause mouse any "press the any key to exit gnuplot"
