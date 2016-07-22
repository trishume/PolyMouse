# PolyMouse

PolyMouse is a fusion of gaze tracking and head tracking to achieve hands-free pointing. It aims to be competitive in both speed and accuracy with a traditional mouse.
It is a product of my research at the [University of Waterloo HCI lab](http://hci.cs.uwaterloo.ca/).

It does this by using eye gaze to quickly determine an imprecise area of interest and then uses small head movements to refine the position of the cursor onto a small target.

The second component is a recognizer for "vocal gestures" like tongue clicking, lip popping and whistling to perform actions with low latency and high recognition accuracy. This can be achieved because these sounds are much easier to recognize than normal speech, and much quicker to perform than speaking a word.

## Results

I may publish a paper in the future but HCI conferences generally require an experiment with participants and I've been too busy to do one so far. One issue is that it takes a couple hours of practice before people can beat the trackpad's speed so I've only had two people (myself being one of them) become proficient at using it. I get around 4.5 bits/s throughput on the Fitts' law pointing speed task (see [my settings](https://gist.github.com/trishume/3755fea9b0cd7460701d63398a8e3a04)) and another pilot participant with ~2 hours of practice gets 3.9 bits/s. It's not difficult, and people pick it up quickly and become reasonably good in a few minutes (~3.2 Fitts' bits/s), it just takes time to train your neck to learn how to point your head with sub-degree accuracy, which is not something that people normally do but doesn't take long to practice into.

As such, I'm personally highly confident that most people could learn to be faster than the trackpad hands-free using a system like this in a couple hours, but I don't have the time and motivation to do an experiment that would show it right now.

Please email me if you have any questions about my research.

## What it Does

Currently this is just a research prototype that I've used with participants. It ties together data from a Pupil eye tracker, a TrackIR 5 head tracker, and a microphone in order to provide a completely hands-free pointing solution. With this system I can perform Fitts' law pointing speed tests and general computing tasks at a speed faster than I can use a trackpad and almost as fast as I can use a mouse.

The program allows switching between various ways of fusing head and eye tracking, but the fastest one is based on Animated MAGIC with a few improvements. Basically what it is is a mouse that is controlled by head movement, which allows very precise pointing, but when you try and move long distances it will detect that you are looking far away from your cursor and quickly move your mouse to the vicinity of your gaze so that you can home in on your target with your head. This combines the high speed but low accuracy of eye tracking with the medium-speed but high accuracy of head tracking.

PolyMouse also integrates with my Popclick VAMP plugins to provide hands-free clicking. Once you have positioned the mouse over a target you can make a short quiet "sss" sound to click, you can also drag by maintaining the noise as a "sssssssssssssssss" sound. There's also some other sounds that let you scroll and an alternative way of clicking with lip popping.

## Software

Currently setting this up on your computer is kind of a mess, but if you're determined everything necessary is open source. You'll need at the very least (Google these):

- openFrameworks plus a bunch of addons including
  - ofxZmq
  - ofxJson
  - a few others, check the XCode project file and google and install those addons
- The Pupil labs eye tracker software (if you want to use an eye tracker, this isn't strictly necessary)
- Linuxtrack
- An installed copy of my Popclick project VAMP plugins, which also implies installing the VAMP SDK

## Hardware

In development I'm using a Pupil Labs eye tracker and a TrackIR 5 optical head pose tracker for maximum accuracy.

The technique should still work with significantly less fancy hardware though. The eventual plan is to implement it using computer vision techniques with a standard webcam.

## Purpose

Hands-free pointing could be useful for:
- Sufferers of repetitive stress injuries
- Programmers who don't want to take their hands off the keyboard
- People who don't have working hands
- People doing other things with their hands like cooking
- Working on large distant displays where using a mouse is inconvenient

There already exist hands-free eye and head tracking based pointing techniques but they are significantly slower than using a standard mouse. An example of this is pure gaze based mouse software which often requires both a magnifying stage for increased accuracy and a dwell clicking stage, both of which take a significant amount of time.

## License

This software is released under the GPLv3 (full text in the `LICENSE` file).

I chose a copyleft license because this is intended to be used as standalone software rather than a library.
I would like any improvements people make to also be available as open source.
