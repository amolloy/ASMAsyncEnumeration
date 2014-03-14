//
//  NSArray+ASMAsyncEnumeration.m
//  Demo
//
//  Created by Andrew Molloy on 3/14/14.
//  Copyright (c) 2014 Andrew Molloy. All rights reserved.
//

#import "NSArray+ASMAsyncEnumeration.h"

@implementation NSArray (ASMAsyncEnumeration)

- (void)asm_enumerateObjectsAsynchronouslyWithIndexes:(NSUInteger*)indexes
										   indexCount:(NSUInteger)indexCount
										  currentStep:(NSUInteger)step
											  options:(NSEnumerationOptions)opts
											  onQueue:(dispatch_queue_t)queue
										 stepsPerLoop:(NSUInteger)stepsPerLoop
										   usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block
										   completion:(void (^)(NSUInteger stoppedIndex))completion
{
	NSMutableIndexSet* indexSet = [NSMutableIndexSet indexSet];
	BOOL done = NO;

	if (opts & NSEnumerationReverse)
	{
		NSUInteger start = (indexCount - 1) - step * stepsPerLoop;
		NSUInteger end = start - stepsPerLoop;
		if (end > start)
		{
			end = 0;
			done = YES;
		}
		for (NSUInteger i = start; i > end; --i)
		{
			[indexSet addIndex:indexes[i]];
		}
		if (done)
		{
			[indexSet addIndex:indexes[0]];
		}
	}
	else
	{
		NSUInteger start = step * stepsPerLoop;
		NSUInteger end = start + stepsPerLoop;
		if (end >= indexCount)
		{
			end = indexCount;
			done = YES;
		}
		for (NSUInteger i = start; i < end; ++i)
		{
			[indexSet addIndex:indexes[i]];
		}
	}

	__block BOOL shouldStop = NO;
	__block NSUInteger lastIndex = 0;

	[self enumerateObjectsAtIndexes:indexSet
							options:opts
						 usingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
							 lastIndex = idx;
							 block(obj, idx, stop);
							 shouldStop = *stop;
						 }];

	if (!shouldStop && !done)
	{
		dispatch_async(queue,
					   ^{
						   [self asm_enumerateObjectsAsynchronouslyWithIndexes:indexes
																	indexCount:indexCount
																   currentStep:step + 1
																	   options:opts
																	   onQueue:queue
																  stepsPerLoop:stepsPerLoop
																	usingBlock:[block copy]
																	completion:[completion copy]];
					   });
	}
	else
	{
		free(indexes);
		completion(lastIndex);
	}
}

- (void)asm_enumerateObjectsAsynchronouslyAtIndexes:(NSIndexSet *)s
											options:(NSEnumerationOptions)opts
											onQueue:(dispatch_queue_t)queue
									   stepsPerLoop:(NSUInteger)stepsPerLoop
										 usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block
										 completion:(void (^)(NSUInteger stoppedIndex))completion
{
	NSUInteger indexCount = [s count];
	NSUInteger* indexes = calloc(indexCount, sizeof(NSUInteger));
	[s getIndexes:indexes
		 maxCount:indexCount
	 inIndexRange:nil];

	dispatch_async(queue,
				   ^{
					   [self asm_enumerateObjectsAsynchronouslyWithIndexes:indexes
																indexCount:indexCount
															   currentStep:0
																   options:opts
																   onQueue:queue
															  stepsPerLoop:stepsPerLoop
																usingBlock:[block copy]
																completion:[completion copy]];
				   });
}

- (void)asm_enumerateObjectsAsynchronouslyWithOptions:(NSEnumerationOptions)opts
											  onQueue:(dispatch_queue_t)queue
										 stepsPerLoop:(NSUInteger)stepsPerLoop
										   usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block
										   completion:(void (^)(NSUInteger stoppedIndex))completion
{
	[self asm_enumerateObjectsAsynchronouslyAtIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, self.count)]
											  options:opts
											  onQueue:queue
										 stepsPerLoop:stepsPerLoop
										   usingBlock:block
										   completion:completion];
}

- (void)asm_enumerateObjectsAsynchronouslyOnMainQueueWithOptions:(NSEnumerationOptions)opts
													stepsPerLoop:(NSUInteger)stepsPerLoop
													  usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block
													  completion:(void (^)(NSUInteger stoppedIndex))completion
{
	[self asm_enumerateObjectsAsynchronouslyAtIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, self.count)]
											  options:opts
											  onQueue:dispatch_get_main_queue()
										 stepsPerLoop:stepsPerLoop
										   usingBlock:block
										   completion:completion];
}

- (void)asm_enumerateObjectsAsynchronouslyOnMainQueueUsingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block
													 completion:(void (^)(NSUInteger stoppedIndex))completion
{
	[self asm_enumerateObjectsAsynchronouslyAtIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, self.count)]
											  options:0
											  onQueue:dispatch_get_main_queue()
										 stepsPerLoop:1
										   usingBlock:block
										   completion:completion];
}

- (void)asm_enumerateObjectsAsynchronouslyWithOnQueue:(dispatch_queue_t)queue
										   usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block
										   completion:(void (^)(NSUInteger stoppedIndex))completion
{
	[self asm_enumerateObjectsAsynchronouslyAtIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, self.count)]
											  options:0
											  onQueue:dispatch_get_main_queue()
										 stepsPerLoop:1
										   usingBlock:block
										   completion:completion];
}
@end
