#import "AppDelegateWrapper.h"
#import <QuartzCore/CAMetalDrawable.hpp>


@implementation AppDelegateWrapper

- (instancetype)init {
    self = [super init];
    if (self) {
        _app = new App();
        
        // Set up a timer to call step() periodically
        [NSTimer scheduledTimerWithTimeInterval:1.0/60.0
                                         target:self
                                       selector:@selector(step)
                                       userInfo:nil
                                        repeats:YES];
    }
    return self;
}

- (void)dealloc {
    delete _app;
}

- (void)draw:(id<CAMetalDrawable>)drawable {
    CA::MetalDrawable* cppDrawable = (__bridge CA::MetalDrawable*)drawable;
    _app->draw(cppDrawable);
}

- (void)step {
    _app->step();
}

@end
