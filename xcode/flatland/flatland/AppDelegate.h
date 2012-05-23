//
//  AppDelegate.h
//  flatland
//
//  Created by Ryan Evans on 5/21/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "FLGLView.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow* window;
@property (assign) IBOutlet FLGLView* glView;

@end
