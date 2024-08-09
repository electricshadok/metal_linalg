#include <Cocoa/Cocoa.h>
#include "AppDelegateWrapper.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (strong, nonatomic) NSWindow *window;
@property (strong, nonatomic) CAMetalLayer *metalLayer;
@property (strong, nonatomic) AppDelegateWrapper *appWrapper;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    NSRect frame = NSMakeRect(0, 0, 800, 600);
    NSUInteger style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;
    
    self.window = [[NSWindow alloc] initWithContentRect:frame
                                               styleMask:style
                                                 backing:NSBackingStoreBuffered
                                                   defer:NO];
    [self.window setTitle:@"Metal Renderer"];
    [self.window makeKeyAndOrderFront:nil];
    
    NSView *contentView = [self.window contentView];
    self.metalLayer = [CAMetalLayer layer];
    self.metalLayer.device = (__bridge id<MTLDevice>)MTL::CreateSystemDefaultDevice();
    self.metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    self.metalLayer.framebufferOnly = YES;
    self.metalLayer.frame = contentView.bounds;
    [contentView setLayer:self.metalLayer];
    [contentView setWantsLayer:YES];
    
    self.appWrapper = [[AppDelegateWrapper alloc] init];
    [self draw];
}

- (void)draw {
    @autoreleasepool {
        id<CAMetalDrawable> drawable = [self.metalLayer nextDrawable];
        if (drawable) {
            [self.appWrapper draw:drawable];
        }
    }
    [self performSelector:@selector(draw) withObject:nil afterDelay:1.0/60.0];
}

@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSApplication *app = [NSApplication sharedApplication];
        AppDelegate *delegate = [[AppDelegate alloc] init];
        [app setDelegate:delegate];
        [app run];
    }
    return 0;
}
