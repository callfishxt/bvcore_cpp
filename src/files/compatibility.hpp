#pragma once

#include "typedefs.hpp"
#include "util/Buffer.hpp"
#include "files/world_regions_fwd.hpp"

namespace compatibility {
    /// @brief Convert region file from version 2 to 3
    /// @see /doc/specs/region_file_spec.md
    /// @param src region file source content
    /// @return new region file content
    util::Buffer<ubyte> convertRegion2to3(
        const util::Buffer<ubyte>& src, RegionLayerIndex layer);
}
