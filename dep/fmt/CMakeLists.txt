# This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

include(CheckSymbolExists)

set(HEADRS 
        include/fmt/args.h
        include/fmt/chrono.h
        include/fmt/color.h
        include/fmt/compile.h
        include/fmt/core.h
        include/fmt/format.h
        include/fmt/format-inl.h
        include/fmt/os.h
        include/fmt/ostream.h
        include/fmt/printf.h
        include/fmt/ranges.h
        include/fmt/std.h
        include/fmt/xchar.h)

set(SRCS
        src/format.cc
        src/os.cc
        )

add_library(fmt ${SRCS} ${HEADRS})
target_include_directories(fmt PRIVATE ${CMAKE_BINARY_DIR})
