
//
//  NSArray+ASMAsyncEnumeration.h
//  Demo
//
//  Created by Andrew Molloy on 3/14/14.
//  Copyright (c) 2014 Andrew Molloy. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSArray (ASMAsyncEnumeration)

typedef void(^ASMNSArrayAsyncEnumerationBlock)(id obj, NSUInteger idx, BOOL *stop);
typedef void(^ASMNSArrayAsyncEnumerationCompletionBlock)(NSUInteger stoppedIndex);

- (void)asm_enumerateObjectsAsynchronouslyAtIndexes:(NSIndexSet *)s
											options:(NSEnumerationOptions)opts
											onQueue:(dispatch_queue_t)queue
									   stepsPerLoop:(NSUInteger)stepsPerLoop
										 usingBlock:(ASMNSArrayAsyncEnumerationBlock)block
										 completion:(ASMNSArrayAsyncEnumerationCompletionBlock)completion;

- (void)asm_enumerateObjectsAsynchronouslyWithOptions:(NSEnumerationOptions)opts
											  onQueue:(dispatch_queue_t)queue
										 stepsPerLoop:(NSUInteger)stepsPerLoop
										   usingBlock:(ASMNSArrayAsyncEnumerationBlock)block
										   completion:(ASMNSArrayAsyncEnumerationCompletionBlock)completion;

- (void)asm_enumerateObjectsAsynchronouslyOnMainQueueWithOptions:(NSEnumerationOptions)opts
													stepsPerLoop:(NSUInteger)stepsPerLoop
													  usingBlock:(ASMNSArrayAsyncEnumerationBlock)block
													  completion:(ASMNSArrayAsyncEnumerationCompletionBlock)completion;

- (void)asm_enumerateObjectsAsynchronouslyOnMainQueueUsingBlock:(ASMNSArrayAsyncEnumerationBlock)block
													 completion:(ASMNSArrayAsyncEnumerationCompletionBlock)completion;

- (void)asm_enumerateObjectsAsynchronouslyWithOnQueue:(dispatch_queue_t)queue
										   usingBlock:(ASMNSArrayAsyncEnumerationBlock)block
										   completion:(ASMNSArrayAsyncEnumerationCompletionBlock)completion;

@end


