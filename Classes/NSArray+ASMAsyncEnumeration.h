
//
//  NSArray+ASMAsyncEnumeration.h
//  ASMAsyncEnumeration
//
//  Created by Andrew Molloy on 3/14/14.
//  Copyright (c) 2014 Andrew Molloy. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Enumerate over an NSArray asynchronously without having to worry about threading issues.
 */
@interface NSArray (ASMAsyncEnumeration)

typedef void(^ASMNSArrayAsyncEnumerationBlock)(id obj, NSUInteger idx, BOOL *stop);
typedef void(^ASMNSArrayAsyncEnumerationCompletionBlock)(NSUInteger stoppedIndex, NSError* error);

/**
 Executes a given block using the objects in the array at the specified indexes. The block will be executed on the provided dispatch queue. The block will be executed at most *stepsPerLoop* times per time through the run loop. After the enumeration is complete, executes the completion block.

 @param indexSet The indexes of the objects over which to enumerate.

 @param opts A bit mask that specifies the options for the enumeration (whether it should be performed in reverse order). Must be either 0 or NSEnumerationReverse.

 @param queue The dispatch queue on which to perform the enumeration. All calls to the enumeration block and the completion block will occur on this queue.

 @param stepsPerLoop The maximum number of objects the block will be executed on per time through the run loop. stepsPerLoop objects will always be executed each time through the run loop, except the final iteration if there are fewer objects left to enumerate.

 @param block
 The block to apply to elements in the array. The block takes three arguments:
 - *param* obj The element in the array.
 - *param* idx The index of the element in the array.
 - *param* stop A reference to a boolean value. The block can set the value to YES to stop further processing of the array.

 @param completion
 The block to execute when enumeration completes. This block is executed whether enumeration stopped because it completed or because the enumeration block set its stop parameter to YES. The block takes two arguments:
 - *param* stoppedIndex The last index the enumeration block was executed on.
 - *param* error An NSError object if an error occurred, or nil otherwise.
 */
- (void)asm_enumerateObjectsAsynchronouslyAtIndexes:(NSIndexSet *)indexSet
											options:(NSEnumerationOptions)opts
											onQueue:(dispatch_queue_t)queue
									   stepsPerLoop:(NSUInteger)stepsPerLoop
										 usingBlock:(ASMNSArrayAsyncEnumerationBlock)block
										 completion:(ASMNSArrayAsyncEnumerationCompletionBlock)completion;

/**
 Executes a given block using each object of the array, starting with the first object and continuing through the array to the last object. The block will be executed on the provided dispatch queue. The block will be executed at most *stepsPerLoop* times per time through the run loop. After the enumeration is complete, executes the completion block.

 @param opts A bit mask that specifies the options for the enumeration (whether it should be performed in reverse order). Must be either 0 or NSEnumerationReverse.

 @param queue The dispatch queue on which to perform the enumeration. All calls to the enumeration block and the completion block will occur on this queue.

 @param stepsPerLoop The maximum number of objects the block will be executed on per time through the run loop. stepsPerLoop objects will always be executed each time through the run loop, except the final iteration if there are fewer objects left to enumerate.

 @param block
 The block to apply to elements in the array. The block takes three arguments:
 - *param* obj The element in the array.
 - *param* idx The index of the element in the array.
 - *param* stop A reference to a boolean value. The block can set the value to YES to stop further processing of the array.

 @param completion
 The block to execute when enumeration completes. This block is executed whether enumeration stopped because it completed or because the enumeration block set its stop parameter to YES. The block takes two arguments:
 - *param* stoppedIndex The last index the enumeration block was executed on.
 - *param* error An NSError object if an error occurred, or nil otherwise.
 */
