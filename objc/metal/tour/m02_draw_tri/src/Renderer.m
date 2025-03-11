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
@import simd;

#include "common_types.h"

@implementation Renderer {
  id<MTLDevice> _device;
  id<MTLCommandQueue> _queue;
  id<MTLRenderPipelineState> _state;
}

- (instancetype)initWithDevice:(id<MTLDevice>)device view:(nonnull MTKView*)view {
  _device = device;
  if (nil == _device) {
    NSLog(@"Failed to create Metal device");
    return nil;
  }
  _queue = [_device newCommandQueue];
  if (nil == _queue) {
    NSLog(@"Failed to create Metal command queue");
    return nil;
  }
  _state = [self newStateForView:view];
  if (nil == _state) {
    return nil;
  }
  return self;
}

- (void)drawPrimitiveInView:(nonnull MTKView*)view {
  MTLRenderPassDescriptor* renderPassDescriptor = [view currentRenderPassDescriptor];
  if (nil == renderPassDescriptor) {
    return;
  }
  id<MTLCommandBuffer> commandBuffer = [_queue commandBuffer];
  if (nil == commandBuffer) {
    return;
  }
  id<MTLRenderCommandEncoder> commandEncoder =
      [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
  commandEncoder.label = @"Render Primitive";
  vector_uint2 viewport = {view.drawableSize.width, view.drawableSize.height};
  [commandEncoder setViewport:(MTLViewport){0.0, 0.0, viewport.x, viewport.y, 0, 1.0}];
  [commandEncoder setRenderPipelineState:_state];
  static const struct Vertex triVertices[] = {
      {{256, -256}, {1, 0, 0, 1}},
      {{-256, -256}, {0, 1, 0, 1}},
      {{0, 256}, {0, 0, 1, 1}},
  };
  [commandEncoder setVertexBytes:triVertices
                          length:sizeof(triVertices)
                         atIndex:VertexInputIndexVertices];
  [commandEncoder setVertexBytes:&viewport
                          length:sizeof(viewport)
                         atIndex:VertexInputIndexViewport];
  [commandEncoder drawPrimitives:MTLPrimitiveTypeTriangle
                     vertexStart:0
                     vertexCount:(sizeof(triVertices) / sizeof(triVertices[0]))];
  [commandEncoder endEncoding];
  id<MTLDrawable> drawable = view.currentDrawable;
  [commandBuffer presentDrawable:drawable];
  [commandBuffer commit];
}

- (id<MTLRenderPipelineState>)newStateForView:(nonnull MTKView*)view {
  NSError* error;
  NSString* mtlDrawTriLibraryFile = [[NSBundle mainBundle] pathForResource:@"m02drawtrishaders"
                                                                    ofType:@"metallib"];
  NSURL* mtlDrawTriLibraryURL = [NSURL URLWithString:mtlDrawTriLibraryFile];
  id<MTLLibrary> mtlDrawTriLibrary = [_device newLibraryWithURL:mtlDrawTriLibraryURL error:&error];
  if (nil == mtlDrawTriLibrary) {
    NSLog(@"Failed to create Metal draw triangle library\n Error:%@", error.localizedDescription);
    return nil;
  }
  id<MTLFunction> vertFunc = [mtlDrawTriLibrary newFunctionWithName:@"vertexShader"];
  id<MTLFunction> fragFunc = [mtlDrawTriLibrary newFunctionWithName:@"fragmentShader"];
  MTLRenderPipelineDescriptor* renderStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
  renderStateDescriptor.label = @"Draw Colored Primitive";
  renderStateDescriptor.vertexFunction = vertFunc;
  renderStateDescriptor.fragmentFunction = fragFunc;
  renderStateDescriptor.colorAttachments[0].pixelFormat = view.colorPixelFormat;
  id<MTLRenderPipelineState> renderState =
      [_device newRenderPipelineStateWithDescriptor:renderStateDescriptor error:&error];
  if (nil == renderState) {
    NSLog(@"Failed to create Metal draw triangle library\n Error: %@", error.localizedDescription);
    return nil;
  }
  return renderState;
}

@end
