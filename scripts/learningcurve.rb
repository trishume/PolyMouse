# Predictions for head learning curve and see if they line up with my results
# Based on the data in the paper:
# Radwin, R., & Vanderheiden, G. (n.d.). A method for evaluating head-controlled computer input devices using fitts' law. Retrieved March 6, 2016, from http://eadc.engr.wisc.edu/Web_Documents/method%20for%20evaluating%20head%20cont.pdf
require "pp"

# IDs given in the paper, calculated using outdated Fitts' law formula
given_ids = [1.0, 2.6, 3.2, 4.2, 4.8, 6.4]

good_points = [1,2,3,4,5, 10, 15, 20, 30]

puts "Learning curve for head tracking given in paper:"
learn = ->(n) { 1132.0 * (n.to_f**(-0.11))}
pp good_points.map {|x| [x, learn[x]] }

puts

puts "Combinations of [size, distance] in mm used in paper:"
combos = [2.7, 8.1, 24.2].product([24.4, 110.9])
p combos
puts "Corresponding IDs using modern formula:"
ids2 = combos.map {|w,d| Math.log2((d/w)+1)}.sort
p ids2
puts "Average ID:"
average_id = ids2.inject(:+)/6.0
p average_id

# These match up with my observations of pilot participants vs me
puts "Predicted TP on first block:"
p average_id / (learn[1]/1000.0)
puts "Predicted TP on 20th block"
p average_id / (learn[20]/1000.0)
puts "[block number, predicted TP]:"
pp good_points.map {|n| [n,average_id / (learn[n]/1000.0)]}

puts

# Now I'm going to try in the reverse direction
puts "Reverse direction, find predicted MT on this study given my pilot participants TP"
av_mt = ->(tp, ids) { ids.map { |id| id/tp.to_f * 1000.0 }.inject(:+) / ids.length }
puts "Predicted MT for pilot participants:"
p av_mt[2.6, ids2]
puts "Predicted MT for me:"
p av_mt[3.6, ids2]
