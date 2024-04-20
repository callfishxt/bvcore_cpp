#ifndef GRAPHICS_CORE_GL_UTIL_H_
#define GRAPHICS_CORE_GL_UTIL_H_

#include "commons.h"
#include "ImageData.h"

#include <GL/glew.h>

namespace gl {
    inline GLenum to_glenum(ImageFormat imageFormat) {
        switch (imageFormat) {
            case ImageFormat::rgb888: return GL_RGB;
            case ImageFormat::rgba8888: return GL_RGBA;
            default: 
                return 0;
        }
    }

    inline GLenum to_glenum(DrawPrimitive primitive) {
        static const GLenum primitives[]{
            GL_POINTS,
            GL_LINES,
            GL_TRIANGLES
        };
        return primitives[static_cast<int>(primitive)];
    }
}

#endif // GRAPHICS_CORE_GL_UTIL_H_
