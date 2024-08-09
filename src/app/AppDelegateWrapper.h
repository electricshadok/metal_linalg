#ifndef AppDelegateWrapper_h
#define AppDelegateWrapper_h

#import <Foundation/Foundation.h>
#include "App.hpp"

@interface AppDelegateWrapper : NSObject
@property (nonatomic) App *app;
- (instancetype)init;
- (void)draw:(id<CAMetalDrawable>)drawable;
- (void)step;
@end


#endif /* AppDelegateWrapper_h */
