#  Copyright (c) Microsoft Corporation. All rights reserved.
#  Licensed under the MIT License.

cmake_minimum_required (VERSION 3.20)

project (AzureSphereDS18B20Sample C)

azsphere_configure_tools(TOOLS_REVISION "22.09")
azsphere_configure_api(TARGET_API_SET "14")

# Create executable
add_executable (${PROJECT_NAME} main.c)
target_link_libraries (${PROJECT_NAME} applibs pthread gcc_s c)

add_subdirectory(ds18b20)

azsphere_target_add_image_package(${PROJECT_NAME})
