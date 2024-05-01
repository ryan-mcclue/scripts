export_set(file, terminal) = sprintf("set t push; set t %s; set o '%s'", terminal, file)
export_reset = "set t pop; set o"
normalise(val, min, max) = (val - min) / (max - min)

eval export_set("graph.png", "pngcairo")

set title "Creation Time pthread() vs fork()"
set xtics out
set xlabel "mb"
set ylabel "launch time (usec)"
set yrange [0:]
set grid x,y

# NOTE(Ryan): Look at https://i.stack.imgur.com/x6yLm.png to see possible palette gradient endpoints
set palette defined (0 "web-blue", 1 "navy")
unset colorbox

set style histogram clustered gap 1
set style data histogram
set boxwidth 0.8 relative
set style fill solid 0.3

# Play with these values
set key top left
set offset 0,0.5,0.5,0

col_start=2
col_end=5

plot for [c=col_start:col_end] "threads" u c:xtic(1) ti col lc palette frac (normalise(c, col_start, col_end))

eval export_reset
