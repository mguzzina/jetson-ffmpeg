#include "hwcontext_nvmpi.h"

static const struct {
    enum AVPixelFormat pixfmt;
    uint32_t drm_format;
} supported_formats[] = {
    /* fully-planar YUV */
    { AV_PIX_FMT_YUV420P, DRM_FORMAT_YUV420, },
    /* semi-planar YUV */
    { AV_PIX_FMT_NV12,    DRM_FORMAT_NV12,   },
};

int nvmpi_device_create(AVHWDeviceContext *ctx, const char *device,
                        AVDictionary *opts, int flags) {
    // Possibly useless
}

static int nvmpi_frames_get_constraints(AVHWDeviceContext *hwdev,
                                        const void *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    int i;

    constraints->min_width  = 16;
    constraints->min_height = 16;

    constraints->valid_hw_formats =
        av_malloc_array(2, sizeof(enum AVPixelFormat));
    if (!constraints->valid_hw_formats)
        return AVERROR(ENOMEM);
    constraints->valid_hw_formats[0] = AV_PIX_FMT_DRM_PRIME;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    constraints->valid_sw_formats =
        av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                        sizeof(enum AVPixelFormat));
    if (!constraints->valid_sw_formats)
        return AVERROR(ENOMEM);
    for(i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i].pixfmt;
    constraints->valid_sw_formats[i] = AV_PIX_FMT_NONE;

    return 0;
}

// int nvmpi_frames_init(AVHWFramesContext *hwfc) {
//     // Implementation for initializing the NVMPI frames context
// }

// int nvmpi_frames_uninit(AVHWFramesContext *hwfc) {
//     // Implementation for uninitializing the NVMPI frames context
// }

const HWContextType ff_hwcontext_type_nvmpi = {
    .type                   = AV_HWDEVICE_TYPE_NVMPI,
    .name                   = "NVMPI",

    .device_hwctx_size      = sizeof(AVNVMPIDeviceContext),
    .frames_hwctx_size      = sizeof(AVNVMPIFramesContext),

    .device_create          = &nvmpi_device_create,

    .frames_get_constraints = &nvmpi_frames_get_constraints,

    // .frames_init            = &nvmpi_frames_init,
    // .frames_uninit          = &nvmpi_frames_uninit,

    // .frames_get_constraints = &nvmpi_frames_get_constraints,

    // .frames_get_buffer      = &nvmpi_get_buffer,

    .pix_fmts = (const enum AVPixelFormat[]) {
        AV_PIX_FMT_DRM_PRIME,
        AV_PIX_FMT_NONE
    },
};
