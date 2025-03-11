// BSD 3-Clause License
//
// Copyright (c) 2023, Dror Smolarsky
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#import "Application.h"

@import Foundation;
@import Cocoa;
@import Metal;
@import MetalKit;

#import "View.h"
#import "WindowDelegate.h"

@implementation Application {
  NSWindow* _window;
  View* _view;
}

- (instancetype)initWithContentRect:(NSRect)contentRect withTitle:(NSString*)title {
  _window =
      [[NSWindow alloc] initWithContentRect:contentRect
                                  styleMask:NSWindowStyleMaskClosable | NSWindowStyleMaskTitled
                                    backing:NSBackingStoreBuffered
                                      defer:NO];
  if (nil == _window) {
    return nil;
  }
  [_window setTitle:title];
  id<MTLDevice> device = MTLCreateSystemDefaultDevice();
  _view = [[View alloc] initWithFrame:contentRect device:device];
  if (nil == _view) {
    return nil;
  }
  [_window setContentView:_view];
  WindowDelegate* windowDelegate = [[WindowDelegate alloc] init];
  if (nil == windowDelegate) {
    return nil;
  }
  [_window setDelegate:windowDelegate];
  [_window makeKeyAndOrderFront:nil];
  _view.clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0);
  return self;
}

@end
