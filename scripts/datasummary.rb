require "csv"

data = []
Dir["FittsStudy/FittsTaskTwo-P*-C*-B*-sd2.csv"].each do |f|
  _, p, c, b = /FittsTaskTwo-P(.*)-C(.*)-B(.*)-sd2\.csv/.match(f).to_a
  table = CSV.read(f, headers: true)
  tps = table["TP(bps)"].map { |e| e.to_f }
  avg_tp = (tps.inject(:+) / tps.size).round(3) unless tps.empty?
  data << [c, p, b, avg_tp]
end

data.sort!

last_c = nil
last_p = nil
participant_data = []
data.each do |c, p, b, avg_tp|
  if last_p != p
    participant_avg = (participant_data.inject(0,:+) / participant_data.size).round(3) unless participant_data.empty?
    puts "   P#{last_p} average: #{participant_avg} bits/s"
    participant_data = []
  end
  puts if last_c != c
  participant_data << avg_tp if avg_tp

  puts "C#{c} P#{p} B#{b}: #{avg_tp} bits/s"

  last_c = c
  last_p = p
end
