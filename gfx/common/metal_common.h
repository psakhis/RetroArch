//
//  metal_common.h
//  RetroArch_Metal
//
//  Created by Stuart Carnie on 5/14/18.
//

#ifndef METAL_COMMON_H__
#define METAL_COMMON_H__

#import <Metal/Metal.h>
#import "metal/metal_common.h"

#include <retro_common_api.h>
#include "../drivers_shader/slang_process.h"

#ifdef HAVE_CONFIG_H
#include "../../config.h"
#endif

RETRO_BEGIN_DECLS

#pragma mark - Classes

@interface FrameView : NSObject<View>

@property (readonly) RPixelFormat format;
@property (readonly) RTextureFilter filter;
@property (readwrite) BOOL visible;
@property (readwrite) CGRect frame;
@property (readwrite) CGSize size;
@property (readonly) struct video_shader* shader;

@property (readwrite) uint64_t         frameCount;

- (void)setFilteringIndex:(int)index smooth:(bool)smooth;
- (BOOL)setShaderFromPath:(NSString *)path;
- (void)updateFrame:(void const *)src pitch:(NSUInteger)pitch;

@end


@interface MetalMenu : NSObject

@property (nonatomic, readwrite) BOOL enabled;
@property (readwrite) float alpha;

- (void)updateFrame:(void const *)source;

- (void)updateWidth:(int)width
             height:(int)height
             format:(RPixelFormat)format
             filter:(RTextureFilter)filter;
@end

@interface MetalDriver : NSObject<PlatformDelegate>

@property (readonly) video_viewport_t* viewport;
@property (readwrite) bool             keepAspect;
@property (readonly) MetalMenu*        menu;
@property (readwrite) uint64_t         frameCount;
@property (readonly) FrameView*        frameView;

- (instancetype)init NS_DESIGNATED_INITIALIZER;

- (void)setVideo:(const video_info_t *)video;

- (void)beginFrame;
- (void)endFrame;

/*! @brief setNeedsResize triggers a display resize */
- (void)setNeedsResize;

- (void)viewDidUpdateFrame:(NSRect)rect;


#pragma mark - Menu APIs

@end

RETRO_END_DECLS

#endif
