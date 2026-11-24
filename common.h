/*
 *  common.h
 *  Teleport
 *
 *  Created by JuL on Thu Dec 04 2003.
 *  Copyright (c) 2003-2005 abyssoft. All rights reserved.
 *
 */

#import <TPPreferencesManager.h>

/* Debug */
#define DEBUG_GENERAL 0
#define DEBUG_TRANSFERS 0

#define DebugLog(logString, args...) \
if([[TPPreferencesManager sharedPreferencesManager] boolForPref:ENABLE_DEBUG_LOG]) \
NSLog(logString , ##args)

/* Persistent plaintext log (~/Library/Logs/teleport-pro.log). The unified log
   redacts dynamic values to <private>, which made every post-mortem of a
   disconnect guesswork; TPLog also mirrors to NSLog. Cheap, low-volume events
   only - never call it per input event. */
#define TPLog(format, args...) TPLogWrite(format , ##args)

void TPLogWrite(NSString *format, ...);

/* Macros */
#define DELETE(obj) if(obj) {[obj release]; obj=nil;}
#define PRINT_ME DebugLog(@"%@: %s", self, __PRETTY_FUNCTION__);
#define PRINT_ME_IF(cond) do{if(cond) DebugLog(@"%@: %s", self, __PRETTY_FUNCTION__);}while(0)

/* Constants */
#define RV_SERVICE @"_teleport._tcp"

#define LEFT_MOUSE_BUTTON 0
#define RIGHT_MOUSE_BUTTON 1
#define OTHER_MOUSE_BUTTON 2
