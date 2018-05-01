//
//  Copyright (c) 2018 Open Whisper Systems. All rights reserved.
//

#import <Mantle/MTLModel.h>

NS_ASSUME_NONNULL_BEGIN

@class OWSSignalServiceProtosDataMessage;
@class TSAttachment;
@class YapDatabaseReadWriteTransaction;

typedef NS_ENUM(NSUInteger, OWSContactPhoneType) {
    OWSContactPhoneType_Home = 1,
    OWSContactPhoneType_Mobile,
    OWSContactPhoneType_Work,
    OWSContactPhoneType_Custom,
};

@interface OWSContactPhoneNumber : MTLModel

@property (nonatomic, readonly) OWSContactPhoneType phoneType;
// Applies in the OWSContactPhoneType_Custom case.
@property (nonatomic, readonly, nullable) NSString *label;

@property (nonatomic, readonly) NSString *phoneNumber;

- (BOOL)isValid;

@end

#pragma mark -

typedef NS_ENUM(NSUInteger, OWSContactEmailType) {
    OWSContactEmailType_Home = 1,
    OWSContactEmailType_Mobile,
    OWSContactEmailType_Work,
    OWSContactEmailType_Custom,
};

@interface OWSContactEmail : MTLModel

@property (nonatomic, readonly) OWSContactEmailType emailType;
// Applies in the OWSContactEmailType_Custom case.
@property (nonatomic, readonly, nullable) NSString *label;

@property (nonatomic, readonly) NSString *email;

- (BOOL)isValid;

@end

#pragma mark -

typedef NS_ENUM(NSUInteger, OWSContactAddressType) {
    OWSContactAddressType_Home = 1,
    OWSContactAddressType_Work,
    OWSContactAddressType_Custom,
};

@interface OWSContactAddress : MTLModel

@property (nonatomic, readonly) OWSContactAddressType addressType;
// Applies in the OWSContactAddressType_Custom case.
@property (nonatomic, readonly, nullable) NSString *label;

@property (nonatomic, readonly, nullable) NSString *street;
@property (nonatomic, readonly, nullable) NSString *pobox;
@property (nonatomic, readonly, nullable) NSString *neighborhood;
@property (nonatomic, readonly, nullable) NSString *city;
@property (nonatomic, readonly, nullable) NSString *region;
@property (nonatomic, readonly, nullable) NSString *postcode;
@property (nonatomic, readonly, nullable) NSString *country;

- (BOOL)isValid;

@end

#pragma mark -

@interface OWSContact : MTLModel

@property (nonatomic, readonly, nullable) NSString *givenName;
@property (nonatomic, readonly, nullable) NSString *familyName;
@property (nonatomic, readonly, nullable) NSString *nameSuffix;
@property (nonatomic, readonly, nullable) NSString *namePrefix;
@property (nonatomic, readonly, nullable) NSString *middleName;

@property (nonatomic, readonly, nullable) NSArray<OWSContactPhoneNumber *> *phoneNumbers;
@property (nonatomic, readonly, nullable) NSArray<OWSContactEmail *> *emails;
@property (nonatomic, readonly, nullable) NSArray<OWSContactAddress *> *addresses;

// TODO: This is provisional.
@property (nonatomic, readonly, nullable) TSAttachment *avatar;
// "Profile" avatars should _not_ be saved to device contacts.
@property (nonatomic, readonly) BOOL isProfileAvatar;

- (instancetype)init NS_UNAVAILABLE;

+ (OWSContact *_Nullable)contactForDataMessage:(OWSSignalServiceProtosDataMessage *)dataMessage
                                   transaction:(YapDatabaseReadWriteTransaction *)transaction;

- (BOOL)isValid;

@end

#pragma mark -

@interface OWSContacts : NSObject

@end

NS_ASSUME_NONNULL_END