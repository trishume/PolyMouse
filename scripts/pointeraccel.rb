# Calculations for head acceleration curve
# based on the sigmoid curve calculations in the paper referenced below, measurements I took with my TrackIR5 on myself, and my display resolution
# Nancel, M., Pietriga, E., Chapuis, O., & Beaudouin-Lafon, M. (2015). Mid-Air Pointing on Ultra-Walls. ACM Trans. Comput.-Hum. Interact. (), 22(5), 21–62. http://doi.org/10.1145/2766448

maxUpY = -6
maxDownY = 9

maxLeft = -18.3
maxRight = 14.5 # (because of blur)
# maxRight = 20 # (if there was no blur)

# Head xQuantum: 0.1-0.4 (prolly 0.25 or something)
xQuantum = 0.25
yQuantum = 0.4

maxScreenX = 1920
maxScreenY = 1080

minScreenX = 4
minScreenY = minScreenX

cdMaxX = maxScreenX/(maxRight-maxLeft).abs
cdMaxY = maxScreenY/(maxUpY-maxDownY).abs

cdMinX = minScreenX/xQuantum.to_f
cdMinY = minScreenY/yQuantum.to_f

puts "CD_max: [x,y] (based on largest movement)"
p [cdMaxX, cdMaxY]
puts "CD_min: [x,y] (based on smallest movement)"
p [cdMinX, cdMinY]

# maxVX = 0.025
maxVX = 0.0025
maxVY = 0.0025

minVX = 0.0003
minVY = 0.0004

initialLambdaX = ((cdMaxX-cdMinX)/(maxVX-minVX))
initialLambdaY = ((cdMaxY-cdMinY)/(maxVY-minVY))

puts "Initial lambda guess: [x,y]"
p [initialLambdaX, initialLambdaY]
