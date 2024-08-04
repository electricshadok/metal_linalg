#ifndef AppDelegateWrapper_h
#define AppDelegateWrapper_h

#import <Foundation/Foundation.h>
#include "App.hpp"

@interface AppDelegateWrapper : NSObject
@property (nonatomic) App *app;
- (instancetype)init;
- (void)drawWithDrawable:(id<CAMetalDrawable>)drawable;
@end


#endif /* AppDelegateWrapper_h */
