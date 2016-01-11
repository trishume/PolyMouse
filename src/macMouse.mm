//
//  macMouse.mm
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-11.
//
//

#include "macMouse.h"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

void moveMouseTo(ofVec2f pt) {
  CGEventType event;
  CGEventRef ev_ref;

  int pressed = [NSEvent pressedMouseButtons];
  if(pressed & kCGMouseButtonLeft){
    event = kCGEventLeftMouseDragged;
  } else if(pressed & kCGMouseButtonRight){
    event = kCGEventRightMouseDragged;
  } else {
    event = kCGEventMouseMoved;
  }

  ev_ref = CGEventCreateMouseEvent(NULL, event, CGPointMake(pt.x,pt.y), kCGMouseButtonLeft);
  CGEventPost(kCGHIDEventTap, ev_ref);
  CFRelease(ev_ref);
}
