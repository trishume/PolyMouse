# PolyMouse

(Currently WIP)

PolyMouse is a fusion of gaze tracking and head tracking to achieve hands-free pointing. It aims to be competitive in both speed and accuracy with a traditional mouse.
It is a product of my research at the [University of Waterloo HCI lab](http://hci.cs.uwaterloo.ca/).

It does this by using eye gaze to quickly determine an imprecise area of interest and then uses small head movements to refine the position of the cursor onto a small target.

The second component is a recognizer for "vocal gestures" like tongue clicking, lip popping and whistling to perform actions with low latency and high recognition accuracy. This can be achieved because these sounds are much easier to recognize than normal speech, and much quicker to perform than speaking a word.

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
