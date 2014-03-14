
//
//  NSArray+ASMAsyncEnumeration.h
//  Demo
//
//  Created by Andrew Molloy on 3/14/14.
//  Copyright (c) 2014 Andrew Molloy. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSArray (ASMAsyncEnumeration)
- (void)asm_enumerateObjectsAsynchronouslyAtIndexes:(NSIndexSet *)s
											options:(NSEnumerationOptions)opts
											onQueue:(dispatch_queue_t)queue
								   withStepsPerLoop:(NSUInteger)stepsPerLoop
										 usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block
										 completion:(void (^)(NSUInteger stoppedIndex))completion;
@end

