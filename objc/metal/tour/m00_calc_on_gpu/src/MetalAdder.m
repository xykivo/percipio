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

#import "MetalAdder.h"
#include <objc/NSObjCRuntime.h>

@import Foundation;
@import Metal;

static const unsigned int arraySize = 1 << 24;
static const unsigned int bufferSize = arraySize * sizeof(float);

@implementation MetalAdder {
  id<MTLDevice> _device;
  id<MTLCommandQueue> _queue;
  id<MTLComputePipelineState> _addArraysState;
  id<MTLBuffer> _bufferA;
  id<MTLBuffer> _bufferB;
  id<MTLBuffer> _bufferResult;
}

- (instancetype)initWithDevice:(id<MTLDevice>)device {
  self = [super init];
  if (nil != self) {
    _device = device;
    _queue = [_device newCommandQueue];
    if (nil == _queue) {
      NSLog(@"Failed to create command queue");
    }
    NSError* error;
    NSString* mtlAddLibraryFile = [[NSBundle mainBundle] pathForResource:@"m00calcongpushaders"
                                                                  ofType:@"metallib"];
    NSURL* mtlAddLibraryURL = [NSURL URLWithString:mtlAddLibraryFile];
    id<MTLLibrary> mtlAddLibrary = [_device newLibraryWithURL:mtlAddLibraryURL error:&error];
    if (nil == mtlAddLibrary) {
      NSLog(@"Failed to create Metal add library");
      return nil;
    }
    id<MTLFunction> mtlAddFunction = [mtlAddLibrary newFunctionWithName:@"add_arrays"];
    if (nil == mtlAddFunction) {
      NSLog(@"Failed to find add_arrays function in Metal add library");
      return nil;
    }
    _addArraysState = [_device newComputePipelineStateWithFunction:mtlAddFunction error:&error];
    if (nil == _addArraysState) {
      NSLog(@"Failed to create Metal add arrays pipeline state. Error: %@", error);
      return nil;
    }
  }
  return self;
}

- (void)prepareData {
  _bufferA = [_device newBufferWithLength:bufferSize options:MTLResourceStorageModeShared];
  if (nil == _bufferA) {
    NSLog(@"Failed to create data buffer A");
  }
  [self generateRandomData:_bufferA];
  _bufferB = [_device newBufferWithLength:bufferSize options:MTLResourceStorageModeShared];
  if (nil == _bufferB) {
    NSLog(@"Failed to create data buffer B");
  }
  [self generateRandomData:_bufferB];
  _bufferResult = [_device newBufferWithLength:bufferSize options:MTLResourceStorageModeShared];
  if (nil == _bufferResult) {
    NSLog(@"Failed to create result buffer");
  }
}

- (void)compute {
  id<MTLCommandBuffer> commandBuffer = [_queue commandBuffer];
  if (nil == commandBuffer) {
    NSLog(@"Failed to create command buffer");
    return;
  }
  id<MTLComputeCommandEncoder> commandEncoder = [commandBuffer computeCommandEncoder];
  [self encodeAddCommand:commandEncoder];
  [commandEncoder endEncoding];
  [commandBuffer commit];
  [commandBuffer waitUntilCompleted];
  [self validateResult];
}

- (void)generateRandomData:(id<MTLBuffer>)buffer {
  float* data = buffer.contents;
  for (unsigned int i = 0; arraySize > i; ++i) {
    data[i] = (float)rand() / (float)(RAND_MAX);
  }
}

- (void)encodeAddCommand:(id<MTLComputeCommandEncoder>)commandEncoder {
  [commandEncoder setComputePipelineState:_addArraysState];
  [commandEncoder setBuffer:_bufferA offset:0 atIndex:0];
  [commandEncoder setBuffer:_bufferB offset:0 atIndex:1];
  [commandEncoder setBuffer:_bufferResult offset:0 atIndex:2];
  const MTLSize threadGridSize = MTLSizeMake(arraySize, 1, 1);
  NSUInteger threadGroupSizeX = _addArraysState.maxTotalThreadsPerThreadgroup;
  if (threadGroupSizeX > arraySize) {
    threadGroupSizeX = arraySize;
  }
  MTLSize threadsPerThreadGroup = MTLSizeMake(threadGroupSizeX, 1, 1);
  [commandEncoder dispatchThreads:threadGridSize threadsPerThreadgroup:threadsPerThreadGroup];
}

- (void)validateResult {
  float* a = _bufferA.contents;
  float* b = _bufferB.contents;
  float* result = _bufferResult.contents;
  for (unsigned int i = 0; arraySize > i; ++i) {
    const float expected = a[i] + b[i];
    if (expected != result[i]) {
      NSLog(@"Error: invalid result at index %i (expected %f != %f)", i, expected, result[i]);
      return;
    }
  }
}

@end
