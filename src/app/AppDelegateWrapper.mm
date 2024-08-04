#import "AppDelegateWrapper.h"
#import <QuartzCore/CAMetalDrawable.hpp>

@implementation AppDelegateWrapper

- (instancetype)init {
    self = [super init];
    if (self) {
        _app = new App();
    }
    return self;
}

- (void)dealloc {
    delete _app;
}

- (void)drawWithDrawable:(id<CAMetalDrawable>)drawable {
    CA::MetalDrawable* cppDrawable = (__bridge CA::MetalDrawable*)drawable;
    _app->draw(cppDrawable);
}

@end
