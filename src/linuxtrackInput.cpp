//
//  linuxtrackInput.cpp
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#include "linuxtrackInput.h"
#include "linuxtrack.h"

#include <iostream>

using namespace std;

linuxtrackInput::linuxtrackInput() {}

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

  val.x = full_pose.raw_yaw * -1;
  val.y = full_pose.raw_pitch * -1;
  // cout << "head pose: " << val << endl;
}
