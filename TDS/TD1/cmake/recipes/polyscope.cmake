if(TARGET polyscope::polyscope)
    return()
endif()

message(STATUS "Third-party (external): creating target 'polyscope::polyscope'")


include(CPM)
set(BUILD_SHARED_LIBS OFF)
CPMAddPackage(
    NAME polyscope
    GITHUB_REPOSITORY nmwsharp/polyscope # change back to latest nmwsharp/polyscope after #306 is merged
    GIT_TAG master
)


add_library(polyscope::polyscope ALIAS polyscope)
set_target_properties(polyscope PROPERTIES FOLDER third_party)
set_target_properties(glm PROPERTIES FOLDER third_party)
