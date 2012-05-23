//
//  AppDelegate.m
//  flatland
//
//  Created by Ryan Evans on 5/21/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#import "AppDelegate.h"
#include "JSInterpreter.h"
#include <string>

@implementation AppDelegate

@synthesize window;
@synthesize glView = _glView;

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    JSInterpreter* jsi = new JSInterpreter();
    jsi->InitializeVM();
    string filePath = "/Users/ryan/src/mmg/flatland/tests/test_1.js";
    jsi->LoadFile(filePath);
}

@end
