# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_DEB "OFF")
set(CPACK_BINARY_FREEBSD "OFF")
set(CPACK_BINARY_IFW "OFF")
set(CPACK_BINARY_NSIS "OFF")
set(CPACK_BINARY_RPM "OFF")
set(CPACK_BINARY_STGZ "ON")
set(CPACK_BINARY_TBZ2 "OFF")
set(CPACK_BINARY_TGZ "ON")
set(CPACK_BINARY_TXZ "OFF")
set(CPACK_BINARY_TZ "ON")
set(CPACK_BUILD_SOURCE_DIRS "/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-Headers;/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-Headers/build")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENTS_ALL "Unspecified;pkgconfig_package")
set(CPACK_COMPONENTS_ALL_SET_BY_USER "TRUE")
set(CPACK_COMPONENTS_GROUPING "ALL_COMPONENTS_IN_ONE")
set(CPACK_COMPONENT_PKGCONFIG_INSTALL_DISABLED "FALSE")
set(CPACK_COMPONENT_PKGCONFIG_INSTALL_DOWNLOADED "FALSE")
set(CPACK_COMPONENT_PKGCONFIG_INSTALL_HIDDEN "FALSE")
set(CPACK_COMPONENT_PKGCONFIG_INSTALL_REQUIRED "FALSE")
set(CPACK_COMPONENT_PKGCONFIG_PACKAGE_DISABLED "FALSE")
set(CPACK_COMPONENT_PKGCONFIG_PACKAGE_DOWNLOADED "FALSE")
set(CPACK_COMPONENT_PKGCONFIG_PACKAGE_HIDDEN "FALSE")
set(CPACK_COMPONENT_PKGCONFIG_PACKAGE_REQUIRED "FALSE")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEBIAN_FILE_NAME "opencl-c-headers_3.0-1_all.deb")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
set(CPACK_DEBIAN_PACKAGE_BREAKS "opencl-headers (<< 3.0), opencl-clhpp-headers (<< 3.0)")
set(CPACK_DEBIAN_PACKAGE_DEBUG "ON")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/KhronosGroup/OpenCL-Headers")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "khronos")
set(CPACK_DEBIAN_PACKAGE_NAME "opencl-c-headers")
set(CPACK_DEBIAN_PACKAGE_RELEASE "1")
set(CPACK_DEBIAN_PACKAGE_REPLACES "opencl-headers (<< 3.0)")
set(CPACK_DEBIAN_PACKAGE_SECTION "libdevel")
set(CPACK_DEBIAN_PACKAGE_VERSION "3.0")
set(CPACK_DEB_COMPONENT_INSTALL "ON")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "OpenCLHeaders built using CMake")
set(CPACK_GENERATOR "TBZ2;TGZ;TXZ;TZ")
set(CPACK_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
set(CPACK_INNOSETUP_ARCHITECTURE "x64")
set(CPACK_INSTALLED_DIRECTORIES "/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-Headers;/")
set(CPACK_INSTALL_CMAKE_PROJECTS "")
set(CPACK_INSTALL_PREFIX "/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-Headers/install")
set(CPACK_MODULE_PATH "/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-Headers/cmake")
set(CPACK_NSIS_DISPLAY_NAME "OpenCLHeaders 3.0")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "OpenCLHeaders 3.0")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJCOPY_EXECUTABLE "/sbin/objcopy")
set(CPACK_OBJDUMP_EXECUTABLE "/sbin/objdump")
set(CPACK_OUTPUT_CONFIG_FILE "/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-Headers/build/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION "OpenCL (Open Computing Language) C header files
OpenCL (Open Computing Language) is a multi-vendor open standard for
general-purpose parallel programming of heterogeneous systems that include
CPUs, GPUs and other processors.
.
This package provides the C development header files for the OpenCL API
as published by The Khronos Group Inc.  The corresponding specification and
documentation can be found on the Khronos website.")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OpenCLHeaders built using CMake")
set(CPACK_PACKAGE_FILE_NAME "OpenCLHeaders-3.0-Source")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "OpenCLHeaders 3.0")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "OpenCLHeaders 3.0")
set(CPACK_PACKAGE_NAME "OpenCLHeaders")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "khronos")
set(CPACK_PACKAGE_VERSION "3.0")
set(CPACK_PACKAGE_VERSION_MAJOR "3")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGING_INSTALL_PREFIX "/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-Headers/install")
set(CPACK_READELF_EXECUTABLE "/sbin/readelf")
set(CPACK_RESOURCE_FILE_LICENSE "/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-Headers/LICENSE")
set(CPACK_RESOURCE_FILE_README "/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-Headers/README.md")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake/Templates/CPack.GenericWelcome.txt")
set(CPACK_RPM_PACKAGE_SOURCES "ON")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TBZ2;TGZ;TXZ;TZ")
set(CPACK_SOURCE_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
set(CPACK_SOURCE_INSTALLED_DIRECTORIES "/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-Headers;/")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-Headers/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "OpenCLHeaders-3.0-Source")
set(CPACK_SOURCE_RPM "OFF")
set(CPACK_SOURCE_TBZ2 "ON")
set(CPACK_SOURCE_TGZ "ON")
set(CPACK_SOURCE_TOPLEVEL_TAG "Linux-Source")
set(CPACK_SOURCE_TXZ "ON")
set(CPACK_SOURCE_TZ "ON")
set(CPACK_SOURCE_ZIP "OFF")
set(CPACK_STRIP_FILES "")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "Linux-Source")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-Headers/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
