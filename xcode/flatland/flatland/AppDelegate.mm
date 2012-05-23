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
    std::string line = "window.setSize(1024, 768);";
    jsi->RunString(line);
}

@end
