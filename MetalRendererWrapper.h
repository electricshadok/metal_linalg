#ifndef MetalRendererWrapper_h
#define MetalRendererWrapper_h

#import <Foundation/Foundation.h>
#import "MetalRenderer.hpp"

@interface MetalRendererWrapper : NSObject
@property (nonatomic, readonly) MetalRenderer *renderer;
- (instancetype)init;
- (void)drawWithDrawable:(id<CAMetalDrawable>)drawable;
@end

#endif /* MetalRendererWrapper_h */
