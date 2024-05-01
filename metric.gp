export_set(file, terminal) = sprintf("set t push; set t %s; set o '%s'", terminal, file)
export_reset = "set t pop; set o"
normalise(val, min, max) = (val - min) / (max - min)

eval export_set("metrics.png", "pngcairo")

# NOTE(Ryan): Look at https://i.stack.imgur.com/x6yLm.png to see possible palette gradient endpoints
set palette defined (0 "dark-orange", 1 "sienna1")
unset colorbox

set multiplot layout 2,2 

set yrange [0:]
set grid x,y
unset xtics

set ylabel "sec"
set xlabel "Build Time"
plot "build-time.info" u 0:1 notitle w lp lc palette frac (1./4)

set xlabel "Run Time"
plot "run-time.info" u 0:1 notitle w lp lc palette frac (2./4)

set ylabel "MB"
set xlabel "Heap Usage"
plot "heap-usage.info" u 0:1 notitle w lp lc palette frac (3./4)

set yrange [0:100]
set ylabel "%"
set xlabel "Test Coverage"
plot "test-coverage.info" u 0:1 notitle w lp lc palette frac (4./4)

unset multi

eval export_reset
