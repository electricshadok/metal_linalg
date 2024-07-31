#import "MetalRendererWrapper.h"
#import <QuartzCore/CAMetalDrawable.hpp>

@implementation MetalRendererWrapper

- (instancetype)init {
    self = [super init];
    if (self) {
        _renderer = new MetalRenderer();
    }
    return self;
}

- (void)dealloc {
    delete _renderer;
}

- (void)drawWithDrawable:(id<CAMetalDrawable>)drawable {
    CA::MetalDrawable* cppDrawable = (__bridge CA::MetalDrawable*)drawable;
    _renderer->draw(cppDrawable);
}

@end
