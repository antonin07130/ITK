WRAP_LIBRARY(IntensityFilters)

set(WRAPPER_LIBRARY_DEPENDS VXLNumerics Base Numerics)

set(WRAPPER_LIBRARY_LINK_LIBRARIES ITKCommon ITKStatistics)

AUTO_INCLUDE_MODULES()
END_WRAP_LIBRARY()
