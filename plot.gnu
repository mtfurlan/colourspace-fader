#!/usr/bin/env gnuplot

# mkdir -p plotData; inotifywait -r -e create --exclude "\.git" -m . -q | grep --line-buffered -E "\.c$|\.h$|\.sh$|\.gnu$" | grep --line-buffered -v "tmp_pio_test_transport.c" | while read -r directory events filename; do echo "file changed: $directory/$filename"; make test | grep -P "PLOTTITLE.*|PLOTDATA" > plotData/output && head -n1 plotData/output | sed 's/PLOTTITLE: //' > plotData/title && tail -n+2 plotData/output | sed 's/PLOTDATA: //' | sort -n -s -k 1,1 > plotData/rgb.csv && ./plot.gnu; echo "done"; done

#set term svg
#set output "plot.svg"

set multiplot layout 2, 1 title "`head -1 plotData/title`" font ",14"

set lmargin at screen 0.05

# move the key out of the graph area
set yrange [0:350]
# don't add extra space to end of plot
set autoscale xfix

plot "plotData/rgb.csv" using 1:2 title 'red' with lines linecolor "red", \
     "plotData/rgb.csv" using 1:3 title 'green' with lines linecolor "green", \
     "plotData/rgb.csv" using 1:4 title 'blue' with lines linecolor "blue"

# magic to plot colors
set style function pm3d
set view map scale 1
set format cb "%3.1f"

unset colorbox

set palette file 'plotData/rgb.csv' using (($2/255)):(($3/255)):(($4)/255)
set palette maxcolors system("wc -l plotData/rgb.csv | sed 's/ .*//'")

unset key
unset ytics
unset xtics

g(x)=x
splot g(x)

unset multiplot

pause mouse any "press the any key to exit gnuplot"
