//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, IntuneMAMCertificatePinningStatusCode)
{
    IntuneMAMCertificatePinningInvalidChallenge = 100,           // The operation failed because the supplied challenge object is either nil or invalid
    IntuneMAMCertificatePinningInvalidCertificateChain = 101,            // The operation failed because the supplied certificate chain is invalid or empty
    IntuneMAMCertificatePinningNilHost = 102,                    // The operation failed because the supplied host is nil or empty
    IntuneMAMCertificatePinningFailedTrustEvaluation = 103,          // The certificates failed to pass trust certificate validation
    IntuneMAMCertificatePinningFailedFormationEvaluation = 104,          // The certificates failed to pass formation validation
    IntuneMAMCertificatePinningErrorAccessingCert = 105,         // Failed to extract one or more certificates from the chain
    IntuneMAMCertificatePinningAlgNotSupported = 106,            // The operation failed because the specified algorithm is not supported or the hashing operation failed
    IntuneMAMCertificatePinningMatchNotFound = 107,            // Failed to find a matching pin within the provided certificate chain with the provided host
};

__attribute__((visibility("default")))
@interface IntuneMAMCertificatePinningManager : NSObject

+(IntuneMAMCertificatePinningManager* _Nonnull) instance;

// Validates the certificate chain for the specified NSURLAuthenticationChallenge. Returns TRUE if the certificate chain matches the
// expected one for the host and identity or if no pins are provided for the host or identity. If FALSE is returned, the
// certificate chain does not match the expected chain and the application should block the request. If nil is passed in for the
// identity, the current thread identity is used to perform the certificate pinning validation.
- (BOOL) validateChainWithChallenge:(NSURLAuthenticationChallenge* _Nonnull)challenge andIdentity:(NSString* _Nullable)identity error:(NSError* _Nullable* _Nullable)error;

// Validates the certificate chain for the specified cert chain and host. Returns TRUE if the certificate chain matches an expected
// one for the host and identity or if no pins are provided for the host or identity. If FALSE is returned, the certificate
// chain does not match the expected chain and the application should block the request. The certificate array should include the server
// certificate (at index 0) followed by intermediate certificates and lastly with the root certificate (at index -1).
// If nil is passed in for the identity, the current thread identity is used to perform the certificate pinning validation.
- (BOOL) validateChainWithCertificates:(NSArray<NSData*>* _Nonnull)certificates andHostname:(NSString* _Nonnull)hostname andIdentity:(NSString* _Nullable)identity error:(NSError* _Nullable* _Nullable)error;

@end

