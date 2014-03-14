# ASMAsyncEnumeration

[![Version](http://cocoapod-badges.herokuapp.com/v/ASMAsyncEnumeration/badge.png)](http://cocoadocs.org/docsets/ASMAsyncEnumeration)
[![Platform](http://cocoapod-badges.herokuapp.com/p/ASMAsyncEnumeration/badge.png)](http://cocoadocs.org/docsets/ASMAsyncEnumeration)

Sometimes, you need perform an operation on every object in an array. Sometimes, that array can be very large. Sometimes, the operation you wish to perform is too slow to enumerate over the entire array on the main thread. Often, moving the array enumeration onto a background thread seems like the best solution. Unfortunately, there is overhead, both technical and cognitive, to do so.

ASMAsyncEnumeration offers another choice: perform the enumeration on the main thread (or any dispatch queue you desire), allowing the thread's run loop to run in between operations.
 
## Extremely important note

ASMAsyncEnumeration is not about doing things fast. ASMAsyncEnumeration will not magically make your code run faster. In fact, if anything, it will make it slower. Instead, the point of ASMAsyncEnumeration is to provide a quick and easy way to perform long running operations, where speed really isn't that important, without having to worry about threading issues.
 
## Usage

To run the example project; clone the repo, and run `pod install` from the Example directory first.

    NSArray* array = ...; // some big array
    [array asm_enumerateObjectsAsynchronouslyOnMainQueueUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        NSLog(@"index: %@ value: %@", @(idx), obj);
    }
    completion:^(NSUInteger stoppedIndex, NSError* error) {
		NSLog(@"Finished.");
	}];

This will perform the enumeration on the main thread, doing one iteration per loop of the main run loop. There are several methods offering various levels of control, including running on specific dispatch queues, controlling how many steps to take per loop of the run loop, and enumerating over a specified index set.

Both the enumeration and completion blocks will be called on the specified dispatch queue.

Using these methods with a mutable array is not advisable. If you wish to use it with an NSMutableArray, it is preferable to make a non-mutable copy and use it instead. The array is retained until the enumeration completes, so the copy can be a temporary:

    NSMutableArray* mutableArray = ...;
    [mutableArray.copy asm_enumerateObjectsAsynchronouslyOnMainQueueUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        NSLog(@"index: %@ value: %@", @(idx), obj);
    }
    completion:^(NSUInteger stoppedIndex, NSError* error) {
		NSLog(@"Finished.");
	}];
  
If you must enumerate a mutable array directly, you must be careful not to mutate the array before the enumeration is complete, otherwise the results are undefined.

ASMAsyncEnumeration supports NSProgress.

## Installation

ASMAsyncEnumeration is available through [CocoaPods](http://cocoapods.org), to install it simply add the following line to your Podfile:

    pod "ASMAsyncEnumeration"

## Author

Andy Molloy, andy@themolloys.org

## License

ASMAsyncEnumeration is available under the MIT license. See the LICENSE file for more info.

