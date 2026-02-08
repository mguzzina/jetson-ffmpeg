#ifndef AVCODEC_HWCONTEXT_NVMPI_H
#define AVCODEC_HWCONTEXT_NVMPI_H

#include <NvBuffer.h>

#include "hwcontext_drm.h"

/**
 * DRM Prime Frame descriptor for NVMPI HWDevice.
 */
typedef struct AVNVMPIDRMFrameDescriptor {
    /**
     * Backwards compatibility with AVDRMFrameDescriptor.
     */
    // AVDRMFrameDescriptor drm_desc;

    /**
     * References to NvBuffer instances which are used
     * on each drm frame index.
     */
    NvBuffer buffers[AV_DRM_MAX_PLANES];
} AVNVMPIDRMFrameDescriptor;

/**
 * NVMPI-specific data associated with a frame pool.
 *
 * Allocated as AVHWFramesContext.hwctx.
 */
typedef struct AVNVMPIFramesContext {
    // /**
    //  * MPP buffer group.
    //  */
    // MppBufferGroup buf_group;
    // /**
    //  * MPP buffer allocation flags at frames context level.
    //  */
    // int flags;

    /**
     * The descriptors of all frames in the pool after creation.
     * Only valid if AVHWFramesContext.initial_pool_size was positive.
     * These are intended to be used as the buffer of NVMPI decoder.
     */
    AVNVMPIDRMFrameDescriptor *frames;
    int                     nb_frames;
} AVNVMPIFramesContext;

/**
 * NVMPI device details.
 *
 * Allocated as AVHWDeviceContext.hwctx
 */
typedef struct NVMPIDeviceContext {
    /**
     * NvBuffer allocation flags at device context level.
     */
    // int flags;
} NVMPIDeviceContext;

#endif /* AVCODEC_HWCONTEXT_NVMPI_H */
