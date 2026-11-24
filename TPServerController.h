//
//  TPServerController.h
//  Teleport
//
//  Created by JuL on Thu Dec 04 2003.
//  Copyright (c) 2003-2005 abyssoft. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TPConnectionController.h"

typedef NS_ENUM(NSInteger, TPServerState) {
	TPServerIdleState,
	TPServerSharedState,
	TPServerControlledState
} ;

@class TPRemoteHost, TPHotBorder, TPMessage;

@interface TPServerController : TPConnectionController
{
	TPServerState _state;
	TPHotBorder * _clientHotBorder;
	NSDictionary * _switchOptions;

	/* Placement the return hot border was created with, so it can be rebuilt
	   after a sleep/wake cycle (see rearmReturnBorderAfterWake). */
	NSRect _clientHotBorderPlacement;
	NSRect _clientHotBorderScreenFrame;
	
	/* Optional UDP pointer channel. The listener socket lives as long as the
	   app is sharing; a session only becomes reachable once a random token has
	   been handed to the controlling client over the TCP connection. */
	int _pointerSocket;
	BOOL _pointerListenerStarted;
	BOOL _pointerPeerValid;
	uint32_t _pointerPeerAddress;
	uint16_t _pointerPeerPort;
	uint64_t _pointerToken;
	uint32_t _pointerLastSequence;
}

+ (TPServerController*)defaultController;

- (void)startSharing;
- (void)stopSharing;

- (void)requestedStartControlByHost:(TPRemoteHost*)host onConnection:(TPNetworkConnection*)connection withInfoDict:(NSDictionary*)infoDict;
- (void)startControlWithInfoDict:(NSDictionary*)infoDict;

- (void)requestStopControlAtLocation:(NSPoint)location withDraggingInfo:(id<NSDraggingInfo>)draggingInfo;
- (void)stopControlWithDisconnect:(BOOL)disconnect;

/* Rebuilds the return hot border while being controlled. The tracking window
   can silently stop firing across a sleep/wake or lock cycle, which left the
   cursor stranded on this Mac until the app was restarted (2026-11-19). */
- (void)rearmReturnBorderAfterWake;

- (void)setSwitchOptions:(NSDictionary*)switchOptions;

@property (nonatomic) BOOL allowControl;
@property (nonatomic, getter=isControlled, readonly) BOOL controlled;

//- (void)sendPong;

@end
