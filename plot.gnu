#!/usr/bin/env gnuplot

# inotifywait -q -r -e create --exclude "\.git" -m . | grep --line-buffered -E "\.c$|\.h$|\.sh$|\.gnu$" | grep --line-buffered -v "tmp_pio_test_transport.c" | while read -r directory events filename; do echo "file changed: $directory/$filename"; make test | grep -P "\d+\.\d+, *\d+, *\d+, *\d+" > rgb.csv && ./plot.gnu; echo "done"; done

# For some reason if I output to png it will interpolate the colour box.
# So instead of saving to SVG I just exported to png manually
#set term svg
#set output "plot.svg"

set multiplot layout 2, 1 title "Attempt 2 HSL sweep with min .001 ΔE" font ",14"

set lmargin at screen 0.05

plot "rgb.csv" using 2 title 'red' with lines linecolor "red", \
     "rgb.csv" using 3 title 'green' with lines linecolor "green", \
     "rgb.csv" using 4 title 'blue' with lines linecolor "blue"

set style function pm3d
set view map scale 1
set format cb "%3.1f"

unset colorbox

set palette file 'rgb.csv' using (($2/255)):(($3/255)):(($4)/255)
set palette maxcolors system("wc -l rgb.csv")

unset key
unset ytics
unset xtics


g(x)=x
splot g(x)

unset multiplot

pause mouse close
