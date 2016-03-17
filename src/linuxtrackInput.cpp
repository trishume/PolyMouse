// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#include "linuxtrackInput.h"
#include "linuxtrack.h"

#include <iostream>
#include <cmath>

using namespace std;

linuxtrackInput::linuxtrackInput() : userEngaged(false) {}

void linuxtrackInput::setup() {
  cout << "Initializing linuxtrack ... " << endl;
  linuxtrack_state_type trackingState = linuxtrack_init("PolyMouse");
  cout << linuxtrack_explain(trackingState) << endl;
}

void linuxtrackInput::update() {
  linuxtrack_pose_t full_pose;
  float blobs[3*3];
  int blobs_read;
  // linuxtrack_state_type trackingState = linuxtrack_get_tracking_state();
  // cout << linuxtrack_explain(trackingState) << endl;
  // if(trackingState != RUNNING) return;
  if(linuxtrack_get_pose_full(&full_pose, blobs, 3, &blobs_read) <= 0){
    //no new pose
    return;
  }

  ofVec2f orientation(full_pose.raw_yaw * -1, full_pose.raw_pitch * -1);
  val = orientation - last;
  // cout << "head pose: " << val << endl;

  if(orientation == last) {
    countNoChange++;
  } else {
    countNoChange = 0;
  }

  userEngaged = (countNoChange < 30 && abs(orientation.x) < 35.0);
  last = orientation;
}
