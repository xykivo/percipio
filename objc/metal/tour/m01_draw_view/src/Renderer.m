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

#import "Renderer.h"

@import Foundation;
@import Cocoa;
@import Metal;

@implementation Renderer {
  id<MTLDevice> _device;
  id<MTLCommandQueue> _queue;
}

- (instancetype)initWithDevice:(id<MTLDevice>)device {
  _device = device;
  if (nil == _device) {
    return nil;
  }
  _queue = [_device newCommandQueue];
  if (nil == _queue) {
    return nil;
  }
  return self;
}

- (void)clearViewColor:(nonnull MTKView*)view {
  // Present to a drawable from an empty command buffers clears the view
  // color to the current view clear color property.
  MTLRenderPassDescriptor* renderPassDescriptor = [view currentRenderPassDescriptor];
  if (nil == renderPassDescriptor) {
    return;
  }
  id<MTLCommandBuffer> commandBuffer = [_queue commandBuffer];
  id<MTLRenderCommandEncoder> commandEncoder =
      [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
  [commandEncoder endEncoding];
  id<MTLDrawable> drawable = view.currentDrawable;
  [commandBuffer presentDrawable:drawable];
  [commandBuffer commit];
}

@end
