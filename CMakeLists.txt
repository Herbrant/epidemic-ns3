set(main_src epidemic-benchmark)
set(header_files protocol/epidemic-helper protocol/epidemic-packet-queue protocol/epidemic-packet protocol/epidemic-routing-protocol protocol/epidemic-tag stats/stats)
set(source_files ${main_src} ${header_files})
set(target_prefix scratch_epidemic-ns3_)

get_filename_component(main_src ${main_src} ABSOLUTE)
get_filename_component(scratch_absolute_directory ${main_src} DIRECTORY)
string(REPLACE "${PROJECT_SOURCE_DIR}" "${CMAKE_OUTPUT_DIRECTORY}"
               scratch_directory ${scratch_absolute_directory}
)

build_exec(
        EXECNAME epidemic-benchmark
        EXECNAME_PREFIX ${target_prefix}
        SOURCE_FILES ${source_files}
        HEADER_FILES ${header_files}
        LIBRARIES_TO_LINK "${ns3-libs}" "${ns3-contrib-libs}"
        EXECUTABLE_DIRECTORY_PATH ${scratch_directory}/
)
