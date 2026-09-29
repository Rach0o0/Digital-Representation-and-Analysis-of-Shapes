if(DEFINED ENV{CPM_SOURCE_CACHE})
    set(CPM_SOURCE_CACHE_DEFAULT $ENV{CPM_SOURCE_CACHE})
else()
    # Set CPM cache folder if unset
    file(REAL_PATH "~/.cache/CPM" CPM_SOURCE_CACHE_DEFAULT EXPAND_TILDE)
endif()

set(CPM_SOURCE_CACHE
    ${CPM_SOURCE_CACHE_DEFAULT}
    CACHE PATH "Directory to download CPM dependencies"
)
message(STATUS "Using CPM cache folder: ${CPM_SOURCE_CACHE}")
