//
//  macMouse.mm
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-11.
//
//

#include "macMouse.h"

#include "ofAppRunner.h"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

static const int kLeftButtonMask = 1;
static const int kRightButtonMask = 2;

static const CGMouseButton kCGButtonMapping[2] = {kCGMouseButtonLeft, kCGMouseButtonRight};
static const CGEventType kCGEventMapping[2] = {kCGEventLeftMouseDown, kCGEventLeftMouseUp};

mouseEventSource::mouseEventSource() {
  evtSrc = (void*)CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
}
mouseEventSource::~mouseEventSource() {
  CFRelease(evtSrc);
}

void moveMouseTo(mouseEventSource &src, ofVec2f pt) {
  CGEventType event;
  CGEventRef ev_ref;

  int pressed = [NSEvent pressedMouseButtons];
  if(pressed & kLeftButtonMask){
    event = kCGEventLeftMouseDragged;
  } else if(pressed & kRightButtonMask){
    event = kCGEventRightMouseDragged;
  } else {
    event = kCGEventMouseMoved;
  }

  CGPoint newPoint = CGPointMake(pt.x,pt.y);
  ev_ref = CGEventCreateMouseEvent((CGEventSourceRef)src.evtSrc, event, newPoint, kCGMouseButtonLeft);
  CGEventPost(kCGHIDEventTap, ev_ref);
  CFRelease(ev_ref);
}

void mouseEventAtPoint(mouseEventSource &src, mouseButtonType btn, mouseEventType evt, ofVec2f pt) {
  CGPoint newPoint = CGPointMake(pt.x,pt.y);
  CGEventRef cgEvt = CGEventCreateMouseEvent((CGEventSourceRef)src.evtSrc, kCGEventMapping[evt], newPoint, kCGButtonMapping[btn]);
  CGEventPost(kCGHIDEventTap, cgEvt);
  CFRelease(cgEvt);
}

void emitScrollEvent(mouseEventSource &src, int amount) {
  CGEventRef cgEvt = CGEventCreateScrollWheelEvent ((CGEventSourceRef)src.evtSrc, kCGScrollEventUnitPixel, 1, amount);
  CGEventPost(kCGHIDEventTap, cgEvt);
  CFRelease(cgEvt);
}

mouseMonitor addMouseMonitor(std::function<void(ofVec2f)> func) {
  // TODO: these monitors might not get released, not sure ARC can handle the (void*) casts
  id globalMon = [NSEvent addGlobalMonitorForEventsMatchingMask:NSLeftMouseDownMask
                                         handler:^(NSEvent *event) {
      NSPoint pt = [NSEvent mouseLocation];
      ofVec2f pos(pt.x,ofGetScreenHeight() - pt.y);
      func(pos);
  }];
  id localMon = [NSEvent addLocalMonitorForEventsMatchingMask:NSLeftMouseDownMask
                                         handler:^(NSEvent *event) {
      NSPoint pt = [NSEvent mouseLocation];
      ofVec2f pos(pt.x,ofGetScreenHeight() - pt.y);
      func(pos);
      return event;
  }];

  mouseMonitor mon;
  mon.globalMonitor = (void*)(globalMon);
  mon.localMonitor = (void*)(localMon);
  return mon;
}

void stopMouseMonitor(mouseMonitor mon) {
  id globalMon = (id)(mon.globalMonitor);
  if(globalMon) [NSEvent removeMonitor: globalMon];
  id localMon = (id)(mon.localMonitor);
  if(localMon) [NSEvent removeMonitor: localMon];
}
