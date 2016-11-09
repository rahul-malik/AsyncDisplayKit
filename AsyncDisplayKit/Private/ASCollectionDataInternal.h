//
//  ASCollectionDataInternal.h
//  AsyncDisplayKit
//
//  Created by Adlai Holler on 11/5/16.
//  Copyright © 2016 Facebook. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <vector>
#import <AsyncDisplayKit/ASBaseDefines.h>
#import <AsyncDisplayKit/ASCollectionData.h>
#import "ASSection.h"
#import "ASIndexedNodeContext.h"
#import "ASObjectDescriptionHelpers.h"

NS_ASSUME_NONNULL_BEGIN

@interface ASCollectionItemImpl : NSObject <ASCollectionItem, ASDescriptionProvider>

// NOTE: This property is nilled out after it is read.
@property (nonatomic, readonly, strong, nullable) ASCellNodeBlock nodeBlock;

- (instancetype)initWithIdentifier:(ASItemIdentifier)identifier
                         nodeBlock:(ASCellNodeBlock)nodeBlock;
@end

/**
 * In the future we could unify this with ASSection, but right now they're
 * used in somewhat different ways, and have different lifetimes.
 *
 * NOTE: When a section is copied, its items array is reset to empty.
 */
@interface ASCollectionSectionImpl : NSObject <ASCollectionSection, ASDescriptionProvider, NSCopying>

- (instancetype)initWithIdentifier:(ASSectionIdentifier)identifier;

// Private properties
@property (nonatomic, strong, readonly) NSArray<ASCollectionItemImpl *> *itemsInternal;
@end

@interface ASCollectionData () <ASDescriptionProvider>

/**
 * Creates a new data that can reuse elements from the given data object, or a blank one if none is provided.
 */
- (instancetype)initWithReusableContentFromCompletedData:(nullable ASCollectionData *)data NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, nullable) void(^postNodeBlock)(ASCellNode *);

@property (nonatomic, strong, readonly) NSArray<ASCollectionSectionImpl *> *sectionsInternal;

/// Retrieve the number of items in each section. Must be completed.
@property (nonatomic, readonly) std::vector<NSInteger> itemCounts;

/// Retrieve the item at the given index path. Must be completed.
- (ASCollectionItemImpl *)itemAtIndexPath:(NSIndexPath *)indexPath;

// Call this when editing the data is done.
- (void)markCompleted;

@end

NS_ASSUME_NONNULL_END
