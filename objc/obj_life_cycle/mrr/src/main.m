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

#include <stdlib.h>

@import Foundation;

#import "XKVObject.h"
#import "XKVObjectHolder.h"

void autoReleasePool() {
  @autoreleasepool {
    NSLog(@"-> auto_release_pool");

    XKVObject* obj = [[XKVObject alloc] initWithName:@"obj-auto_release_pool"];
    [obj autorelease];
    XKVObject* holder = [[XKVObjectHolder alloc] initWithName:@"holder-auto_release_pool"];
    [holder autorelease];

    NSLog(@"<- auto_release_pool");
  }
}

void localAutoReleasePool() {
  NSLog(@"-> local_auto_release_pool");

  @autoreleasepool {
    XKVObject* obj = [[XKVObject alloc] initWithName:@"obj-local_auto_release_pool"];
    [obj autorelease];
    XKVObject* holder = [[XKVObjectHolder alloc] initWithName:@"holder-local_auto_release_pool"];
    [holder autorelease];
  }

  NSLog(@"<- local_auto_release_pool");
}

void manualRetainRelease() {
  NSLog(@"-> manual_retain_release");

  XKVObject* obj = [XKVObject createWithName:@"obj-manual_retain_release"];
  [obj release];

  obj = [[XKVObject alloc] initWithName:@"obj-manual_retain_release"];
  [obj release];
  XKVObjectHolder* holder = [[XKVObjectHolder alloc] initWithName:@"holder-manual_retain_release"];
  [holder release];

  NSLog(@"<- manual_retain_release");
}

void manualRetainReleaseLeak() {
  NSLog(@"-> manual_retain_release");

  XKVObject* obj0 = [[XKVObject alloc] initWithName:@"obj0-leaked"];

  XKVObject* obj1 = [[XKVObject alloc] initWithName:@"obj1-leaked"];
  [obj1 retain];  // no need to call retain, retain transfers ownership
  [obj1 release];

  NSLog(@"<- manual_retain_release");
}

int main() {
  NSLog(@"Objective-C MRR object life cycle");

  autoReleasePool();
  localAutoReleasePool();
  manualRetainRelease();
  manualRetainReleaseLeak();
  return EXIT_SUCCESS;
}
