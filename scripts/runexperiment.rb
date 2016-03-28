# Script to run a PARTICIPANT through a latin square with the FittsTaskTwo applet

CONDITIONS = [
  "Trackpad",
  "Pure head tracking",
  "Liberal MAGIC",
  "Animated MAGIC",
  "PolyMouse including tss click"
]

BLOCKS_PER_CONDITION = 3
LATIN_SQUARE = [
  [1, 2, 3, 4],
  [2, 3, 4, 1],
  [3, 4, 1, 2],
  [4, 1, 2, 3],
]

TEMPLATE_CONFIG = IO.read("FittsTaskTwo-template.cfg")
raise "Need PARTICIPANT number" unless ARGV[0]
PARTICIPANT = ARGV[0].to_i

def log(msg)
  logline = "#{Time.now.to_s} / #{PARTICIPANT}: #{msg}"
  puts logline
  File.open("experiment.log",'a') do |f|
    f.puts logline
  end
end

def setup_config(condition, block)
  ps = "P#{PARTICIPANT.to_s.rjust(2,'0')}"
  cs = "C#{condition.to_s.rjust(2,'0')}"
  bs = "B#{block.to_s.rjust(2,'0')}"
  log "Setting up #{ps}-#{cs}-#{bs}"
  File.open("FittsStudy/FittsTaskTwo.cfg","w") do |f|
    f.puts ps
    f.puts cs
    f.puts bs
    f.puts TEMPLATE_CONFIG
  end
end

def run_applet
  Dir.chdir('FittsStudy') do
    log "Running block"
    system "java -jar FittsTaskTwo.jar"
    log "Finished block"
  end
end

def run_condition(condition, num_blocks)
  log "Please set up condition: #{CONDITIONS[condition-1]}"
  print "Press enter to continue:"
  STDIN.gets
  num_blocks.times do |i|
    setup_config(condition, i+1)
    run_applet
  end
end

def run_experiment()
  square_row = PARTICIPANT % LATIN_SQUARE.size
  conditions = LATIN_SQUARE[square_row]
  log "Latin square row: #{square_row} - #{conditions.inspect}"
  conditions.each do |condition|
    run_condition(condition, BLOCKS_PER_CONDITION)
  end
end

log `sha1sum #{$0}`
run_experiment()
