# Script to run a PARTICIPANT through a latin square with the FittsTaskTwo applet
require "pp"
require "json"
require "tk"

CONDITIONS = [
  "Pure head tracking",
  "Trackpad",
  "Liberal MAGIC",
  "Animated MAGIC",
  "PolyMouse including tss click",
  "Head practice 1",
  "Head practice 2"
]

BLOCKS_PER_CONDITION = 3
LATIN_SQUARE = [
  [1, 2, 3, 4],
  [2, 3, 4, 1],
  [3, 4, 1, 2],
  [4, 1, 2, 3],
]

TEMPLATE_CONFIG = IO.read("FittsTaskTwo-template.cfg")

unless ARGV.empty?
  raise "Need PARTICIPANT number" unless ARGV[0]
  PARTICIPANT = ARGV[0].to_i
  raise "Need SESSION number" unless ARGV[1]
  SESSION = ARGV[1].to_i
else
  print "Participant number (e.g 31): "
  PARTICIPANT = gets.to_i
  print "Session number (1 for practice, 2 for main experiment): "
  SESSION = gets.to_i
end

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
    spawn "java -jar FittsTaskTwo.jar"
  end
end

def condition_test_plan(condition_code,num_blocks)
  [
    {
      type: :setup,
      condition_code: condition_code,
      name: "Set up #{CONDITIONS[condition_code-1]}"
    },
    (1..num_blocks).map do |i|
      {
        type: :fitts,
        condition_code: condition_code,
        block_num: i,
        name: "Fitts' C#{condition_code}-B#{i}"
      }
    end,
    {
      type: :finish,
      condition_code: condition_code,
      name: "Finish #{CONDITIONS[condition_code-1]}"
    },
  ]
end

def main_experiment_plan()
  square_row = PARTICIPANT % LATIN_SQUARE.size
  conditions = LATIN_SQUARE[square_row]
  log "Latin square row: #{square_row} - #{conditions.inspect}"
  [
    conditions.map do |condition_code|
      condition_test_plan(condition_code, BLOCKS_PER_CONDITION)
    end,
    condition_test_plan(5, BLOCKS_PER_CONDITION),
    {type: :form, name: "Final questionnaire"},
    {type: :done, name: "Experiment Finished"}
  ].flatten
end

def practice_session_plan()
  log "Practice session"
  [
    {type: :form, name: "Initial questionnaire"},
    condition_test_plan(6, 2),
    {type: :game, name: "Practice with game"},
    condition_test_plan(7, 2),
    {type: :done, name: "Experiment Finished"}
  ].flatten
end

def plan_item_actions(item)
  case item[:type]
  when :done
    [["Quit", -> { exit(0) }]]
  when :fitts
    [
      ["Start Applet", -> {
        setup_config(item[:condition_code], item[:block_num])
        run_applet()
      }],
      ["Start PolyMouse", -> {
        spawn("open ../PolyMouse/bin/PolyMouseDebug.app")
      }],
    ]
  when :setup
    [
      ["Start PolyMouse", -> {
        spawn("open ../PolyMouse/bin/PolyMouseDebug.app")
      }],
      ["Start Pupil", -> {
        Dir.chdir("../pupil/pupil_src/capture") { spawn("python main.py") }
      }],
    ]
  when :game
    [["Start FTL", -> {
      spawn("open /Applications/FTL.app")
    }]]
  when :finish
    [["Extra Block", -> {
      log "Extra block for C#{item[:condition_code]}"
      setup_config(item[:condition_code], BLOCKS_PER_CONDITION+1)
      run_applet()
    }]]
  else
    []
  end
end

# http://stackoverflow.com/questions/858970/how-to-get-a-stopwatch-program-running
def format_stopwatch(time)
  h = sprintf('%02i', (time.to_i / 3600))
  m = sprintf('%02i', ((time.to_i % 3600) / 60))
  s = sprintf('%02i', (time.to_i % 60))
  "#{h}:#{m}:#{s}"
end

def run_gui(plan)
  log "Running GUI with plan: #{JSON.dump(plan)}"

  root = TkRoot.new { title "Experiment" }

  start_time = Time.now
  last_change_time = Time.now
  timer_label = TkLabel.new(root) do
     font TkFont.new('arial 20 bold')
     pack { padx 15 ; pady 15; }
  end
  split_label = TkLabel.new(root) do
     font TkFont.new('arial 15 bold')
     foreground  "red"
     pack { padx 15 ; pady 15; }
  end
  update_timer = -> (_) {
    been_running = Time.now - start_time
    timer_label.configure('text' => format_stopwatch(been_running))
    since_last_section = Time.now - last_change_time
    split_label.configure('text' => format_stopwatch(since_last_section))
  }
  timer = TkRTTimer.new(50, -1, update_timer)
  timer.start
  update_timer[0]

  list = TkListbox.new(root) do
    width 40
    height plan.length
    setgrid 1
    selectmode 'browse'
    pack('fill' => 'x')
  end

  list.insert 0, *plan.map { |e| e[:name] }
  list.selection_set(0)

  cur_buttons = []
  cur_actions = []
  selected = -> {
    last_change_time = Time.now
    cur_sel = list.curselection[0]
    log "Selected #{cur_sel}: #{plan[cur_sel][:name]}"
    cur_actions = plan_item_actions(plan[cur_sel])
    cur_buttons.each {|b| b.destroy() }
    cur_buttons = []
    cur_actions.each do |name, l|
      cur_buttons << TkButton.new(root) do
        width 30
        text name
        command proc {
          log "Running action '#{name}'"
          l[]
        }
        pack('fill' => 'x')
      end
    end
  }
  advance = -> {
    cur_sel = list.curselection[0]
    return if cur_sel+1 >= plan.length
    list.selection_clear(cur_sel)
    list.selection_set(cur_sel+1)
    selected[]
  }
  list.bind('<ListboxSelect>') { selected[] }
  root.bind('Return') { (cur_actions[0] || [nil,->{}])[1].call()}
  root.bind('t') { (cur_actions[1] || [nil,->{}])[1].call()}
  selected[]

  btn_next = TkButton.new(root) do
    text "Next"
    command advance
    pack('fill' => 'x')
  end
  btn_next.focus()

  Tk.mainloop
end

log `sha1sum #{$0}`
plan = if SESSION <= 1
  practice_session_plan()
else
  main_experiment_plan()
end
run_gui(plan)