- (void)asm_enumerateObjectsAsynchronouslyWithOptions:(NSEnumerationOptions)opts
											  onQueue:(dispatch_queue_t)queue
										 stepsPerLoop:(NSUInteger)stepsPerLoop
										   usingBlock:(ASMNSArrayAsyncEnumerationBlock)block
										   completion:(ASMNSArrayAsyncEnumerationCompletionBlock)completion;

/**
 Executes a given block using each object of the array, starting with the first object and continuing through the array to the last object. The block will be executed on the main thread. The block will be executed at most *stepsPerLoop* times per time through the run loop. After the enumeration is complete, executes the completion block.

 @param opts A bit mask that specifies the options for the enumeration (whether it should be performed in reverse order). Must be either 0 or NSEnumerationReverse.
 
 @param stepsPerLoop The maximum number of objects the block will be executed on per time through the run loop. stepsPerLoop objects will always be executed each time through the run loop, except the final iteration if there are fewer objects left to enumerate.

 @param block
 The block to apply to elements in the array. The block takes three arguments:
 - *param* obj The element in the array.
 - *param* idx The index of the element in the array.
 - *param* stop A reference to a boolean value. The block can set the value to YES to stop further processing of the array.

 @param completion
 The block to execute when enumeration completes. This block is executed whether enumeration stopped because it completed or because the enumeration block set its stop parameter to YES. The block takes two arguments:
 - *param* stoppedIndex The last index the enumeration block was executed on.
 - *param* error An NSError object if an error occurred, or nil otherwise.
 */

- (void)asm_enumerateObjectsAsynchronouslyOnMainQueueWithOptions:(NSEnumerationOptions)opts
													stepsPerLoop:(NSUInteger)stepsPerLoop
													  usingBlock:(ASMNSArrayAsyncEnumerationBlock)block
													  completion:(ASMNSArrayAsyncEnumerationCompletionBlock)completion;

/**
 Executes a given block using each object of the array, starting with the first object and continuing through the array to the last object. The block will be executed on the main thread, and will be executed once per time through the run loop. After the enumeration is complete, executes the completion block.
 
 @param block 
 The block to apply to elements in the array. The block takes three arguments:
     - *param* obj The element in the array.
     - *param* idx The index of the element in the array.
     - *param* stop A reference to a boolean value. The block can set the value to YES to stop further processing of the array.
 
 @param completion
 The block to execute when enumeration completes. This block is executed whether enumeration stopped because it completed or because the enumeration block set its stop parameter to YES. The block takes two arguments:
     - *param* stoppedIndex The last index the enumeration block was executed on.
     - *param* error An NSError object if an error occurred, or nil otherwise.
 */

- (void)asm_enumerateObjectsAsynchronouslyOnMainQueueUsingBlock:(ASMNSArrayAsyncEnumerationBlock)block
													 completion:(ASMNSArrayAsyncEnumerationCompletionBlock)completion;

/**
 Executes a given block using each object of the array, starting with the first object and continuing through the array to the last object. The block will be executed on the provided dispatch queue, and will be executed once per time through the run loop. After the enumeration is complete, executes the completion block.

 @param queue The dispatch queue on which to perform the enumeration. All calls to the enumeration block and the completion block will occur on this queue.

 @param block
 The block to apply to elements in the array. The block takes three arguments:
 - *param* obj The element in the array.
 - *param* idx The index of the element in the array.
 - *param* stop A reference to a boolean value. The block can set the value to YES to stop further processing of the array.

 @param completion
 The block to execute when enumeration completes. This block is executed whether enumeration stopped because it completed or because the enumeration block set its stop parameter to YES. The block takes two arguments:
 - *param* stoppedIndex The last index the enumeration block was executed on.
 - *param* error An NSError object if an error occurred, or nil otherwise.
 */
- (void)asm_enumerateObjectsAsynchronouslyWithOnQueue:(dispatch_queue_t)queue
										   usingBlock:(ASMNSArrayAsyncEnumerationBlock)block
										   completion:(ASMNSArrayAsyncEnumerationCompletionBlock)completion;

@end


