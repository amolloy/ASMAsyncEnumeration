//
//  ASMViewController.m
//  Demo
//
//  Created by Andrew Molloy on 3/14/14.
//  Copyright (c) 2014 Andrew Molloy. All rights reserved.
//

#import "ASMViewController.h"
#import "NSArray+ASMAsyncEnumeration.h"

static void* sProgressObserverContext = &sProgressObserverContext;

@interface ASMViewController ()
@property (nonatomic, strong) IBOutlet UIProgressView* progressView;
@property (nonatomic, strong) IBOutlet UILabel* progressLabel;
@property (nonatomic, strong) IBOutlet UILabel* progressAdditionalInfoLabel;
@property (nonatomic, strong) NSProgress* progress;
@end

@implementation ASMViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

	NSUInteger top = 10000;

	NSMutableArray* testArray = [NSMutableArray arrayWithCapacity:top];
	for (NSUInteger i = 0; i < top; ++i)
	{
		[testArray addObject:@(i)];
	}

	NSTimer* timer = [NSTimer scheduledTimerWithTimeInterval:0
													  target:self
													selector:@selector(timer:)
													userInfo:nil
													 repeats:YES];

	self.progress = [NSProgress progressWithTotalUnitCount:1];
	[self.progress addObserver:self
					forKeyPath:NSStringFromSelector(@selector(fractionCompleted))
					   options:NSKeyValueObservingOptionInitial
					   context:sProgressObserverContext];
	[self.progress becomeCurrentWithPendingUnitCount:1];

	[testArray asm_enumerateObjectsAsynchronouslyOnMainQueueWithOptions:0
														   stepsPerLoop:101
															 usingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
																 NSLog(@"index: %@ value: %@", @(idx), obj);
															 }
															 completion:^(NSUInteger stoppedIndex, NSError* error) {
																 NSLog(@"Stopped at index %@", @(stoppedIndex));
																 if (error)
																 {
																	 NSLog(@"Error: %@", error);
																 }
																 [timer invalidate];
																 [self.progress removeObserver:self
																					forKeyPath:NSStringFromSelector(@selector(fractionCompleted))
																					   context:sProgressObserverContext];
															 }];
	[self.progress resignCurrent];

	NSLog(@"Begin.");
}

- (void)timer:(NSTimer*)timer
{
	NSLog(@"Run Loop Looped");
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object
						change:(NSDictionary *)change context:(void *)context
{
    if (context == sProgressObserverContext)
    {
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            NSProgress* progress = object;
            self.progressView.progress = progress.fractionCompleted;
            self.progressLabel.text = progress.localizedDescription;
            self.progressAdditionalInfoLabel.text = progress.localizedAdditionalDescription;
        }];
    }
    else
    {
        [super observeValueForKeyPath:keyPath ofObject:object change:change context:context];
    }
}

- (IBAction)cancel:(id)sender
{
	[self.progress cancel];
}
@end
