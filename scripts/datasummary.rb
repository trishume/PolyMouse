require "csv"
thresh = ARGV[0] ? ARGV[0].to_f : 0.0
folder = ARGV[1] ? ARGV[1] : "FittsStudy"

data = []
Dir["#{folder}/FittsTaskTwo-P*-C*-B*-sd2.csv"].each do |f|
  _, p, c, b = /FittsTaskTwo-P(.*)-C(.*)-B(.*)-sd2\.csv/.match(f).to_a
  table = CSV.read(f, headers: true)
  tps_raw = table["TP(bps)"].map { |e| e.to_f }
  tps = tps_raw.select {|tp| tp > thresh }
  # TODO: maybe discard sequences that were retried
  avg_tp = (tps.inject(:+) / tps.size).round(3) unless tps.empty?
  data << [c, p, b, avg_tp, tps_raw.length != tps.length]
end

data.sort!

last_c = nil
last_p = nil
participant_data = []
data.each do |c, p, b, avg_tp, did_drop|
  if (last_p != p && last_p) || (last_c != c && last_c)
    participant_avg = (participant_data.inject(0,:+) / participant_data.size).round(3) unless participant_data.empty?
    best_2_data = participant_data.sort.reverse[0..1]
    best_2_avg = (best_2_data.inject(0,:+) / best_2_data.size).round(3) unless best_2_data.empty?
    puts "   P#{last_p} average: #{participant_avg} bits/s     best2: #{best_2_avg} bits/s"

    participant_data = []
  end
  puts if last_c != c
  participant_data << avg_tp if avg_tp

  puts "C#{c} P#{p} B#{b}: #{avg_tp} bits/s #{did_drop ? '~' : ''}"

  last_c = c
  last_p = p
end
